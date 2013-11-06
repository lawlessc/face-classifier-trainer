
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
#include <dirent.h>

//gets time for random number initialization
//also to time training
#include <time.h>

//simply using this for square root function
#include <math.h>

#include "face_detect.cpp"
#endif




//#define NUMBER_OF_TRAINING_SAMPLES 3311
//#define ATTRIBUTES_PER_SAMPLE 65536 //this is the number of inputs created from a 256 image
//#define NUMBER_OF_TESTING_SAMPLES 796

//#define NUMBER_OF_CLASSES 1


using namespace std;
using namespace cv;




class neuralTest{
	
    //  friend class CvANN_MLP;

   // friend int 

   public:

      neuralTest ();
       friend class CvANN_MLP;

         CvANN_MLP* network;
         CvANN_MLP_TrainParams parameters;

         int Number_Of_samples;
         int Number_Of_Negative_Samples;
         int Number_Of_Positive_Samples;
         int elements_per_sample;

         Mat network_layers;

         double a_alpha;
         double a_beta;
         int net_func;

         Mat trainingInput;
         Mat trainingOutput;
         float pos_output;
         float neg_output;
         
         Mat K_FOLD_Input;
         Mat K_FOLD_Output;
         Mat K_FOLD_TestMat;
         Mat K_FOLD_TestOut;
     



         Mat training_classifications ;
         Mat  Result;
         Mat  testing;

         char *positiveDirectory;
         char *negativeDirectory;
         IplImage*  imageForVectors;

         vector<string> all_files;
         vector<int> sample_class;

          vector<string> testing_files_name;
          vector<string> k_fold_results;

         //image scale
         int image_scaling;
         bool use_face_detection;

         //bool pos_neg;

         face_detect face_detector;
       //  bool training_mode;

      //If this is on can be checked for a face, will be greyscaled and will be scaled in size   
     // void set_training_mode(bool fc);

void setScale(int sc);

void setFaceDetection(bool fc);

void  set_number_of_elements();
  

   
  
void set_input_data(char *pd,char *nd  );
 ////higher level functions used outside this class
void setLayers(int number_of_hidden_layers,int neurons_per_hidden_layer);



void setUp(int training_function, int network_function, double bparam1,double bparam2,
              int max_iterations, double epsilon , double activation_alpha, double activation_beta, int termCrit);

void setRpropPrameters( double param1,double param2,double param3,double param4,double param5);


//sets the scale images being used to train the networks are converted to,  assumes images are square.
//this also determines the number of inputs      


void setUp();

void prepareImages();

void train_k_fold();
void train();

void save_network(string directory,string filename);



void load_network(string directory_filename);
int  get_input_size();




float test(string directory_filename);
float test_image(IplImage* image);
bool test_image_bool(IplImage* image);

 void kfold_validation_Test(int output_size);
 void get_test_results(vector<string>& results);


void set_number_of_elements(char *directory);


bool getImageVectors(string  add,char *directory,vector<float>& vv);
bool  getImageVectors(string directory,vector<float>& vv);
bool getImageVectors(IplImage* tt , vector<float>& vv);
void vectorize(IplImage* tt , vector<float>& vv);

void  get_files_names(char *directory,vector<string>& stringVec);
void  vectorTest(vector<float> vc);
void  get_files_positive();
void  get_files_negative();

void move_matrix_row(Mat& tomat ,Mat& frommat ,int x , int y, int k);
void  randomize_data();
void  swap_items(int x, int y);

void KfoldCrossValidation(int k);

int getImageVectorSIZE(string add,char *directory);
int getImageVectorSIZE(string directory);
int getImageVectorSIZE(IplImage* tt);

void NegativeSampleCounter(char *directory);
void PositiveSampleCounter(char *directory);



IplImage* get_face_roi(IplImage* image,vector<CvPoint>& vv );

IplImage* greyscale(IplImage* image);

IplImage* Scale(IplImage* image);

//void store_recent_positive(IplImage* image);
//void store_recent_negative(IplImage* image);

	private:

};
