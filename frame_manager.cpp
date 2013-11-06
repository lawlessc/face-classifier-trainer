#include "frame_manager.h"


#include <cstdlib>
using namespace cv;
using namespace std;




frame_manager::frame_manager()
    {
       
       unclassified_image_address ="./failed_classify";


     //string window_name;
  window_name = "Face:" ;
    // string fromfeed;
  fromfeed    = "camera:";

  set_frame_size_to_default();
    }


void frame_manager::set_frame_size_to_default()
     {
      f1 =0;
      f2 =0;
      res1 = 256;
      res2 = 256;
     

     }



   
    void frame_manager::set_mode(int mode_)
    {


    mode= mode_;
    }





       //neuralTest  smiling;
       void  frame_manager::load_smiling(string file_address)
       {
         load_network(smiling,file_address);
       }
  //  neuralTest  fear;
       void  frame_manager::load_fear(string file_address)
         {
         load_network(fear,file_address);
         }
   // neuralTest  sadness;
       void  frame_manager::load_sadness(string file_address)
         {
         load_network(sadness,file_address);
       }
   // neuralTest  disgust;
       void  frame_manager::load_disgust(string file_address)
         {
         load_network(disgust,file_address);
       }
   // neuralTest  anger;
       void  frame_manager::load_anger(string file_address)
         {
         load_network(anger,file_address);
       }
    //neuralTest  surprise;
       void  frame_manager::load_surprise(string file_address)
         {
         load_network(surprise,file_address);
       }





//void frame_manager::load_test_net()
//{
  //load_network(test_net,"./bw");
//}


 
void frame_manager::load_face_detect()
{

  face_detector = face_detect();
  face_detector.load_haar_facedetect();
  

}

void frame_manager::load_network(neuralTest& net_to_load,string file_address )
{


  net_to_load = neuralTest();

  net_to_load .load_network(file_address);
  
}


void frame_manager::add_NNetwork(string directory)
{


}



//run when starting monitor mode ,adds selected number of feeds
void frame_manager::add_feeds(int n)
{
   feeds.clear();
 for(int i = 0 ; i < n ; i++)
 {

  // CvCapture *cam = cvCaptureFromCAM( i );
 // cvCreateCameraCapture( int index );
 
  feeds.insert( feeds.end() , cvCreateCameraCapture( i )  );
  
 }


}




void frame_manager::process_image_test(IplImage* image)
{
IplImage *dst = cvCreateImage( cvSize( image->width, image->height ), IPL_DEPTH_8U, 1 );
 cvConvertImage(image,dst,0);
}

IplImage* frame_manager::process_image(IplImage* image)
{

cvSetImageROI(image, cvRect(f1,f2, res1, res2));
IplImage *roi = cvCreateImage( cvSize(res1, res2 ), image->depth, image->nChannels );

cvCopy(image,roi, NULL);

IplImage *dst = cvCreateImage( cvSize( roi->width, roi->height ), IPL_DEPTH_8U, 1 );

cvConvertImage(roi,dst,0);

float x = test_net.test_image(dst);

 //cout << "size: " << face_detect_net.getImageVectorSIZE(dst);

 cvResetImageROI(image);
return dst;
}



IplImage* frame_manager::expression_image_test(IplImage* image,vector<CvPoint>& vv )
 {
cvSetImageROI(image, cvRect(   vv[0].x   ,   vv[0].y   , vv[1].x    ,    vv[1].y )  );
IplImage *roi = cvCreateImage( cvSize( vv[1].x  , vv[1].y ),  IPL_DEPTH_8U, 1 );
cvConvertImage(image,roi,0);
//This piece of code just keeps all face images being returned to a window 1 size
//its use is cosmetic as having a window change size constantly is annoying
IplImage *dst = cvCreateImage( cvSize( res1, res2 ), IPL_DEPTH_8U, 1 );
cvResize(roi, dst,1);

string result;
stringstream wn;
//bool x = test_net.test_image_bool(roi);
     if(smiling.test_image_bool(roi) == true)
     {

      wn << "Smile" ;//<< x;
     }
     else if(fear.test_image_bool(roi)  == true )
     {
 
         wn << "Fear";// << x;
     }
     else if(sadness.test_image_bool(roi)  == true )
     {
 
         wn << "Sadness";// << x;
     }
     else if(disgust.test_image_bool(roi)  == true )
     {
 
         wn << "Disgust";// << x;
     }
     else if(anger.test_image_bool(roi)  == true )
     {
 
         wn << "Anger" ;//<< x;
     }
     else if(surprise.test_image_bool(roi)  == true )
     {
 
         wn << "Surprise" ;//<< x;
     }
     else
     {
            wn << "Unknown" ;//<< x;
      store_unclassified_image(roi);
     }


 cvResetImageROI(image);

result = wn.str();


CvFont font;
double hScale=0.8;
double vScale=0.8;
int    lineWidth=2;
cvInitFont(&font,CV_FONT_HERSHEY_SIMPLEX|CV_FONT_ITALIC, hScale,vScale,0,lineWidth);

//cvPutText (img,"My comment",, &font, cvScalar(255,255,0));

// cvPutText(roi,result.c_str(), cvPoint((roi->width)/2,(roi->height)/2), &font, cvScalar(255,255,0));
 cvPutText(dst,result.c_str(), cvPoint((roi->width)/2,(roi->height)/2), &font, cvScalar(255,255,0));

//return roi;
 return dst;
}

IplImage* frame_manager::process_image_test(IplImage* image,vector<CvPoint>& vv )
 {
cvSetImageROI(image, cvRect(   vv[0].x   ,   vv[0].y   , vv[1].x    ,    vv[1].y )  );
IplImage *roi = cvCreateImage( cvSize( vv[1].x  , vv[1].y ),  IPL_DEPTH_8U, 1 );
cvConvertImage(image,roi,0);
//This piece of code just keeps all face images being returned to a window 1 size
//its use is cosmetic as having a window change size constantly is annoying
IplImage *dst = cvCreateImage( cvSize( res1, res2 ), IPL_DEPTH_8U, 1 );
cvResize(roi, dst,1);

bool x = test_net.test_image_bool(roi);



 cvResetImageROI(image);

string result;
stringstream wn;
if(x == true)
{
//wn << "Output:" << x;
wn << "True" ;//<< x;
}
else
{
wn << "False";// << x;
}
result = wn.str();


CvFont font;
double hScale=0.8;
double vScale=0.8;
int    lineWidth=2;
cvInitFont(&font,CV_FONT_HERSHEY_SIMPLEX|CV_FONT_ITALIC, hScale,vScale,0,lineWidth);

//cvPutText (img,"My comment",, &font, cvScalar(255,255,0));

// cvPutText(roi,result.c_str(), cvPoint((roi->width)/2,(roi->height)/2), &font, cvScalar(255,255,0));
 cvPutText(dst,result.c_str(), cvPoint((roi->width)/2,(roi->height)/2), &font, cvScalar(255,255,0));

//return roi;
 return dst;
}

float frame_manager::use_network()
{



return 0.1;
}





void frame_manager::loop(bool usefd)
{
frames.clear();


//gathers images from each frame
  for(int x = 0 ;  x < feeds.size() ; x++)
{
frames.insert( frames.end() , cvQueryFrame( feeds[x] ) );
}


//outputs those images to windows
for (int i = 0 ; i < frames.size() ; i ++)
{
stringstream w;
w << fromfeed << i;
result = w.str();
cvShowImage( result.c_str(),   frames[i] );

if(usefd == true)
{
 mloop(frames[i], i );
}



}



}


void frame_manager::mloop(IplImage* frame , int feed_no)
{
  

  vector<CvPoint> test;

  face_detector.detect_face( frame, test);
  


   for(int i = 0 ; i < test.size() ;i+=2)
   {
   // string result;
   stringstream wn;
   
    wn << window_name << (i+1) <<" " << fromfeed <<feed_no;
    result = wn.str();
    
    vector<CvPoint> current;
  
    current.insert(   current.end() , test[i]);
    current.insert(   current.end() , test[i+1]);
    
    if(mode ==1)
    {cvShowImage( result.c_str(),   process_image_test(frame,current) );}
   if(mode ==2)
    {cvShowImage( result.c_str(),   expression_image_test(frame,current) );}
   }



}





 void  frame_manager::store_unclassified_image(IplImage* image)
   {
          
           

        
    string directory_string;
    directory_string.assign(unclassified_image_address);
    
      
    string systime;
    systime   =   time(NULL);

    string direc = directory_string+"/"+systime+".jpg";

      

       cvSaveImage(direc.c_str() ,image);


   }