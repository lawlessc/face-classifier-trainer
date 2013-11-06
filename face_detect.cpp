#include "face_detect.h"


#include <cstdlib>
using namespace cv;
using namespace std;




face_detect::face_detect()
    {


    }










void face_detect::load_haar_facedetect()
{
  
 storage = 0;
 face_detect::cascade = 0;
 face_detect::cascade = (CvHaarClassifierCascade*)cvLoad("haarcascade_frontalface_alt.xml", 0, 0, 0 );
 storage = cvCreateMemStorage(0);


precentChange = 20;
precentChange = precentChange/2;


}


void  face_detect::detect_face( IplImage* img, vector<CvPoint>& vv )
{
    int scale = 1;

    // Create a new image based on the input image
   // IplImage* temp = cvCreateImage( cvSize(img->width/scale,img->height/scale), 8, 3 );

    // Create two points to represent the face locations
    CvPoint pt1, pt2;
    int i;

    // Clear the memory storage which was used before
    cvClearMemStorage( storage );
        vector<CvPoint> testy;
    // Find whether the cascade is loaded, to find the faces. If yes, then:
    if( cascade )
    {

        // There can be more than one face in an image. So create a growable sequence of faces.
        // Detect the objects and store them in the sequence
        CvSeq* faces = cvHaarDetectObjects( img, cascade, storage,
                                            1.1, 2, CV_HAAR_DO_CANNY_PRUNING,
                                            cvSize(40, 40) );

        // Loop the number of faces found.
        for( i = 0; i < (faces ? faces->total : 0); i++ )
        {
           // Create a new rectangle for drawing the face
            CvRect* r = (CvRect*)cvGetSeqElem( faces, i );
 
            pt1.x = r->x;
            pt2.x = r->width;
            pt1.y = r->y;
            pt2.y = r->height;

            // this change is to 
           

            int  wc = (int)    ((precentChange *(pt2.x))/100);
            int  hc = (int)    ((precentChange *(pt2.y))/100);
                              

              pt1.x += wc;
              pt1.y += hc;
//
              pt2.x = pt2.x - (hc*2);
              pt2.y = pt2.y - (wc*2);

                //pt2.y +=  pt2.y/2;
              pt1.y +=  (int) pt2.y/7;

            testy.insert(  testy.end() ,   pt1 );
            testy.insert(  testy.end() ,   pt2 );

            // Draw the rectangle in the input image
            //cvRectangle( img, pt1, pt2, CV_RGB(255,0,0), 3, 8, 0 );

        }
    }


   // cvReleaseImage( &temp );
   return vv.swap(testy);

}



  void face_detect::detect_first_face( IplImage* img, vector<CvPoint>& vv )
  {
    int scale = 1;

   

    // Create two points to represent the face locations
    CvPoint pt1, pt2;
    int i;

    // Clear the memory storage which was used before
    cvClearMemStorage( storage );
        vector<CvPoint> testy;
   
        CvSeq* faces = cvHaarDetectObjects( img, cascade, storage,
                                            1.1, 2, CV_HAAR_DO_CANNY_PRUNING,
                                            cvSize(40, 40) );

        // Loop the number of faces found.
        if(faces->total >=1 )
        {
       // for( i = 0; i < 1; i++ )
       // {
           // Create a new rectangle for drawing the face
            CvRect* r = (CvRect*)cvGetSeqElem( faces, 0 );
 
            pt1.x = r->x;
            pt2.x = r->width;
            pt1.y = r->y;
            pt2.y = r->height;

            // this change is to 
           

            int  wc = (int)    ((precentChange *(pt2.x))/100);
            int  hc = (int)    ((precentChange *(pt2.y))/100);
                              

              pt1.x += wc;
              pt1.y += hc;
//
              pt2.x = pt2.x - (wc*2);
              pt2.y = pt2.y - (hc*2);

              //lowers the image a little to remove top of forehead
              pt1.y +=  pt2.y/7;

            testy.insert(  testy.end() ,   pt1 );
            testy.insert(  testy.end() ,   pt2 );
        //  }
      }

   return vv.swap(testy);

}