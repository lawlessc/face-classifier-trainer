#include "neuralTest.h"



using namespace cv;




 neuralTest::neuralTest()
    {

           network = new CvANN_MLP();

           Number_Of_samples = 0;
           Number_Of_Negative_Samples = 0;
           Number_Of_Positive_Samples = 0;
           use_face_detection = false; // this is false by default
           face_detector = face_detect();
           face_detector.load_haar_facedetect();
    }



  void neuralTest::setScale(int sc)
    {
    image_scaling = sc;


       

    }

 void neuralTest::setFaceDetection(bool fc)
    {

    use_face_detection = fc;


    }

  //this sets the number of neural network inputs to the number of pixels that a scaled image will contain
  void neuralTest::set_number_of_elements()
  {

    elements_per_sample =  image_scaling *  image_scaling ;
  }



void neuralTest::set_input_data(char *pd,char *nd  )
{


//pos_output = pos_output_;
//neg_output = neg_output_;


positiveDirectory = pd;
negativeDirectory = nd;

set_number_of_elements();

PositiveSampleCounter(positiveDirectory);
NegativeSampleCounter(negativeDirectory);

trainingInput                       = Mat(Number_Of_samples, elements_per_sample, CV_32FC1);
trainingOutput                      = Mat(Number_Of_samples, 2, CV_32FC1);
cout <<"Number_Of_samples:" << Number_Of_samples;
cout <<" elements_per_sample"<<  elements_per_sample;
}




void neuralTest::setLayers(int number_of_hidden_layers,int neurons_per_hidden_layer)
{
        network_layers = Mat(  1 ,  number_of_hidden_layers+2 ,  CV_32SC1);
        
        network_layers.at<int>(0,0) = elements_per_sample;
       
        for(int i = 1 ; i <=number_of_hidden_layers ; i++)
        {
        network_layers.at<int>(0,i) = neurons_per_hidden_layer;
        }
        network_layers.at<int>(0, number_of_hidden_layers+1) =  2;
          // network_layers.at<int>(0, number_of_hidden_layers+2) =  2;
}


void neuralTest::setUp(int training_function, int network_function, double bparam1,double bparam2,
              int max_iterations, double epsilon , double activation_alpha, double activation_beta , int termCrit)
{


a_alpha = activation_alpha;
a_beta  = activation_beta ;
net_func = network_function;

network->create(network_layers,  net_func,  a_alpha   ,a_beta  ); 

           if(termCrit == 1)
           {                                           //
parameters = CvANN_MLP_TrainParams(cvTermCriteria(CV_TERMCRIT_EPS, max_iterations, epsilon),training_function,
                                                             bparam1,bparam2);
}

           if(termCrit == 2)
           {                                           //
parameters = CvANN_MLP_TrainParams(cvTermCriteria(CV_TERMCRIT_ITER, max_iterations, epsilon),training_function,
                                                             bparam1,bparam2);
}


           if(termCrit == 3)
           {                                           //
parameters = CvANN_MLP_TrainParams(cvTermCriteria(CV_TERMCRIT_ITER+CV_TERMCRIT_EPS, max_iterations, epsilon),training_function,
                                                             bparam1,bparam2);


}

/*bp_dw_scale = bp_moment_scale = 0.1;
    rp_dw0 = 0.1; rp_dw_plus = 1.2; rp_dw_minus = 0.5;
    rp_dw_min = FLT_EPSILON; rp_dw_max = 50.;*/


//parameters.rp_dw0= 0.1;
parameters.rp_dw_min =FLT_EPSILON;
//parameters.rp_dw_plus = 1.2;
//parameters.rp_dw_minus = 0.5;

parameters.rp_dw_max =50.;

//parameters.min_val: -1;
  // parameters.max_val = 1;
  // parameters.min_val1 = -1;
 // parameters. max_val1 = 1;



}



void neuralTest::setRpropPrameters( double param1,double param2,double param3,double param4,double param5)
{

parameters.rp_dw0= param1;
parameters.rp_dw_min =param2;
parameters.rp_dw_plus = param3;
parameters.rp_dw_minus = param4;
parameters.rp_dw_max =param5;
   



}


void neuralTest::prepareImages()
{
     //clears vectors in the case the user is training again
    //all_files.clear();
    sample_class.clear(); 

    testing_files_name.clear();

 cout<< "gatherting images" << "\n" ;
//pos_neg = true;
get_files_positive();

//pos_neg = false;
cout<< "got positive" << "\n" ;
get_files_negative();

cout<< "got Negative" << "\n" ;

//cout<< "gatherting images" << "\n" ;
randomize_data();
cout<< "randomized" << "\n" ;

//g_print("GOT DATA");

}







 bool neuralTest::getImageVectors(string  add,char *directory,vector<float>& vv)
	{
    
    string  image_directory_string;

    image_directory_string.assign(directory);



        string direc = image_directory_string+"/"+add;
         return getImageVectors(direc , vv);
       
	}




 bool neuralTest::getImageVectors(string directory,vector<float>& vv)
	{
     

      IplImage *image = cvLoadImage(directory.c_str (), CV_LOAD_IMAGE_GRAYSCALE );
      

      return  getImageVectors(image, vv);

	}

	  bool neuralTest::getImageVectors(IplImage* image, vector<float>& vv)
  {
     
       
       if (use_face_detection == true )
       {
          vector<CvPoint> face_loc;
          face_detector.detect_first_face( image , face_loc );
         //  cout << "test1";
          if(face_loc.empty() ==true)
          { //cout << "test2";
            return false;
          }
          else
          {
 //cout << "test3";
          image =  get_face_roi( image , face_loc );

         // if (pos_neg == true)
         // {

          //  store_recent_positive(image);
         // }

         // if (pos_neg == true)
          //{

          //  store_recent_negative(image);
         // }

        }
       }


       
         

            vectorize(image , vv);


     return true;
  }

//as this is the final step to turning images to vectors
//only this function is required to create a vector and swap it
 void   neuralTest::vectorize(IplImage* image , vector<float>& vv)
{
               
    
      image = greyscale(image);
      image = Scale(image);
    
    // IplImage *out = cvCreateImage(cvSize( image->width, image->height ), IPL_DEPTH_8U, 1);

      //cvThreshold(image, out, 0, 255, CV_THRESH_BINARY);
    IplImage *final_img = cvCreateImage( cvSize( image->width, image->height ), IPL_DEPTH_32F, 1 );
     //cvConvertScale(image, img32,  1/255. ,0);
    cvConvertScale(image, final_img ,  1/255. ,0);


//cvConvertScale(image, image, 0.0039215, 0);
  vector<float> im_vector;

  

for(int i = 0 ; i < (image->height) ; i++)
          {
               for(int j = 0 ; j < (image->width) ; j++)
                  {
                   // im_vector.insert( im_vector.end() , CV_IMAGE_ELEM(image, float, i, j ) );
                    im_vector.insert( im_vector.end() , CV_IMAGE_ELEM(final_img , float, i, j ) );
                    
                  }

           }




 // return
   vv.swap(im_vector);
}



IplImage* neuralTest::get_face_roi(IplImage* image,vector<CvPoint>& vv )
 {
cvSetImageROI(image, cvRect(   vv[0].x   ,   vv[0].y   , vv[1].x    ,    vv[1].y )  );
IplImage *to_return = cvCreateImage( cvSize( vv[1].x  , vv[1].y ),  IPL_DEPTH_8U, 1 );
cvConvertImage(image,to_return,0);
return to_return;
}

IplImage* neuralTest::greyscale(IplImage* image)
 {
   //cout << "greyscale";
IplImage *to_return = cvCreateImage( cvSize( image->width  , image->height ),  IPL_DEPTH_8U, 1);

cvConvertImage(image,to_return,CV_INTER_AREA);

return to_return;
}



IplImage* neuralTest::Scale(IplImage* image)
{// cout << "Scale";
IplImage *to_return = cvCreateImage( cvSize( image_scaling , image_scaling  ), IPL_DEPTH_8U, 1 );
cvResize(image, to_return,1);
return to_return;
}











  /// this is no longer used
	void neuralTest::train()
    {



  network->train(trainingInput, trainingOutput, Mat(), Mat(), parameters);





    }






void neuralTest::save_network(string directory,string filename)
{

 string  sfilename;
 sfilename.assign(directory +"/"+ filename);
 char* filename_  = (char*)sfilename.c_str();

 network->save(filename_);

}





void neuralTest::load_network(string directory_filename)
{

//char* dd = directory_filename.c_str()
 network->load( directory_filename.c_str() );


 // The purpose of this is to get the size of the input layer on loading a network, then find the square root for image scaling purposes
 setScale(get_input_size());

}






int  neuralTest::get_input_size()
{
   CvMat* nlayers = (CvMat* ) network->get_layer_sizes();
 
    int i = CV_MAT_ELEM( *nlayers ,int , 0, 0 );
   
   
 
  return  sqrt(   i );
}




float neuralTest::test(string directory_filename)
 {

        int elements = getImageVectorSIZE(directory_filename);
        Mat input    = Mat(1, elements , CV_32FC1);
        Mat output   = Mat(2,  2  ,        CV_32FC1);

        vector<float> vect;

           getImageVectors(directory_filename,vect);

         for( int j = 0; j < elements; j++)
          {
             input.at<float>(0,j)  = vect[j];

         }



            network->predict( input, output);


         // printf("  %f  " ,  output.at<float>(0,0) );

return output.at<float>(0,0);
}




float neuralTest::test_image(IplImage* image)
    {
         
        vector<float> vect;
        vectorize(image , vect);


        int elements = image_scaling*image_scaling;
        Mat input    = Mat(1, elements , CV_32FC1);
        Mat output   = Mat(1,  2  ,        CV_32FC1);

          
         for( int j = 0; j < elements; j++)
          {
            input.at<float>(0,j)  = vect[j];
          //  cout << vect[j];
          }


        network->predict(input, output);


       printf("  %f  " ,  output.at<float>(0,0) );
       printf("  %f  " ,  output.at<float>(0,1) );

return output.at<float>(0,0);
    }



bool neuralTest::test_image_bool(IplImage* image)
  {
         
        vector<float> vect;
        vectorize(image , vect);


       // int elements = image_scaling*image_scaling;
        Mat input    = Mat(1, vect.size(), CV_32FC1);
        Mat output   = Mat(1,  2  ,        CV_32FC1);

          
         for( int j = 0; j < vect.size(); j++)
          {
            input.at<float>(0,j)  = vect[j];
          //  cout << vect[j];
          }


        network->predict(input, output);


      // printf("  %f  " ,  output.at<float>(0,0) );
      // printf("  %f  " ,  output.at<float>(0,1) );
      if( output.at<float>(0,0) >  output.at<float>(0,1))
      {

        return true;
      }


//return output.at<float>(0,0);
      return false;
    }





    void neuralTest::vectorTest(vector<float> vc)
    {



    for(int i = 0 ; i < vc.size() ; i++)
           {
                    printf("  This is a test %f" ,  vc[i]   );

           }

    }


void  neuralTest::get_files_positive()
{

int filename_offset = 0;
vector<string> sv;



get_files_names(positiveDirectory,sv);



                for(int i = 0 ; i < Number_Of_Positive_Samples ;i++ )
       {
        
         
             vector<float>  vec;
          bool to_continue = false;
           
          to_continue = getImageVectors(sv[i+filename_offset],positiveDirectory,vec);

        if(to_continue == true)
        {
            
           for(int j = 0; j < elements_per_sample; j++)
          {
            
         
            trainingInput.at<float>(i,j)  = vec[j];
          

          }
          

          trainingOutput.at<float>(i,0)  = 1.0f;
          trainingOutput.at<float>(i,1)  = 0.0f;

         }
        if(to_continue == false)
        {
         // Number_Of_samples--;
          Number_Of_Positive_Samples--;
          i--;
          filename_offset++;

        //  all_files.erase (all_files.begin() +i);
       //   sv.erase (sv.begin() +i);
         }

       }

}








void  neuralTest::get_files_negative()
{

 int filename_offset = 0;
vector<string> sv;

get_files_names(negativeDirectory,sv);

                for(int i= 0 ; i < Number_Of_Negative_Samples;i++ )
         {

              vector<float>  vec;

           bool to_continue = false;
           
          to_continue =  getImageVectors(sv[i+filename_offset],negativeDirectory,vec);

        if(to_continue == true)
        {

           for(int j = 0; j < elements_per_sample; j++)
          {

            trainingInput.at<float>((i + (Number_Of_Positive_Samples-1)),j)  =  vec[j];

          }
             
          trainingOutput.at<float>((i + (Number_Of_Positive_Samples-1)),  0) = 0.0f;
          trainingOutput.at<float>((i + (Number_Of_Positive_Samples-1)),  1) = 1.0f;


          }
         if(to_continue == false)
        {
      //    Number_Of_samples--;
          Number_Of_Negative_Samples--;
          i--;
          filename_offset++;
        //  all_files.erase (all_files.begin() + (Number_Of_Positive_Samples-1));
          //sv.erase (sv.begin() +i);
    
        }


        }
      
   }



void neuralTest::move_matrix_row(Mat& tomat ,Mat& frommat ,int x , int y, int k )
{

for(int i = 0 ; i < k ; i++)
    {
      tomat.at<float>(x,i) = frommat.at<float>(y,i);
    }

}





void  neuralTest::randomize_data()
{
   srand ( time(NULL) );

   
  
  int i = Number_Of_samples - 1;
  while(i >=0 )
  {
    
    
    int r  = rand() % (Number_Of_samples) ;
    
     swap_items(i,r); 

   i--; 
  }

}



void neuralTest::KfoldCrossValidation(int k)
{
     // this will cause problems where the number of samples is not evenly divisble,
     // it might be better to simply round down and lose some data instead of crashing
 int data_chunk_size = floor(Number_Of_samples/k);

 stringstream startTime;

 startTime << time (NULL)*60;
 
//clears results matrix, just incase training has alrady been done once.
 k_fold_results.clear();

 //defines the matrices to be used
  K_FOLD_Input    =  Mat(data_chunk_size*(k-1), elements_per_sample, CV_32FC1);
  K_FOLD_Output   =  Mat(data_chunk_size*(k-1), 2  , CV_32FC1);  
  K_FOLD_TestMat  =  Mat(data_chunk_size, elements_per_sample, CV_32FC1);
  K_FOLD_TestOut  =  Mat(data_chunk_size, 2, CV_32FC1);




 //trainingOutput                      = Mat(Number_Of_samples, classes, CV_32FC1);
   int  i =0;
   while( i < k)
   {

      network->clear();
      network->create(network_layers,  net_func,  a_alpha   ,a_beta  );
      bool test_mat_compiled = false;
      
      for(int chunk_no = 0 ; chunk_no < k ; chunk_no++)
    { 
         for(int j = 0 ; j < data_chunk_size; j++)
     { 
       if(chunk_no == i )
        {
          move_matrix_row( K_FOLD_TestMat , trainingInput,   j , j+((data_chunk_size)*chunk_no) , elements_per_sample );
          move_matrix_row( K_FOLD_TestOut ,  trainingOutput, j , j+((data_chunk_size)*chunk_no) , 2 );

          test_mat_compiled = true;
        }

        if(chunk_no != i && test_mat_compiled == false )
          {  
        
           move_matrix_row( K_FOLD_Input ,   trainingInput   , j+((data_chunk_size-1)*chunk_no) , j+((data_chunk_size)*chunk_no) , elements_per_sample );
           move_matrix_row( K_FOLD_Output ,  trainingOutput  , j+((data_chunk_size-1)*chunk_no) , j+((data_chunk_size)*chunk_no) , 2 );
          }
        if(chunk_no != i && test_mat_compiled == true )
          { 
         
           move_matrix_row( K_FOLD_Input ,   trainingInput   , j+((data_chunk_size-1)*(chunk_no-1)) , j+((data_chunk_size)*(chunk_no)) , elements_per_sample );
           move_matrix_row( K_FOLD_Output ,  trainingOutput  , j+((data_chunk_size-1)*(chunk_no-1)) , j+((data_chunk_size)*(chunk_no)), 2 );
          }
        
     }




     }
     train_k_fold();
      
  
   stringstream file;//create a stringstream
   file<< "k-test" << i << "time:" <<  startTime ;//add number to the stream
   

   save_network("./saves", file.str() );



    stringstream testend;
    testend << "For network " << i<< "\n" ;
    k_fold_results.insert(  k_fold_results.end() ,  testend.str() );

   kfold_validation_Test(data_chunk_size);

 




   cout << "\n" ;
   cout <<   i  ;
   cout << "\n" ;

   i++;
   }






}




    void neuralTest::kfold_validation_Test(int output_size)
    {

      
        Mat output_   = Mat(output_size, 2    ,        CV_32FC1);

        network->predict(K_FOLD_TestMat, output_);

           int error_count = 0;
      // printf("  %f  " ,  output.at<float>(0,0) );
           for (int i = 0 ; i < output_size ; i++)
           {
  
        
            cout << "\n";
          
   stringstream testoutput;//create a stringstream
   //file<< "k-test" << i;//add number to the stream
         //cout << "Output Positive is : " << output_.at<float>(i,0) <<"   "/*<<  testing_files_name[i] */<< "should be :  " <<K_FOLD_TestOut.at<float>(i,0) << "\n" ; 
         //cout << "Output Negative is : " << output_.at<float>(i,1) <<"   "/*<<  testing_files_name[i] */<< "should be :  " <<K_FOLD_TestOut.at<float>(i,1) << "\n" ; 
   // testoutput << "file isOutput Positive is : " << output_.at<float>(i,0) <<"   "/*<<  testing_files_name[i] */<< "should be :  " <<K_FOLD_TestOut.at<float>(i,0) << "\n"
   //               << "Output Negative is : " << output_.at<float>(i,1) <<"   "/*<<  testing_files_name[i] */<< "should be :  " <<K_FOLD_TestOut.at<float>(i,1) << "\n" ; 
     
      string res_predicted;
      string res_actual;
      string result_type;
     if(output_.at<float>(i,0) > output_.at<float>(i,1) )
     {
      res_predicted = "Yes";
      result_type = "True Positive";
     }
     else
     {

      res_predicted = "No";
      result_type = "True Negative";
     }

      if(K_FOLD_TestOut.at<float>(i,0) > K_FOLD_TestOut.at<float>(i,1) )
     {
      res_actual = "Yes";
     
     }
     else
     {

      res_actual = "No";
     }


     if(res_predicted != res_actual)
     {

      error_count++;

      if(res_predicted == "Yes")
        {result_type = "False Positive";}
            
      if(res_predicted == "No")
      {result_type = "False Negative";}
            
     }

      //testoutput 
      //<< "file:"<<  testing_files_name[i]
      cout <<"Result:   "<<  res_predicted <<"  Actual Result:   " <<  res_actual <<"\n" << result_type<<"\n" ;
      

     // k_fold_results.insert(  k_fold_results.end() ,  testoutput.str() );
      }

      stringstream testend;

      float error_rate = ( error_count/output_size )*100;
      testend << "Error count is: " << error_count << " in "<< output_size << " images" << "\n" <<"Error rate of:"<< error_rate<< " Percent" <<"\n" ;


      k_fold_results.insert(  k_fold_results.end() ,  testend.str() );


         
    }





     void neuralTest::get_test_results(vector<string>& results)

     {
      


      results.swap(  k_fold_results);
     }


          void neuralTest::train_k_fold()
    {


 // cout <<"start-train";
  int iter = network->train( K_FOLD_Input, K_FOLD_Output, Mat(),Mat(), parameters);
  cout <<"irations: "<< iter;
 



    }







//This use by the randomizing algorithm to swap data
void  neuralTest::swap_items(int x, int y)
{
 // cout << "swap: " << x << " : " << y;
     Mat temp = Mat(1, elements_per_sample, CV_32FC1);

      
        
          move_matrix_row( temp , trainingInput, 0 , x , elements_per_sample );
     //  trainingInput.row(x) =  trainingInput.row(y);
          move_matrix_row( trainingInput , trainingInput, x , y , elements_per_sample );
       //trainingInput.row(y) =  temp.row(0);
           move_matrix_row( trainingInput , temp, y , 0 , elements_per_sample );

  Mat tempo = Mat(1, 2, CV_32FC1);

      // tempo.row(0)           =  trainingOutput.row(x) ;
        move_matrix_row( tempo , trainingOutput, 0 , x , 2 );
      // trainingOutput.row(x) =  trainingOutput.row(y);
        move_matrix_row( trainingOutput , trainingOutput, x , y , 2 );
     //  trainingOutput.row(y) =  tempo.row(0);
       move_matrix_row( trainingOutput , tempo, y , 0 , 2 );

 // String str_temp;

   //    str_temp     = all_files[x];
    //   all_files[x] = all_files[y];   
     //  all_files[y] = str_temp;
 
      
}




void  neuralTest::NegativeSampleCounter(char *directory)
{

DIR *dir;
String sr;
struct dirent *ent;
    dir = opendir (directory);
if (dir != NULL) {

  //counts files in directory
  while ((ent = readdir (dir)) != NULL) {
      sr.assign(ent -> d_name);
        if(sr =="." || sr =="..")
      {

      }
      else
      {
       Number_Of_samples++;
       Number_Of_Negative_Samples++;
      }

  }
  closedir (dir);
} else {
  /* could not open directory */
  perror ("");
 // return EXIT_FAILURE;
}


}

void  neuralTest::PositiveSampleCounter(char *directory)
{

DIR *dir;
string sr;

struct dirent *ent;
    dir = opendir (directory);
if (dir != NULL) {

  //counts files in directory
  while ((ent = readdir (dir)) != NULL) {
      sr.assign(ent -> d_name);
       if(sr =="." || sr =="..")
      {

      }
      else
      {
       Number_Of_samples++;
       Number_Of_Positive_Samples++;
      }
//perror ("5");
  }
  closedir (dir);
} else {
  /* could not open directory */
  perror ("");
 // return EXIT_FAILURE;
}


}


//THis gets the first image file address in the positive images directory and uses to set the number of elements/inputs per the network
void neuralTest::set_number_of_elements(char *directory)
{
DIR *dir;
string sr;
bool in_while= true;

struct dirent *ent;
    dir = opendir (directory);
if (dir != NULL) {
//ent = readdir (dir);

while ((ent = readdir (dir)) != NULL && in_while == true )
 {
     sr.assign(ent -> d_name);
   if(sr =="." || sr =="..")
      {
          //recurssion in file IO might be a dirty fix
       //set_number_of_elements(directory);

      }
      else
      {
       elements_per_sample = getImageVectorSIZE(ent->d_name,directory);
       in_while = false;
      }
}


closedir (dir);
}
 else {
  // could not open directory
  perror ("");
 // return EXIT_FAILURE;
}

}









//the purpose of this is to get the size of one image in files
//this was tp be used once for helping set the size of matrices/vectors being
//used as our inputs
//int neuralTest::getImageVectorSIZE(String add)
int neuralTest::getImageVectorSIZE(string add,char *directory)
	{
  string  image_address_string;
  string  image_directory_string;

  image_address_string.assign(add);
  image_directory_string.assign(directory);

  string direc = image_directory_string+"/"+ image_address_string;
 
  return getImageVectorSIZE(direc);
}


int neuralTest::getImageVectorSIZE(string directory)
	{

        IplImage *dst = cvLoadImage(directory.c_str (), CV_LOAD_IMAGE_GRAYSCALE );


   return getImageVectorSIZE(dst);
	}


  int neuralTest::getImageVectorSIZE(IplImage* tt)
  {
    return (tt->width ) * (tt->height);
  }




void neuralTest::get_files_names(char *directory,vector<string>& stringVec)
{

string  sr;
vector<string> stringVectors;

DIR *dir;

struct dirent *ent;
    dir = opendir (directory);
if (dir != NULL) {

  // print all the files and directories within directory
  while ((ent = readdir (dir)) != NULL) {
      sr.assign(ent->d_name);
      if(sr =="." || sr =="..")
      {

      }
      else
      {
        stringVectors.insert( stringVectors.end() , sr );
        //all_files.insert( all_files.end() , sr );
       

      }

  }
  closedir (dir);
} else {
  // could not open directory
  perror ("");
 // return EXIT_FAILURE;
}

  return stringVec.swap(stringVectors);
}

/*
void   neuralTest::store_recent_positive(IplImage* image)
   {
          
           
    
     char *unclassified_image_address;
        unclassified_image_address ="./positive_loaded";
    string directory_string;
    directory_string.assign(unclassified_image_address);
    
      
    string systime;
    systime   =   time(NULL);

    string direc = directory_string+"/"+systime+".jpg";

      

       cvSaveImage(direc.c_str() ,image);


   }

   void   neuralTest::store_recent_negative(IplImage* image)
   {
          
           
     char *unclassified_image_address;
         unclassified_image_address ="./negative_loaded";
    string directory_string;
    directory_string.assign(unclassified_image_address);
    
      
    string systime;
    systime   =   time(NULL);

    string direc = directory_string+"/"+systime+".jpg";

      

       cvSaveImage(direc.c_str() ,image);


   }*/