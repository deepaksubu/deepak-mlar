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
void vKeyboard(unsigned char key,int x,int y);

//void lineMode(cv::<Point2f> center);

//Enumeration for modes
enum Mode{
  Free,
  Triangle,
  Grid,
  Line,
  Line2
};

bool imperialUnitFlag = false;
bool xflag = false;
float M2CM = 100.0f;
float M2IN = 39.3700787f;

Mode mode;

void init(){
  mode = Free;
}

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
        if (TheInputVideo=="live") TheVideoCapturer.open(1);
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
	init();
        glutInit(&argc, argv);
        glutInitWindowPosition( 0, 0);
        glutInitWindowSize(TheInputImage.size().width,TheInputImage.size().height);
        glutInitDisplayMode( GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE );
        glutCreateWindow( "AruCo" );

        glutDisplayFunc( vDrawScene );
        glutIdleFunc( vIdle );
        glutReshapeFunc( vResize );
        //glutMouseFunc(vMouse);
	glutKeyboardFunc(vKeyboard);
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
 *Mode Selection using Keyboard
 *
 *
 *
 ************************************/
void vKeyboard(unsigned char key,int x,int y){
  if (key == 't'){
    mode = Triangle;
    cout << "I am in the triangle exploration mode" << endl;
  } else if (key == 'g'){
    mode = Grid;
    cout << "I am in the grid mode" << endl;
  } else if (key == 'l'){
    mode = Line;
    cout << "I am in the line mode" << endl;
  } else if (key == 'x'){
    mode = Line2;
    xflag = !xflag;
    cout << "I am in the line mode2" << endl;
    //glutPostRedisplay();
  } 
  else if (key == 'u'){
    imperialUnitFlag = !imperialUnitFlag;
  } 
  else {
    mode = Free;
    cout << "I am in the default free mode" << endl;
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

void convertDistance(float *distance){
  *distance = imperialUnitFlag?(M2IN**distance):(M2CM**distance);
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

  //metric or imperial
  convertDistance(&distance);
    
  return distance;
  
}

float calculateArea(){
  float area = 0;

  
  cv::Mat t0 = TheMarkers[0].Tvec;
  cv::Mat t1 = TheMarkers[1].Tvec;
  cv::Mat t2 = TheMarkers[2].Tvec;
		


  int sz =  TheMarkers.size();

  //If the input is a square  
  if (TheMarkers.size() == 4) {
    float length = calculateDistance(t0,t1);
    float width = calculateDistance(t1,t2);
    area = length * width;
    //float perimeter = 2*length + 2*width;
    //ap[0] = area;
  }
  //The input is a triangle
  else if (TheMarkers.size() == 3){
    
    float side1 = calculateDistance(t0,t1);
    float side2 = calculateDistance(t1,t2);
    float side3 = calculateDistance(t0,t2);
    float perimeter = side1 + side2 + side3;
    float s = perimeter / 2;
    area = sqrt(s * (s - side1) * (s - side2) * (s - side3));
        
  }
  
  return area;
  
}

void drawString(char* string){

  char *c;
  for (c=string; *c != '\0'; c++) 
    {
      glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *c);
    }
 
}



void drawX(cv::Mat t3,cv::Mat t2){
    
  float s = calculateDistance(t3,t2);
  char buffer[50];
  int n = sprintf(buffer,"X\n");

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
  cout << "I am in the X of line mode2"<<endl;
  
}

void drawSideText(cv::Mat t3,cv::Mat t2){
    
  float s = calculateDistance(t3,t2);
  char buffer[50];
  int n = sprintf(buffer,"%.0f\n",floor(s+0.5));

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

void drawSideTextTranslate(cv::Mat t3,cv::Mat t2, float unit){
    
  float s = calculateDistance(t3,t2);
  char buffer[50];
  int n = sprintf(buffer,"%.0f\n",floor(s+0.5));

  float x_bmid = (t3.at<float>(0,0) + t2.at<float>(0,0))/2;
  float y_bmid = (t3.at<float>(1,0) + t2.at<float>(1,0))/2;
  float z_bmid = (-t3.at<float>(2,0) - t2.at<float>(2,0))/2;

  glPushMatrix();
  glColor3f(0,0,1);
  
  
  glLoadIdentity();
  glTranslatef(x_bmid,y_bmid + unit,z_bmid);
  glRasterPos3f( 0.0f, 0.0f, 0.0f );
  drawString(buffer);
  glPopMatrix();
  
}


void drawArea(vector<cv::Point2f> centers){
    

  float area = calculateArea();
  char buffer[50];
  int n = sprintf(buffer,"Area = %4.0f\n",floor(area+0.5));

  float x_area = 0;
  float y_area = 0;
  float z_area = 0;

  float xtranslateArea = -4*0.015;

  float ytranslateArea = 2.5*0.015;
  
  if (centers.size() == 4){

    cv::Mat t0 = TheMarkers[0].Tvec;
    cv::Mat t1 = TheMarkers[1].Tvec;
    cv::Mat t2 = TheMarkers[2].Tvec;
    cv::Mat t3 = TheMarkers[3].Tvec;

    x_area = t0.at<float>(0,0) + xtranslateArea;
    y_area = t0.at<float>(1,0) - ytranslateArea;
    z_area = -t0.at<float>(2,0);
  
  } else if (centers.size() == 3){
    
    cv::Mat t0 = TheMarkers[0].Tvec;
    cv::Mat t1 = TheMarkers[1].Tvec;
    cv::Mat t2 = TheMarkers[2].Tvec;

    x_area = t0.at<float>(0,0) + xtranslateArea;;
    y_area = t0.at<float>(1,0) - ytranslateArea;;
    z_area = -t0.at<float>(2,0);

  }

  
  glPushMatrix();
  glColor3f(0,0,1);
  
  glLoadIdentity();
  glTranslatef(x_area,y_area,z_area);
  glRasterPos3f( 0.0f, 0.0f, 0.0f);
  drawString(buffer);
  glPopMatrix();
  
}

void triangleMode(vector<cv::Point2f> centers){
  float length = 0;
  float height = 0;
  
  
  if (centers.size() == 3){
    cv::Mat t0 = TheMarkers[0].Tvec;
    cv::Mat t1 = TheMarkers[1].Tvec;
    cv::Mat t2 = TheMarkers[2].Tvec;
    
    length = calculateDistance(t2,t1);
    height = calculateDistance(t0,t2);

    glColor3f(1,1,0);
    glPushMatrix();
    glLoadIdentity();
    
    glBegin(GL_TRIANGLES);
    glVertex3f(t0.at<float>(0,0),t0.at<float>(1,0) ,-t0.at<float>(2,0));
    glVertex3f(t2.at<float>(0,0),t2.at<float>(1,0) ,-t2.at<float>(2,0));
    glVertex3f(t1.at<float>(0,0),t1.at<float>(1,0) ,-t1.at<float>(2,0));
    glEnd();

    glColor3f(0,1,1);
    
    glBegin(GL_TRIANGLES);
    glVertex3f(t0.at<float>(0,0),t0.at<float>(1,0) ,-t0.at<float>(2,0));
    glVertex3f(t1.at<float>(0,0),t1.at<float>(1,0) ,-t1.at<float>(2,0));
    glVertex3f(t2.at<float>(0,0) + length,t2.at<float>(1,0) - height ,-t2.at<float>(2,0));
   
    glEnd();

    glPopMatrix();
    
    drawSideText(t0,t1);
    drawSideText(t1,t2);
    drawSideText(t0,t2);
    drawArea(centers);  

  }
}


void lineMode(vector<cv::Point2f> centers){
  
  float translateDistance = -0.055;
  float lineWidth = 2;
  
  if (centers.size() == 3){
    cv::Mat t0 = TheMarkers[0].Tvec;
    cv::Mat t1 = TheMarkers[1].Tvec;
    cv::Mat t2 = TheMarkers[2].Tvec;

    glPushMatrix();
    glLoadIdentity();
    glColor3f(1,1,0);
    glLineWidth(lineWidth);
    glBegin(GL_LINES);
    
    glVertex3f(t0.at<float>(0,0),t0.at<float>(1,0) ,-t0.at<float>(2,0));
    glVertex3f(t1.at<float>(0,0),t1.at<float>(1,0) ,-t1.at<float>(2,0));

    glVertex3f(t1.at<float>(0,0),t1.at<float>(1,0) ,-t1.at<float>(2,0));
    glVertex3f(t2.at<float>(0,0),t2.at<float>(1,0) ,-t2.at<float>(2,0));

    glEnd();
    
    glTranslatef(0.0f,translateDistance,0.0f);
    
    glBegin(GL_LINES);
    glVertex3f(t0.at<float>(0,0),t0.at<float>(1,0) ,-t0.at<float>(2,0));
    glVertex3f(t2.at<float>(0,0),t2.at<float>(1,0) ,-t2.at<float>(2,0));
    glEnd();

    glPopMatrix();
    
    
    drawSideText(t0,t1);
    drawSideText(t1,t2);
    drawSideTextTranslate(t0,t2,translateDistance);
    
  }
  
}

void lineMode2(vector<cv::Point2f> centers){
  
  float translateDistance = -0.055;
  float lineWidth = 2;
  
  if (centers.size() == 3){
    cv::Mat t0 = TheMarkers[0].Tvec;
    cv::Mat t1 = TheMarkers[1].Tvec;
    cv::Mat t2 = TheMarkers[2].Tvec;

    glPushMatrix();
    glLoadIdentity();
    glColor3f(1,1,0);
    glLineWidth(lineWidth);
    glBegin(GL_LINES);
    
    glVertex3f(t0.at<float>(0,0),t0.at<float>(1,0) ,-t0.at<float>(2,0));
    glVertex3f(t1.at<float>(0,0),t1.at<float>(1,0) ,-t1.at<float>(2,0));

    glVertex3f(t1.at<float>(0,0),t1.at<float>(1,0) ,-t1.at<float>(2,0));
    glVertex3f(t2.at<float>(0,0),t2.at<float>(1,0) ,-t2.at<float>(2,0));

    glEnd();
    
    glTranslatef(0.0f,translateDistance,0.0f);
    
    glBegin(GL_LINES);
    glVertex3f(t0.at<float>(0,0),t0.at<float>(1,0) ,-t0.at<float>(2,0));
    glVertex3f(t2.at<float>(0,0),t2.at<float>(1,0) ,-t2.at<float>(2,0));
    glEnd();

    glPopMatrix();
    
    
    drawSideText(t0,t1);
    
    if (xflag){
      drawX(t1,t2);
    } else {
      drawSideText(t1,t2);
    }
    
    drawSideTextTranslate(t0,t2,translateDistance);
    
  }
  
}

void gridMode(vector<cv::Point2f> centers){
  float ap;
 

  if (centers.size() == 4){
  
    cv::Mat t0 = TheMarkers[0].Tvec;
    cv::Mat t1 = TheMarkers[1].Tvec;
    cv::Mat t2 = TheMarkers[2].Tvec;
    cv::Mat t3 = TheMarkers[3].Tvec;

    GLfloat grid2x2[12] = {
      t0.at<float>(0,0), t0.at<float>(1,0), -t0.at<float>(2,0), t1.at<float>(0,0), t1.at<float>(1,0), -t1.at<float>(2,0),
      t3.at<float>(0,0), t3.at<float>(1,0), -t3.at<float>(2,0), t2.at<float>(0,0), t2.at<float>(1,0), -t2.at<float>(2,0)
    };
    
    glPushMatrix();
    glLoadIdentity();
    glColor3f(1,0,0);

    float unit = 0.005;

    glEnable(GL_MAP2_VERTEX_3);
    glMap2f(GL_MAP2_VERTEX_3,
	    0.0, 1.0,  /* U ranges 0..1 */
	    3,         /* U stride, 3 floats per coord */
	    2,         /* U is 2nd order, ie. linear */
	    0.0, 1.0,  /* V ranges 0..1 */
	    2 * 3,     /* V stride, row is 2 coords, 3 floats per coord */
	    2,         /* V is 2nd order, ie linear */
	    grid2x2);  /* control points */


    
    int rows = ceil (abs(t0.at<float>(1,0) - t3.at<float>(1,0))/unit);
    int columns = ceil (abs(t0.at<float>(0,0) - t1.at<float>(0,0))/unit);
 
    glMapGrid2f(rows, 0.0, 1.0,
		columns, 0.0, 1.0);
   
    glEvalMesh2(GL_LINE,
	      0, rows,   /* Starting at 0 mesh 5 steps (rows). */
	      0, columns);  /* Starting at 0 mesh 6 steps (columns). */
    
    glPopMatrix();

    drawSideText(t3,t2);
    drawSideText(t0,t3);
    drawSideText(t0,t1);
    drawSideText(t1,t2);
    drawArea(centers);
    
  } else if (centers.size() == 3){

   
    cv::Mat t0 = TheMarkers[0].Tvec;
    cv::Mat t1 = TheMarkers[1].Tvec;
    cv::Mat t2 = TheMarkers[2].Tvec;
    

    GLfloat grid2x2[12] = {
      t0.at<float>(0,0), t0.at<float>(1,0), -t0.at<float>(2,0), t1.at<float>(0,0), t1.at<float>(1,0), -t1.at<float>(2,0),
      t2.at<float>(0,0), t2.at<float>(1,0), -t2.at<float>(2,0), t2.at<float>(0,0), t2.at<float>(1,0), -t2.at<float>(2,0)
    };
    
    glPushMatrix();
    glLoadIdentity();
    glColor3f(1,0,0);

    float unit = 0.005;

    glEnable(GL_MAP2_VERTEX_3);
    glMap2f(GL_MAP2_VERTEX_3,
	    0.0, 1.0,  /* U ranges 0..1 */
	    3,         /* U stride, 3 floats per coord */
	    2,         /* U is 2nd order, ie. linear */
	    0.0, 1.0,  /* V ranges 0..1 */
	    2 * 3,     /* V stride, row is 2 coords, 3 floats per coord */
	    2,         /* V is 2nd order, ie linear */
	    grid2x2);  /* control points */


    
    int rows = ceil (abs(t1.at<float>(1,0) - t2.at<float>(1,0))/unit);
    int columns = ceil (abs(t0.at<float>(0,0) - t1.at<float>(0,0))/unit);
 
    glMapGrid2f(rows, 0.0, 1.0,
		columns, 0.0, 1.0);
   
    glEvalMesh2(GL_LINE,
	      0, rows,   /* Starting at 0 mesh 5 steps (rows). */
	      0, columns);  /* Starting at 0 mesh 6 steps (columns). */
    
    glPopMatrix();
    
    drawSideText(t0,t1);
    drawSideText(t1,t2);
    drawSideText(t0,t2);
    drawArea(centers);
      
    
  }

  
}

void freeMode(vector<cv::Point2f> centers){
  
    float ap = 0;
   

    if (centers.size() == 4){
 
      glColor3f(1,1,0);
      glPushMatrix();
      glLoadIdentity();
      glBegin(GL_QUADS);
      cv::Mat t0 = TheMarkers[0].Tvec;
      cv::Mat t1 = TheMarkers[1].Tvec;
      cv::Mat t2 = TheMarkers[2].Tvec;
      cv::Mat t3 = TheMarkers[3].Tvec;
      glVertex3f(t3.at<float>(0,0),t3.at<float>(1,0) ,-t3.at<float>(2,0));
      glVertex3f(t2.at<float>(0,0),t2.at<float>(1,0) ,-t2.at<float>(2,0));
      glVertex3f(t1.at<float>(0,0),t1.at<float>(1,0) ,-t1.at<float>(2,0));
      glVertex3f(t0.at<float>(0,0),t0.at<float>(1,0) ,-t0.at<float>(2,0));
       
      glEnd();
      glPopMatrix();
      
      drawSideText(t3,t2);
      drawSideText(t0,t3);
      drawSideText(t0,t1);
      drawSideText(t1,t2);
      drawArea(centers);  
      
    }
    else if (centers.size() == 3){
   
      glColor3f(1,1,0);
      glPushMatrix();
      glLoadIdentity();
       glBegin(GL_TRIANGLES);
       cv::Mat t0 = TheMarkers[0].Tvec;
       cv::Mat t1 = TheMarkers[1].Tvec;
       cv::Mat t2 = TheMarkers[2].Tvec;
       glVertex3f(t0.at<float>(0,0),t0.at<float>(1,0) ,-t0.at<float>(2,0));
       glVertex3f(t2.at<float>(0,0),t2.at<float>(1,0) ,-t2.at<float>(2,0));
       glVertex3f(t1.at<float>(0,0),t1.at<float>(1,0) ,-t1.at<float>(2,0));
       glEnd();
       glPopMatrix();
       
       drawSideText(t0,t1);
       drawSideText(t1,t2);
       drawSideText(t0,t2);
       drawArea(centers);
       
      
    }

    else if (centers.size() == 2){

      glColor3f(1,1,0);
      glPushMatrix();
      glLoadIdentity();
      glBegin(GL_LINES);
      cv::Mat t0 = TheMarkers[0].Tvec;
      cv::Mat t1 = TheMarkers[1].Tvec;
      glVertex3f(t0.at<float>(0,0),t0.at<float>(1,0) ,-t0.at<float>(2,0));
      glVertex3f(t1.at<float>(0,0),t1.at<float>(1,0) ,-t1.at<float>(2,0));
      glEnd();
      glPopMatrix();
      drawSideText(t0,t1);
      
    }

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
	
	// TheMarkers[m].glGetModelViewMatrix(modelview_matrix);
	// glLoadIdentity();
	// glLoadMatrixd(modelview_matrix);
	// axis(TheMarkerSize);
	// glColor3f(1,0.4,0.4);
	// glTranslatef(0, TheMarkerSize/2,0);
	// glPushMatrix();
	// glutWireCube( TheMarkerSize );
	// glPopMatrix();

      }
    
    char textString[100] = "Free Mode";
    char unitString[100] = "Metric Units";
     if ( mode == Free){
      
      freeMode(centers);
      int a = sprintf(textString,"%s","Free Mode");

    } else if (mode == Triangle){

      triangleMode(centers);
      int a = sprintf(textString,"%s","Triangle Exploration Mode");
   

    } else if (mode == Grid){

     
 int a = sprintf(textString,"%s","Grid Mode");
      gridMode(centers);

    } else if (mode == Line){
       int a = sprintf(textString,"%s","Line Mode");
       lineMode(centers);

    } else if (mode == Line2){
       int a = sprintf(textString,"%s","Line Mode2");
       lineMode2(centers);
     }

    
     int m =sprintf(unitString,"%s",imperialUnitFlag?"Imperial Units":"Metric Units");
    
    if (centers.size() > 0){
    cv::Mat t0 = TheMarkers[0].Tvec;
    float xTranslate = -0.1f;
    float yTranslate = -0.1f;
    glPushMatrix();
    glLoadIdentity();
    glColor4f(1.0f,0.0f,0.0f,0.5f);
    glTranslatef(t0.at<float>(0,0) + xTranslate,t0.at<float>(1,0)+yTranslate,-t0.at<float>(2,0));
    glRasterPos3f( 0.0f,0.0f,0.0f );
    char buffer[100];
    int n = sprintf(buffer,"%s \n%s",textString,unitString);
    drawString(buffer);
    glPopMatrix();  
    }

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

