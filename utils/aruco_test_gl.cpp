/*****************************
Copyright 2011 Rafael Muñoz Salinas. All rights reserved.

Redistribution and use in source and binary forms, with or without modification, are
permitted provided that the following conditions are met:

   1. Redistributions of source code must retain the above copyright notice, this list of
      conditions and the following disclaimer.

   2. Redistributions in binary form must reproduce the above copyright notice, this list
      of conditions and the following disclaimer in the documentation and/or other materials
      provided with the distribution.

THIS SOFTWARE IS PROVIDED BY Rafael Muñoz Salinas ''AS IS'' AND ANY EXPRESS OR IMPLIED
WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND
FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL Rafael Muñoz Salinas OR
CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

The views and conclusions contained in the software and documentation are those of the
authors and should not be interpreted as representing official policies, either expressed
or implied, of Rafael Muñoz Salinas.
********************************/
#include <iostream>

#include <fstream>
#include <sstream>
#ifdef __APPLE__
#include <gl.h>
#include <GLUT/glut.h>
#else
#include <GL/gl.h>
#include <GL/glut.h>
#endif
#include "aruco.h"
using namespace cv;
using namespace aruco;

string TheInputVideo;
string TheIntrinsicFile;
bool The3DInfoAvailable=false;
float TheMarkerSize=-1;
MarkerDetector PPDetector;
VideoCapture TheVideoCapturer;
vector<Marker> TheMarkers;
Mat TheInputImage,TheUndInputImage,TheResizedImage;
CameraParameters TheCameraParams;
Size TheGlWindowSize;
bool TheCaptureFlag=true;
bool readIntrinsicFile(string TheIntrinsicFile,Mat & TheIntriscCameraMatrix,Mat &TheDistorsionCameraParams,Size size);

void vDrawScene();
void vIdle();
void vResize( GLsizei iWidth, GLsizei iHeight );
void vMouse(int b,int s,int x,int y);


/************************************
 *
 *
 *
 *
 ************************************/

bool readArguments ( int argc,char **argv )
{
    if (argc!=4) {
        cerr<<"Invalid number of arguments"<<endl;
        cerr<<"Usage: (in.avi|live)  intrinsics.yml   size "<<endl;
        return false;
    }
    TheInputVideo=argv[1];
    TheIntrinsicFile=argv[2];
    TheMarkerSize=atof(argv[3]);
    return true;
}


/************************************
 *
 *
 *
 *
 ************************************/

int main(int argc,char **argv)
{
    try
    {//parse arguments
        if (readArguments (argc,argv)==false) return 0;
        //read from camera
	//Deepak changed to 1 from 0
        if (TheInputVideo=="live") TheVideoCapturer.open(0);
        else TheVideoCapturer.open(TheInputVideo);
        if (!TheVideoCapturer.isOpened())
        {
            cerr<<"Could not open video"<<endl;
            return -1;

        }

        //read first image
        TheVideoCapturer>>TheInputImage;
        //read camera paramters if passed
        TheCameraParams.readFromXMLFile(TheIntrinsicFile);
        TheCameraParams.resize(TheInputImage.size());

        glutInit(&argc, argv);
        glutInitWindowPosition( 0, 0);
        glutInitWindowSize(TheInputImage.size().width,TheInputImage.size().height);
        glutInitDisplayMode( GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE );
        glutCreateWindow( "AruCo" );
        glutDisplayFunc( vDrawScene );
        glutIdleFunc( vIdle );
        glutReshapeFunc( vResize );
        glutMouseFunc(vMouse);
        glClearColor( 0.0, 0.0, 0.0, 1.0 );
        glClearDepth( 1.0 );
        TheGlWindowSize=TheInputImage.size();
        vResize(TheGlWindowSize.width,TheGlWindowSize.height);
        glutMainLoop();

    } catch (std::exception &ex)

    {
        cout<<"Exception :"<<ex.what()<<endl;
    }

}
/************************************
 *
 *
 *
 *
 ************************************/

void vMouse(int b,int s,int x,int y)
{
    if (b==GLUT_LEFT_BUTTON && s==GLUT_DOWN) {
        TheCaptureFlag=!TheCaptureFlag;
    }

}

/************************************
 *
 *
 *
 *
 ************************************/
void axis(float size)
{
    glColor3f (1,0,0 );
    glBegin(GL_LINES);
    glVertex3f(0.0f, 0.0f, 0.0f); // origin of the line
    glVertex3f(size,0.0f, 0.0f); // ending point of the line
    glEnd( );

    glColor3f ( 0,1,0 );
    glBegin(GL_LINES);
    glVertex3f(0.0f, 0.0f, 0.0f); // origin of the line
    glVertex3f( 0.0f,size, 0.0f); // ending point of the line
    glEnd( );


    glColor3f (0,0,1 );
    glBegin(GL_LINES);
    glVertex3f(0.0f, 0.0f, 0.0f); // origin of the line
    glVertex3f(0.0f, 0.0f, size); // ending point of the line
    glEnd( );


}
/**********************************************************
 *Calculate the distance between two points expressed as cv matrices
 *Finished by deepak
 *
 *
 **************************************************************/

float calculateDistance(cv::Mat t0,cv::Mat t1){
  
  float d[3];
  float distsquared = 0;
  float distance = 0;
  for (int i = 0; i < 3; i++){
    d[i] = (t0.at<float>(i,0) - t1.at<float>(i,0)); 
    distsquared = distsquared + d[i] * d[i];   
  }
  
  distance = sqrt(distsquared);
  
  return distance;
  
}

vector<float> calculateAreaAndPerimeter(){
  vector<float> ap;

  
  if (TheMarkers.size() <= 2) {
    ap.push_back(0);
    ap.push_back(0);
    return ap;
  }
  
  cv::Mat t0 = TheMarkers[0].Tvec;
  cv::Mat t1 = TheMarkers[1].Tvec;
  cv::Mat t2 = TheMarkers[2].Tvec;
		
  //  cv::Point2f c = TheMarkers[0].getCenter();
  //cout<<"center:"<<c<<endl;
  //  cout<<"I am inside"<<endl;

  //If the input is a square
  int sz =  TheMarkers.size();
  cout<<"Size"<<sz<<endl;
  
  if (TheMarkers.size() == 4) {
    float length = calculateDistance(t0,t1);
    float width = calculateDistance(t1,t2);
    float area = length * width;
    float perimeter = 2*length + 2*width;
    ap.push_back(area); ap.push_back(perimeter);
  }
  //The input is a triangle
  else if (TheMarkers.size() == 3){
    
    cout<<"I am inside"<<endl;
    float side1 = calculateDistance(t0,t1);
    float side2 = calculateDistance(t1,t2);
    float side3 = calculateDistance(t0,t2);
    float perimeter = side1 + side2 + side3;
    float s = perimeter / 2;
    float area = sqrt(s * (s - side1) * (s - side2) * (s - side3));
    cout<<"This is intense shit"<<area<<endl;
    ap.push_back(area); ap.push_back(perimeter);
    
  }
  
  return ap;
  
}

void drawString(char* string){

  char *c;
  for (c=string; *c != '\0'; c++) 
    {
      glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *c);
    }
 
}


void drawSideText(cv::Mat t3,cv::Mat t2){
    
  float s = calculateDistance(t3,t2);
  char buffer[50];
  int n = sprintf(buffer,"%.0f\n",floor(s*100+0.5));

  float x_bmid = (t3.at<float>(0,0) + t2.at<float>(0,0))/2;
  float y_bmid = (t3.at<float>(1,0) + t2.at<float>(1,0))/2;
  float z_bmid = (-t3.at<float>(2,0) - t2.at<float>(2,0))/2;

  glPushMatrix();
  glColor3f(0,0,1);
  
  
  glLoadIdentity();
  glTranslatef(x_bmid,y_bmid,z_bmid);
  glRasterPos3f( 0.0f, 0.0f, 0.0f );
  drawString(buffer);
  glPopMatrix();
  
}

void drawSideTextArea(cv::Mat t3,cv::Mat t2, float a){
    
  //  float s = calculateDistance(t3,t2);
  char buffer[50];
  int n = sprintf(buffer,"%4.2f\n",floor(a*100+0.5));

  float x_bmid = (t3.at<float>(0,0) + t2.at<float>(0,0))/2;
  float y_bmid = (t3.at<float>(1,0) + t2.at<float>(1,0))/2;
  float z_bmid = (-t3.at<float>(2,0) - t2.at<float>(2,0))/2;

  glPushMatrix();
  glColor3f(0,0,1);
  
  
  glLoadIdentity();
  glTranslatef(x_bmid,y_bmid,z_bmid);
  glRasterPos3f( 0.0f, 0.0f, 0.0f);
  drawString(buffer);
  glPopMatrix();
  
}


/************************************
 *
 *
 *
 *
 ************************************/
void vDrawScene()
{
  if (TheResizedImage.rows==0)// prevent from going on until the image is initialized
        return;
    ///clear
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
    //glColor3f(1.0f,0.0f,0.0f);
    //    draw image in the buffer
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, TheGlWindowSize.width, 0, TheGlWindowSize.height, -1.0, 1.0);
    glViewport(0, 0, TheGlWindowSize.width , TheGlWindowSize.height);
    glDisable(GL_TEXTURE_2D);
    
    
    glPixelZoom( 1, -1);
    glRasterPos3f( 0, TheGlWindowSize.height  - 0.5, -1.0 );
    glDrawPixels ( TheGlWindowSize.width , TheGlWindowSize.height , GL_RGB , GL_UNSIGNED_BYTE , TheResizedImage.ptr(0) );
    ///Set the appropriate projection matrix so that rendering is done in a enrvironment
    //like the real camera (without distorsion)

    glMatrixMode(GL_PROJECTION);
    double proj_matrix[16];
    TheCameraParams.glGetProjectionMatrix(TheInputImage.size(),TheGlWindowSize,proj_matrix,0.05,10);
    glLoadIdentity();
    glLoadMatrixd(proj_matrix);

    

    //now, for each marker,
    double modelview_matrix[16];
    glMatrixMode(GL_MODELVIEW);
    
    //Deepak Comment here
    glPushMatrix();
    vector<cv::Point2f> centers;

     for (unsigned int m=0;m<TheMarkers.size();m++)
     {
       	centers.push_back(TheMarkers[m].getCenter());
	
    //   	/*Deepak Comment: Begin
	TheMarkers[m].glGetModelViewMatrix(modelview_matrix);
	glLoadIdentity();
	glLoadMatrixd(modelview_matrix);
	axis(TheMarkerSize);
	glColor3f(1,0.4,0.4);
	glTranslatef(0, TheMarkerSize/2,0);
	glPushMatrix();
	glutWireCube( TheMarkerSize );
	glPopMatrix();
    // 	Deepak Comment: End*/
     }


   
    vector<float> ap;
    ap = calculateAreaAndPerimeter();

    //glMatrixMode(GL_MODELVIEW);
    //glPushMatrix();
    // glLoadIdentity();
    //glColor3f (1,0,1 );
    //glutSolidTeapot(4);

    if (centers.size() > 3){
      //      for (int c = 0; c < 3; c++){
      glColor3f(1,1,0);
      //glTranslatef(centers[0].x,0.0f,centers[0].y);
      glPushMatrix();
      glLoadIdentity();
      //    glTranslatef(0, TheMarkerSize/2,0);
       glBegin(GL_QUADS);
      // //origin of the line
      // cout<<"The Marker Size:"<<TheMarkerSize<<endl;
      // //      glVertex3f(TheMarkerSize/2, TheMarkerSize/2,TheMarkerSize/2);//ending point of the line
       cv::Mat t0 = TheMarkers[0].Tvec;
       cv::Mat t1 = TheMarkers[1].Tvec;
       cv::Mat t2 = TheMarkers[2].Tvec;
       cv::Mat t3 = TheMarkers[3].Tvec;
       glVertex3f(t3.at<float>(0,0),t3.at<float>(1,0) ,-t3.at<float>(2,0));
       glVertex3f(t2.at<float>(0,0),t2.at<float>(1,0) ,-t2.at<float>(2,0));
       glVertex3f(t1.at<float>(0,0),t1.at<float>(1,0) ,-t1.at<float>(2,0));
       glVertex3f(t0.at<float>(0,0),t0.at<float>(1,0) ,-t0.at<float>(2,0));
       // glVertex3f(3.0f, 3.0f,3.0f);//ending point of the line
       glEnd();
       //glutSolidTeapot(0.01);
       glPopMatrix();
       
       // glPushMatrix();
       // glLoadIdentity();
       // glColor3f(1,0,0);
       // //glRasterPos3f( 0, 0, 0 );
       
       // //      glRotatef(90,0.0f,0.0f,1.0f);
       // // glTranslatef(t2.at<float>(0,0),t2.at<float>(1,0),-t2.at<float>(2,0));
       //  glTranslatef(0,0,-t2.at<float>(2,0));
       
       
       // glutSolidTeapot(0.05);
       // glPopMatrix();

       
       drawSideText(t3,t2);
       drawSideText(t0,t3);
       drawSideText(t0,t1);
       drawSideText(t1,t2);
       drawSideTextArea(t0,t2,ap[0]);  
       
    }
    else if (centers.size() == 3){

      glColor3f(1,1,0);
      //glTranslatef(centers[0].x,0.0f,centers[0].y);
      glPushMatrix();
      glLoadIdentity();
      //    glTranslatef(0, TheMarkerSize/2,0);
       glBegin(GL_TRIANGLES);
      // //origin of the line
      // cout<<"The Marker Size:"<<TheMarkerSize<<endl;
      // //      glVertex3f(TheMarkerSize/2, TheMarkerSize/2,TheMarkerSize/2);//ending point of the line
       cv::Mat t0 = TheMarkers[0].Tvec;
       cv::Mat t1 = TheMarkers[1].Tvec;
       cv::Mat t2 = TheMarkers[2].Tvec;
       //       cv::Mat t3 = TheMarkers[3].Tvec;
       glVertex3f(t0.at<float>(0,0),t0.at<float>(1,0) ,-t0.at<float>(2,0));
       glVertex3f(t2.at<float>(0,0),t2.at<float>(1,0) ,-t2.at<float>(2,0));
       glVertex3f(t1.at<float>(0,0),t1.at<float>(1,0) ,-t1.at<float>(2,0));
       //glVertex3f(t0.at<float>(0,0),t0.at<float>(1,0) ,-t0.at<float>(2,0));
       // glVertex3f(3.0f, 3.0f,3.0f);//ending point of the line
       glEnd();
       //glutSolidTeapot(0.01);
       glPopMatrix();
       
       // glPushMatrix();
       // glLoadIdentity();
       // glColor3f(1,0,0);
       // //glRasterPos3f( 0, 0, 0 );
       
       // //      glRotatef(90,0.0f,0.0f,1.0f);
       // // glTranslatef(t2.at<float>(0,0),t2.at<float>(1,0),-t2.at<float>(2,0));
       //  glTranslatef(0,0,-t2.at<float>(2,0));
       
       
       // glutSolidTeapot(0.05);
       // glPopMatrix();

       
       drawSideText(t0,t1);
       drawSideText(t1,t2);
       //drawSideText(t0,t2);
       drawSideTextArea(t0,t2,ap[0]);  
      
    }

    else if (centers.size() == 2){

      glColor3f(1,1,0);
      //glTranslatef(centers[0].x,0.0f,centers[0].y);
      glPushMatrix();
      glLoadIdentity();
      //    glTranslatef(0, TheMarkerSize/2,0);
       glBegin(GL_LINES);
      // //origin of the line
      // cout<<"The Marker Size:"<<TheMarkerSize<<endl;
      // //      glVertex3f(TheMarkerSize/2, TheMarkerSize/2,TheMarkerSize/2);//ending point of the line
       cv::Mat t0 = TheMarkers[0].Tvec;
       cv::Mat t1 = TheMarkers[1].Tvec;
       //       cv::Mat t3 = TheMarkers[3].Tvec;
       glVertex3f(t0.at<float>(0,0),t0.at<float>(1,0) ,-t0.at<float>(2,0));
       glVertex3f(t1.at<float>(0,0),t1.at<float>(1,0) ,-t1.at<float>(2,0));
       //glVertex3f(t0.at<float>(0,0),t0.at<float>(1,0) ,-t0.at<float>(2,0));
       // glVertex3f(3.0f, 3.0f,3.0f);//ending point of the line
       glEnd();
       //glutSolidTeapot(0.01);
       glPopMatrix();
       
       // glPushMatrix();
       // glLoadIdentity();
       // glColor3f(1,0,0);
       // //glRasterPos3f( 0, 0, 0 );
       
       // //      glRotatef(90,0.0f,0.0f,1.0f);
       // // glTranslatef(t2.at<float>(0,0),t2.at<float>(1,0),-t2.at<float>(2,0));
       //  glTranslatef(0,0,-t2.at<float>(2,0));
       
       
       // glutSolidTeapot(0.05);
       // glPopMatrix();

       
       drawSideText(t0,t1);
       //       drawSideTextArea(t0,t2,ap[0]);  
      
    }

    
    
      // }
    //    glPopMatrix();

     




    glutSwapBuffers();

}



/************************************
 *
 *
 *
 *
 ************************************/
void vIdle()
{
    if (TheCaptureFlag) {
        //capture image
        TheVideoCapturer.grab();
        TheVideoCapturer.retrieve( TheInputImage);
        TheUndInputImage.create(TheInputImage.size(),CV_8UC3);
        //transform color that by default is BGR to RGB because windows systems do not allow reading BGR images with opengl properly
        cv::cvtColor(TheInputImage,TheInputImage,CV_BGR2RGB);
        //remove distorion in image
        cv::undistort(TheInputImage,TheUndInputImage, TheCameraParams.CameraMatrix, TheCameraParams.Distorsion);
        //detect markers
        PPDetector.detect(TheUndInputImage,TheMarkers, TheCameraParams.CameraMatrix,Mat(),TheMarkerSize);
        //resize the image to the size of the GL window
        cv::resize(TheUndInputImage,TheResizedImage,TheGlWindowSize);
    }
    glutPostRedisplay();
}


/************************************
 *
 *
 *
 *
 ************************************/
void vResize( GLsizei iWidth, GLsizei iHeight )
{
    TheGlWindowSize=Size(iWidth,iHeight);
    //not all sizes are allowed. OpenCv images have padding at the end of each line in these that are not aligned to 4 bytes
    if (iWidth*3%4!=0) {
        iWidth+=iWidth*3%4;//resize to avoid padding
        vResize(iWidth,TheGlWindowSize.height);
    }
    else {
        //resize the image to the size of the GL window
        if (TheUndInputImage.rows!=0)
            cv::resize(TheUndInputImage,TheResizedImage,TheGlWindowSize);
    }
}

