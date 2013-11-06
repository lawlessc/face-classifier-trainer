#ifdef _CH_
#pragma package <opencv>
#endif

#ifndef _EiC
#include <cv.h>
#include <highgui.h>
#include <ml.h>
#include <stdio.h>
#include <ctype.h>

#include <vector>

#endif




using namespace std;
using namespace cv;




class face_detect{
	public:

      face_detect();

      CvMemStorage* storage ;
      CvHaarClassifierCascade* cascade;


      
      int precentChange;

      void load_haar_facedetect();
      void detect_face( IplImage* img, vector<CvPoint>& vv );
      void detect_first_face( IplImage* img, vector<CvPoint>& vv );

      
		

	private:

};