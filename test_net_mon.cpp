#include "cv.h"
#include "highgui.h"
#include <stdio.h>


//GTK libraries//////////////////
#include <gtk/gtk.h>
#include <gtk/gtktext.h>

#include <dirent.h>//another library added...
#include <string>

//OPENCV LIBRARIES
//going to need a better way of including all this libreary spam
#ifdef _CH_
#pragma package <opencv>
#endif

#ifndef _EiC
#include <cv.h>
#include <highgui.h>
#include <stdio.h>
#include <ctype.h>
#include <ml.h>

#include "frame_manager.cpp"

#endif




int main(int argc, char* argv[])
{
//IplImage *img1 = cvLoadImage("test1.jpg", 1);
//CvCapture *capture = cvCaptureFromFile( "wtf.mp4" );
int mode = atoi (argv[1]);//1 is test mode, 2 is expression mode
int number_of_camera = atoi (argv[2]);

frame_manager t1;
t1= frame_manager();
t1.add_feeds(number_of_camera);
t1.load_face_detect();
//t1.load_test_net();

if(mode == 1)
{

  t1.set_mode(mode);
  t1.load_network(t1.test_net ,argv[3] );


}

if(mode == 2)
{
  t1.set_mode(mode);
  
  t1.load_smiling(argv[3]);
  t1.load_fear(argv[4]);
  t1.load_sadness(argv[5]);
  t1.load_disgust(argv[6]);
  t1.load_anger(argv[7]);
  t1.load_surprise(argv[8]);



}
//t1.load_haar_facedetect();
//CvCapture *capture = cvCaptureFromCAM( 0 );
//IplImage* frame;
int       key;
//int fps = ( int )cvGetCaptureProperty( capture, CV_CAP_PROP_FPS );



bool begin = false;


while(  key != 'q' )
 {

          if( key == 't')
          {
         
            begin = true;
          }
           if(begin == true)
           {
        
           t1.loop(true);

           }
           else
           {
            t1.loop(false);

           }

     //   key = cvWaitKey( 1000/fps  );
          key = cvWaitKey( 1 );
    }



  cvDestroyAllWindows();
  

  return 0;

}



//This is a modified version of the detect and draw function from
