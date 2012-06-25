# ===================================================================================
#  aruco CMake configuration file
#
#             ** File generated automatically, do not modify **
#
#  Usage from an external project:
#    In your CMakeLists.txt, add these lines:
#
#    FIND_PACKAGE(aruco REQUIRED )
#    TARGET_LINK_LIBRARIES(MY_TARGET_NAME )
#
#    This file will define the following variables:
#      - aruco_LIBS          : The list of libraries to links against.
#      - aruco_LIB_DIR       : The directory where lib files are. Calling LINK_DIRECTORIES
#                                with this path is NOT needed.
#      - aruco_VERSION       : The  version of this PROJECT_NAME build. Example: "1.2.0"
#      - aruco_VERSION_MAJOR : Major version part of VERSION. Example: "1"
#      - aruco_VERSION_MINOR : Minor version part of VERSION. Example: "2"
#      - aruco_VERSION_PATCH : Patch version part of VERSION. Example: "0"
#
# ===================================================================================
INCLUDE_DIRECTORIES()
SET(aruco_INCLUDE_DIRS )

LINK_DIRECTORIES("/usr/local/lib")
#SET(aruco_LIB_DIR "")

SET(aruco_LIBS debug;/home/deepak/development/opencv/lib/libopencv_calib3d.so;debug;/home/deepak/development/opencv/lib/libopencv_contrib.so;debug;/home/deepak/development/opencv/lib/libopencv_core.so;debug;/home/deepak/development/opencv/lib/libopencv_features2d.so;debug;/home/deepak/development/opencv/lib/libopencv_flann.so;debug;/home/deepak/development/opencv/lib/libopencv_gpu.so;debug;/home/deepak/development/opencv/lib/libopencv_highgui.so;debug;/home/deepak/development/opencv/lib/libopencv_imgproc.so;debug;/home/deepak/development/opencv/lib/libopencv_legacy.so;debug;/home/deepak/development/opencv/lib/libopencv_ml.so;debug;/home/deepak/development/opencv/lib/libopencv_nonfree.so;debug;/home/deepak/development/opencv/lib/libopencv_objdetect.so;debug;/home/deepak/development/opencv/lib/libopencv_photo.so;debug;/home/deepak/development/opencv/lib/libopencv_stitching.so;debug;/home/deepak/development/opencv/lib/libopencv_ts.so;debug;/home/deepak/development/opencv/lib/libopencv_video.so;debug;/home/deepak/development/opencv/lib/libopencv_videostab.so;optimized;/home/deepak/development/opencv/lib/libopencv_calib3d.so;optimized;/home/deepak/development/opencv/lib/libopencv_contrib.so;optimized;/home/deepak/development/opencv/lib/libopencv_core.so;optimized;/home/deepak/development/opencv/lib/libopencv_features2d.so;optimized;/home/deepak/development/opencv/lib/libopencv_flann.so;optimized;/home/deepak/development/opencv/lib/libopencv_gpu.so;optimized;/home/deepak/development/opencv/lib/libopencv_highgui.so;optimized;/home/deepak/development/opencv/lib/libopencv_imgproc.so;optimized;/home/deepak/development/opencv/lib/libopencv_legacy.so;optimized;/home/deepak/development/opencv/lib/libopencv_ml.so;optimized;/home/deepak/development/opencv/lib/libopencv_nonfree.so;optimized;/home/deepak/development/opencv/lib/libopencv_objdetect.so;optimized;/home/deepak/development/opencv/lib/libopencv_photo.so;optimized;/home/deepak/development/opencv/lib/libopencv_stitching.so;optimized;/home/deepak/development/opencv/lib/libopencv_ts.so;optimized;/home/deepak/development/opencv/lib/libopencv_video.so;optimized;/home/deepak/development/opencv/lib/libopencv_videostab.so aruco) 

SET(aruco_FOUND YES)
SET(aruco_FOUND "YES")
SET(aruco_VERSION        1.2.2)
SET(aruco_VERSION_MAJOR  1)
SET(aruco_VERSION_MINOR  2)
SET(aruco_VERSION_PATCH  2)
