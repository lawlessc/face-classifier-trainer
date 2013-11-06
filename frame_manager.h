
#ifdef _CH_
#pragma package <opencv>
#endif

#ifndef _EiC
#include <cv.h>
#include <highgui.h>
#include <ml.h>
#include <stdio.h>
#include <ctype.h>


//#include <stdlib.h>
#include <cstdlib>

#include "neuralTest.cpp"
//#include "face_detect.cpp"
#include <time.h>
#include <vector>
#include <dirent.h>

#endif



using namespace std;
using namespace cv;






class frame_manager{



    public:

    frame_manager();
    void set_frame_size_to_default();

    int mode;
    void set_mode(int mode_);


    //IplImage* frame;

    
    int f1,f2;
    int res1,res2;
   // int moveRate;
     

     vector<IplImage*> frames;
   // vector<neuralTest> neural_nets;

    char *unclassified_image_address;
    vector<CvCapture*> feeds;
    //= cvCaptureFromCAM( 0 );

     
     string window_name;
  //window_name = "Face:" ;
     string fromfeed;
     string result;
  //fromfeed    = "camera:";

    neuralTest  smiling;
       void  load_smiling(string file_address);
    neuralTest  fear;
       void  load_fear(string file_address);
    neuralTest  sadness;
       void  load_sadness(string file_address);
    neuralTest  disgust;
       void  load_disgust(string file_address);
    neuralTest  anger;
       void  load_anger(string file_address);
    neuralTest  surprise;
       void  load_surprise(string file_address);

 
    neuralTest test_net;

   
    //void  load_test_net();


    void load_network(neuralTest& net_to_load,string file_address );

    void add_feeds(int n);

   




    face_detect  face_detector;
    void load_face_detect();

    



  //   void receive_frame(IplImage* image);

   //  void get_regions();

     //void set_frame_size(cvRect fsize);




     
     void add_NNetwork(string directory);
     //void add_NNetwork_face_detect(string directory);
     void hightlight_region_selected(IplImage* image);
     void get_region_selected(IplImage* image);




    // void mloop(IplImage* frame);
      void loop(bool usefd);
      void mloop(IplImage* frame , int feed_no);


//void move_ROI_UP();
///void move_ROI_DOWN();
//void move_ROI_LEFT();
//void move_ROI_RIGHT();

     
     void  process_image_test(IplImage* image);
     
     IplImage* expression_image_test(IplImage* image,vector<CvPoint>& vv );
     IplImage* process_image(IplImage* image);
     IplImage* process_image_test(IplImage* image,vector<CvPoint>& vv );
     float use_network();


     void  store_unclassified_image(IplImage* image);
 







	private:

};
