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
#include "neuralTest.cpp"
#endif



using namespace std;

GtkWidget *window;//window declared here as global
GtkWidget *Top_Layer_Box;

GtkWidget *SetupBox;
GtkWidget *SetupBox2;

GtkWidget *Test_result_box;
GtkScrolledWindow *Test_results_text_box;
GtkWidget *Train_again_button;      

vector<string> k_fold_results;
  //these all represent data that will be passed to the neural net when trianing takes place,
  //might be beter to encapsulate them all into one data type / class
char *dir1;
char *dir2;

int termcrit = 0;  //0 termcrit?
int  training_Function = 1;  //0 backpropagation 1 is rpropogation
int  network_Function = 1;//0 IDENTITY  , 1 SIGMOID_SYM   2 GAUSSIAN


 double  training_param1;
double  training_param2;

  int neurons_per_hidden_layer;

  neuralTest  mine;





  GtkSpinButton   *image_scale_spinner;
  GtkToggleButton  *face_detect_on; 


  //GtkSpinButton   *positive_output_spinner;
  //float positive_output;
  //GtkSpinButton   *negative_output_spinner;
  //float negative_output;

   
   GtkSpinButton *Term_COUNT;
   int  Max_iterations;
   GtkSpinButton *Term_EPSILON;
  double  epsilon_;
  int termcr ;



  GtkSpinButton  *rp_dw0;// rp_dw0 for RPROP and bp_dw_scale for BACKPROP.
  double para1;
  GtkSpinButton *rp_dw_min;//It is rp_dw_min for RPROP and bp_moment_scale for BACKPROP.
  double para2;

  GtkSpinButton  *rp_dw_plus;
  double para3;
  GtkSpinButton *rp_dw_minus;
  double para4;
  
  GtkSpinButton  *rp_dw_max;
  double para5;

 
 // GtkSpinButton *rp_dw0SPIN;
 // GtkSpinButton *rp_dw_minSPIN;
 // GtkSpinButton *rp_dw_plusSPIN;
 // GtkSpinButton *rp_dw_minusSPIN;
 // GtkSpinButton *rp_dw_maxSPIN;
  



 // parameters.rp_dw0= 0.1;
//parameters.rp_dw_min =FLT_EPSILON;
//parameters.rp_dw_plus = 1.2;
//parameters.rp_dw_minus = 0.5;

//parameters.rp_dw_max =50.;



   GtkSpinButton  *alpha_activation;
  double alpha;
   GtkSpinButton  *beta_activation;
  double beta;

  GtkSpinButton  *hidden_layer_spin;
  GtkSpinButton  *hidden_layer_neurons_spin;



   GtkSpinButton  *number_of_KFolds;
   int K_Folds ;

//textbox declared globally so functions may access them
  GtkWidget *SaveTextBox;








void add_one(GtkWidget *widget, gpointer data)
{
  GtkWidget *newlabel = gtk_label_new("new");
  GtkWidget *newbox  =  gtk_vbutton_box_new();

  Test_result_box = gtk_vbutton_box_new();
 
 gtk_container_add(GTK_CONTAINER(newbox),newlabel);
 Test_result_box = newbox;
 gtk_container_add(GTK_CONTAINER(Top_Layer_Box),Test_result_box);

 gtk_widget_show (Test_result_box);

}


void  settings_function(GtkComboBox *combo, gpointer data)
{


string  sstring = gtk_combo_box_get_active_text( combo );

              //OpenCv network evaluation function enumerators
              // enum { IDENTITY = 0, SIGMOID_SYM = 1, GAUSSIAN = 2 };
             //it might be better to set these to enumerators somehow
            if(sstring == "IDENTITY")
             {
              network_Function=0;
              // g_print("IDENTITY");
             }
            if(sstring == "SIGMOID_SYM")
             {
              network_Function=1;
              //g_print("SIGMOID_SYM");
             }
            if(sstring == "GAUSSIAN")
             {
              network_Function=2;
             // g_print("GAUSSIAN");
             }


             //   OpenCv training algorithm enumerators
             //   enum { BACKPROP=0, RPROP=1 };

           if(sstring == "BackProp")
             {
              training_Function=0;
              //g_print("BackProp");
             }
           if(sstring == "Rprop")
             {
              training_Function=1;
             //g_print("Rprop");
             }



}




void  epsilon_function(GtkButton *button, GtkRadioButton *radiobutton )
{

          //    g_print("Epsilon");

 termcr = 1;

}


void  count_function(GtkButton *button, GtkRadioButton *radiobutton )
{

            //  g_print("Count");

 termcr = 2;

}

void  epsilonpluscount_function(GtkButton *button, GtkRadioButton *radiobutton )
{

            //  g_print("Epsilon+count");
  termcr = 3;

}



void select_negative_folder(GtkWidget *widget, gpointer data)
{
    GtkWidget *dialog;

     dialog = gtk_file_chooser_dialog_new("Select folder",
                                          GTK_WINDOW(window),
                                          GTK_FILE_CHOOSER_ACTION_SELECT_FOLDER,
                                          GTK_STOCK_CANCEL,GTK_RESPONSE_CANCEL,
                                          GTK_STOCK_OPEN,GTK_RESPONSE_ACCEPT,
                                          NULL);  //GTK_FILE_CHOOSER_ACTION_OPEN,

            if(gtk_dialog_run(GTK_DIALOG(dialog)) == GTK_RESPONSE_ACCEPT)
                    {
                        //char  *file = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(dialog));

                              // g_print(file);

                              dir2 = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(dialog));

                       }


gtk_widget_destroy(dialog);





}


void load_network(GtkWidget *widget, gpointer data)
{
    GtkWidget *dialog;

     dialog = gtk_file_chooser_dialog_new("Select Neural Network",
                                          GTK_WINDOW(window),
                                          GTK_FILE_CHOOSER_ACTION_OPEN,
                                          GTK_STOCK_CANCEL,GTK_RESPONSE_CANCEL,
                                          GTK_STOCK_OPEN,GTK_RESPONSE_ACCEPT,
                                          NULL);  //GTK_FILE_CHOOSER_ACTION_OPEN,

            if(gtk_dialog_run(GTK_DIALOG(dialog)) == GTK_RESPONSE_ACCEPT)
                    {
                          string  sfilename;
                        char  *file = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(dialog));




               sfilename.assign(file);
               char* filename_  = (char*)sfilename.c_str();



                             mine.load_network( filename_);



                       }
gtk_widget_destroy(dialog);

}

void save_network(GtkWidget *widget, gpointer data)
{
   // GtkWidget *dialog;
   //String
   //filename;
     const gchar *filename;
      filename   =     gtk_entry_get_text(GTK_ENTRY(SaveTextBox));
        //g_print(filename);
        GtkWidget *dialog;

     dialog = gtk_file_chooser_dialog_new("Select folder to save network to",
                                          GTK_WINDOW(window),
                                          GTK_FILE_CHOOSER_ACTION_SELECT_FOLDER,
                                          GTK_STOCK_CANCEL,GTK_RESPONSE_CANCEL,
                                          GTK_STOCK_OPEN,GTK_RESPONSE_ACCEPT,
                                          NULL);  //GTK_FILE_CHOOSER_ACTION_OPEN,

            if(gtk_dialog_run(GTK_DIALOG(dialog)) == GTK_RESPONSE_ACCEPT)
                    {
                        char  *file = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(dialog));

                              // g_print(file);

                             // dir2 = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(dialog));

                          string  sfilename;
                          string  sdirectory;

                          sfilename.assign(filename);
                              sdirectory.assign(file);

                          mine.save_network(sdirectory,sfilename);


                       }


gtk_widget_destroy(dialog);




}

//user selects an image to test against the currently selected network
void test_network(GtkWidget *widget, gpointer data)
{
    float test;
    GtkWidget *dialog;

     dialog = gtk_file_chooser_dialog_new("Select folder",
                                          GTK_WINDOW(window),
                                          GTK_FILE_CHOOSER_ACTION_OPEN,
                                          GTK_STOCK_CANCEL,GTK_RESPONSE_CANCEL,
                                          GTK_STOCK_OPEN,GTK_RESPONSE_ACCEPT,
                                          NULL);  //GTK_FILE_CHOOSER_ACTION_OPEN,

            if(gtk_dialog_run(GTK_DIALOG(dialog)) == GTK_RESPONSE_ACCEPT)
                    {
                       string file = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(dialog));

                              // g_print(file);

                            //  dir2 = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(dialog));



                    //       float  ff = mine.test(file);
                //    mine.getImageVectorSIZE(file);
                      //    cout<< "float is : " << ff << " \n";
                 test =   mine.getImageVectorSIZE(file);
                       }
gtk_widget_destroy(dialog);
cout << "Output is "  << test;
}



void select_positive_folder(GtkWidget *widget, gpointer data)
{
    GtkWidget *dialog;

     dialog = gtk_file_chooser_dialog_new("Select folder",
                                          GTK_WINDOW(window),
                                          GTK_FILE_CHOOSER_ACTION_SELECT_FOLDER,
                                          GTK_STOCK_CANCEL,GTK_RESPONSE_CANCEL,
                                          GTK_STOCK_OPEN,GTK_RESPONSE_ACCEPT,
                                          NULL);  //GTK_FILE_CHOOSER_ACTION_OPEN,

            if(gtk_dialog_run(GTK_DIALOG(dialog)) == GTK_RESPONSE_ACCEPT)
                    {
                        //char  *file = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(dialog));

                              // g_print(file);

                              dir1 = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(dialog));

                       }


gtk_widget_destroy(dialog);

}






void show_results()
{



//Test_result_box.gtk_widget_destroy ();
//Test_result_box = gtk_vbutton_box_new();
Test_results_text_box  = (GtkScrolledWindow*)  gtk_scrolled_window_new     (NULL,NULL);

 gtk_widget_set_usize((GtkWidget *)Test_results_text_box, 250, 150);

gtk_scrolled_window_set_policy (GTK_SCROLLED_WINDOW (Test_results_text_box),GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);
//gtk_layout_set_size(Test_results_text_box,100 , k_fold_results.size()*40);

 GtkWidget *resultBox;
 resultBox = gtk_vbutton_box_new();


for (int i = 0 ; i <k_fold_results.size() ; i++)
{

  GtkWidget *  resultlabel = gtk_accel_label_new      (k_fold_results[i].c_str());
 gtk_container_add(GTK_CONTAINER( resultBox ),resultlabel);
 

}
//gtk_scrolled_window_add_with_viewport (Test_results_text_box,resultBox);
 //gtk_container_add(GTK_CONTAINER(viewport ), resultBox);


gtk_scrolled_window_add_with_viewport( GTK_SCROLLED_WINDOW( Test_results_text_box),resultBox);

gtk_container_add(GTK_CONTAINER(Test_result_box),(GtkWidget*) Test_results_text_box);
    
//gtk_widget_show_all (resultBox);
gtk_widget_show_all (Test_result_box);
gtk_widget_show_all ((GtkWidget*)Test_results_text_box);
  //gtk_widget_show (Test_result_box);
}






void k_fold()
{
bool  use_face_detect =   gtk_toggle_button_get_active (face_detect_on);

int imagescale  =   (int)  gtk_spin_button_get_value(image_scale_spinner);
  
Max_iterations  =  (int)  gtk_spin_button_get_value(Term_COUNT);
epsilon_         =        gtk_spin_button_get_value(Term_EPSILON);

para1    = gtk_spin_button_get_value(rp_dw0);
para2    = gtk_spin_button_get_value(rp_dw_min );
para3    = gtk_spin_button_get_value(rp_dw_plus );
para4    = gtk_spin_button_get_value(rp_dw_minus );
para5    = gtk_spin_button_get_value(rp_dw_max  );

alpha    = gtk_spin_button_get_value(alpha_activation);
beta     = gtk_spin_button_get_value(beta_activation);


//positive_output = (float) gtk_spin_button_get_value(positive_output_spinner);
//negative_output = (float) gtk_spin_button_get_value(negative_output_spinner);

int hiddenLayers  =(int)  gtk_spin_button_get_value(hidden_layer_spin);
int hiddenNeurons =(int)  gtk_spin_button_get_value(hidden_layer_neurons_spin);

mine = neuralTest();

mine.setFaceDetection(use_face_detect);

mine.setScale(imagescale);

mine.set_input_data(dir1 ,dir2);

mine.setLayers(hiddenLayers,hiddenNeurons);

mine.setUp(  training_Function  ,  network_Function , para1 ,para2  , Max_iterations,epsilon_ ,alpha , beta ,termcr);

mine.setRpropPrameters(para1, para2, para3, para4, para5);


mine.prepareImages();
//g_print("data prepped");
//mine.train();number_of_KFolds
int kf = (int) gtk_spin_button_get_value(number_of_KFolds);
mine.KfoldCrossValidation(kf);
//mine.train_k_fold();
//g_print("trained");

mine.get_test_results(k_fold_results);
 


show_results();


}


void check_for_folders()
{
  if(dir1 == NULL || dir2 == NULL)
  {

 
     GtkWidget *     file_warning;

     file_warning =     gtk_message_dialog_new ( GTK_WINDOW(window),
                                                 GTK_DIALOG_MODAL,
                                                 GTK_MESSAGE_WARNING,
                                                 GTK_BUTTONS_OK,
                                                 "You need to select both a positive and negative sample folder");


     gtk_dialog_run (GTK_DIALOG (file_warning));

                    gtk_widget_destroy(file_warning);



  }
  else
  {
    k_fold();
    gtk_widget_set_sensitive(Train_again_button, true);
  }



}

//this is to be use if images have already been gathered, to train the networks again
void train_k_fold_again()
{


Max_iterations  =  (int)  gtk_spin_button_get_value(Term_COUNT);
epsilon_         =        gtk_spin_button_get_value(Term_EPSILON);

para1    = gtk_spin_button_get_value(rp_dw0);
para2    = gtk_spin_button_get_value(rp_dw_min );
para3    = gtk_spin_button_get_value(rp_dw_plus );
para4    = gtk_spin_button_get_value(rp_dw_minus );
para5    = gtk_spin_button_get_value(rp_dw_max  );
alpha    = gtk_spin_button_get_value(alpha_activation);
beta     = gtk_spin_button_get_value(beta_activation);

int hiddenLayers  =(int)  gtk_spin_button_get_value(hidden_layer_spin);
int hiddenNeurons =(int)  gtk_spin_button_get_value(hidden_layer_neurons_spin);

mine.setLayers(hiddenLayers,hiddenNeurons);

mine.setUp(  training_Function  ,  network_Function , para1 ,para2  , Max_iterations,epsilon_ ,alpha , beta ,termcr);

mine.setRpropPrameters(para1, para2, para3, para4, para5);


int kf = (int) gtk_spin_button_get_value(number_of_KFolds);
mine.KfoldCrossValidation(kf);


mine.get_test_results(k_fold_results);

show_results();



}



/////////////////////BEGINS MAIN////////////////////////////////////////////////////////////////////////////////
int main (int argc, char *argv[])
{
    //GtkWidget *window;

//hold all other boxes

GtkWidget *labels_TrainingDataBox;
GtkWidget *TrainingDataBox;//holds positive and negative folder address for image files

GtkWidget *labels_ImageProcessBox;
GtkWidget *ImageProcessBox;

GtkWidget *labels_TermCriteriaBox;
GtkWidget *TermCriteriaBox;

GtkWidget *labels_TermCriteria_Radio_Box;
GtkWidget *TermCriteria_Radio_Box;

GtkWidget *labels_TrainingParamBox;
GtkWidget *TrainingParamBox;//holds combobox for specifying network training algo and parameters

GtkWidget *labels_NetworkTopologyBox;
GtkWidget *NetworkTopologyBox;//holds options that allow the user to define how the network works and neurons in the hidden layer(s)

GtkWidget *labels_NetworkLayerBox;
GtkWidget *NetworkLayerBox;


GtkWidget *labels_TrainTestButtonBox;
GtkWidget *TrainTestButtonBox;//hold options that allow the user to define how a network is trained


GtkWidget *labels_LoadSaveButtonBox;
GtkWidget *LoadSaveButtonBox;

GtkWidget *labels_KFoldButtonBox;
GtkWidget *KFoldButtonBox;

//GtkWidget *labels_ImageProcessBox;
GtkWidget  *ButtonboxForPositive;
GtkWidget  *ButtonboxForNegative;



//determines if EPS, COUNT or COUNT + EPS are used as termination criteria
GtkWidget *Term_TYPE_EPS;
GtkWidget *Term_TYPE_COUNT;
GtkWidget *Term_TYPE_EPS_PLUS_COUNT;


GtkWidget *TrainingMethodComboBox;

GtkWidget *ActivationFunctionComboBox;


//GtkWidget *TrainButton;
//GtkWidget *TestButton;

//GtkWidget *LoadButton;
//GtkWidget *SaveButton;

GtkWidget *KFoldButton;




gtk_init(&argc, &argv);

    /* Create the main, top level window */
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  
    gtk_window_set_title(GTK_WINDOW(window), "NetWork Training");
    GtkWidget * space_label  =         gtk_label_new  ("   "); //exists to take up space so labels can be placed next to correct widgets
 



    /*
    ** Map the destroy signal of the window to gtk_main_quit;
    ** When the window is about to be destroyed, we get a notification and
    ** stop the main GTK+ loop by returning 0
    */
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

Top_Layer_Box          = gtk_vbutton_box_new();
SetupBox               = gtk_hbutton_box_new();
SetupBox2              = gtk_hbutton_box_new();
Test_result_box        = gtk_vbutton_box_new();


labels_TrainingDataBox        = gtk_vbutton_box_new ();
TrainingDataBox        = gtk_vbutton_box_new ();


labels_ImageProcessBox        = gtk_vbutton_box_new ();
ImageProcessBox        = gtk_vbutton_box_new ();



labels_TermCriteriaBox        = gtk_vbutton_box_new ();
TermCriteriaBox        = gtk_vbutton_box_new ();

labels_TermCriteria_Radio_Box = gtk_vbutton_box_new ();
TermCriteria_Radio_Box = gtk_vbutton_box_new ();

labels_TrainingParamBox       = gtk_vbutton_box_new ();
TrainingParamBox       = gtk_vbutton_box_new ();

labels_NetworkTopologyBox     = gtk_vbutton_box_new ();
NetworkTopologyBox     = gtk_vbutton_box_new ();

labels_NetworkLayerBox        = gtk_vbutton_box_new ();
NetworkLayerBox        = gtk_vbutton_box_new ();
//TrainTestButtonBox     = gtk_vbutton_box_new ();
//LoadSaveButtonBox      = gtk_vbutton_box_new ();

labels_KFoldButtonBox         = gtk_vbutton_box_new ();
KFoldButtonBox         = gtk_vbutton_box_new ();



//////////////////////////////////////////////////////////////////////
   //      ///THE TRAINING DATA BOX
///////////////////////////////////////////////////////////////////////////


 ButtonboxForPositive = gtk_button_new_with_label ("Positive Folder");
 ButtonboxForNegative = gtk_button_new_with_label ("Negative Folder");

 GtkWidget * pos_folder_label  =         gtk_label_new  ("Set positive samples");
 GtkWidget * neg_folder_label  =         gtk_label_new  ("Set negative samples");

 gtk_widget_set_tooltip_text (  ButtonboxForPositive   , "Select folder from which to gather positive images");
 gtk_widget_set_tooltip_text (  ButtonboxForNegative   , "Select folder from which to gather negative images");

      gtk_container_add(GTK_CONTAINER(labels_TrainingDataBox), pos_folder_label);
      gtk_container_add(GTK_CONTAINER(TrainingDataBox), ButtonboxForPositive);
     gtk_container_add(GTK_CONTAINER(labels_TrainingDataBox), neg_folder_label);
      gtk_container_add(GTK_CONTAINER(TrainingDataBox), ButtonboxForNegative);
      // gtk_container_add(GTK_CONTAINER(TrainingDataBox), (GtkWidget *)negative_output_spinner);

g_signal_connect(G_OBJECT(ButtonboxForPositive), "clicked",
      G_CALLBACK(select_positive_folder), NULL);

g_signal_connect(G_OBJECT(ButtonboxForNegative), "clicked",
      G_CALLBACK(select_negative_folder), NULL);





//////////////////////////////////////////////////////////////////////
   //      ///IMAGE PROCESSING BOX
///////////////////////////////////////////////////////////////////////////
GtkAdjustment *scale_adj;
scale_adj  = (GtkAdjustment *) gtk_adjustment_new ( 50, 2 ,10000, 1.00, 0, 0);
image_scale_spinner        =  (GtkSpinButton *)     gtk_spin_button_new     ( scale_adj  ,  1  ,  0  );
 

face_detect_on =  (GtkToggleButton*) gtk_check_button_new_with_label ("Face Detection");



gtk_widget_set_tooltip_text ( (GtkWidget *)image_scale_spinner , "The image scale determines not only scale of image but also the number of inputs (at 1 per pixel). i.e 50 will scale images to 50X50 squares which will train a network with 2500 input neurons");
gtk_widget_set_tooltip_text ( (GtkWidget *)face_detect_on , "Use face detection on images");



GtkWidget * imagescale_label  =         gtk_label_new  ("Set image scale");
GtkWidget * facedetect_label  =         gtk_label_new  (" ");

gtk_container_add(GTK_CONTAINER(labels_ImageProcessBox), imagescale_label);
gtk_container_add(GTK_CONTAINER(ImageProcessBox), (GtkWidget *) image_scale_spinner);
gtk_container_add(GTK_CONTAINER(labels_ImageProcessBox), facedetect_label);
gtk_container_add(GTK_CONTAINER(ImageProcessBox), (GtkWidget *) face_detect_on);





 //////////////////////////////////////////////////////////////////////
   //      ///TERMCRITERIA BOX
///////////////////////////////////////////////////////////////////////////
//
//
////
////



//Term_COUNT    =   gtk_entry_new ();
//Term_EPSILON  =   gtk_entry_new ();



GtkAdjustment *TCount;
GtkAdjustment *TEpsilon;
//fparam_adj_one = (GtkAdjustment *) gtk_adjustment_new (2.500, 0.0, 5.0, 0.001, 0.1, 0.1);
//GtkAdjustment*  test = gtk_adjustment_new(0,0,  120,  1 ,0,0);
TCount = (GtkAdjustment *) gtk_adjustment_new (45000, 2 ,1000000, 1, 0, 0);
TEpsilon = (GtkAdjustment *) gtk_adjustment_new (0.000010, 0.0000001, 100.0000, 0.000001, 0, 0);
Term_COUNT        =   (GtkSpinButton *)gtk_spin_button_new   (    TCount ,  1  ,  0  );
Term_EPSILON        =   (GtkSpinButton *)gtk_spin_button_new ( TEpsilon ,  1  ,  7  );


 gtk_widget_set_tooltip_text (   (GtkWidget *) Term_COUNT   , "Set termination count");
 gtk_widget_set_tooltip_text (   (GtkWidget *) Term_EPSILON   , "Set termination epsilon");




//Term_TYPE     =   gtk_radio_button_new_with_label( NULL, "1" );

Term_TYPE_EPS                     =gtk_radio_button_new_with_label( NULL, "Epsilon" );


Term_TYPE_COUNT    = //              =gtk_radio_button_new_with_label( NULL, "Count");
gtk_radio_button_new_with_label_from_widget( GTK_RADIO_BUTTON( Term_TYPE_EPS           ), "Count" );
Term_TYPE_EPS_PLUS_COUNT    =    //  =gtk_radio_button_new_with_label( NULL, "Epsilon+Count" );
gtk_radio_button_new_with_label_from_widget( GTK_RADIO_BUTTON( Term_TYPE_EPS           ), "Epsilon+Count" );


GtkWidget * iterations_label  =         gtk_label_new  ("Maximum iterations:");
GtkWidget * epsilon_label  =         gtk_label_new  ("Epsilon:");

gtk_container_add(GTK_CONTAINER(labels_TermCriteriaBox), iterations_label);
gtk_container_add(GTK_CONTAINER(TermCriteriaBox), (GtkWidget *)Term_COUNT);

gtk_container_add(GTK_CONTAINER(labels_TermCriteriaBox), epsilon_label);
gtk_container_add(GTK_CONTAINER(TermCriteriaBox), (GtkWidget *)Term_EPSILON);


gtk_container_add(GTK_CONTAINER(labels_TermCriteriaBox),  gtk_label_new  ("   "));
gtk_container_add(GTK_CONTAINER(TermCriteriaBox), Term_TYPE_EPS );

gtk_container_add(GTK_CONTAINER(labels_TermCriteriaBox), gtk_label_new  ("   "));
gtk_container_add(GTK_CONTAINER(TermCriteriaBox), Term_TYPE_COUNT );

gtk_container_add(GTK_CONTAINER(labels_TermCriteriaBox), gtk_label_new  ("   "));
gtk_container_add(GTK_CONTAINER(TermCriteriaBox), Term_TYPE_EPS_PLUS_COUNT  );


g_signal_connect( G_OBJECT( Term_TYPE_EPS   ), "clicked",
                      G_CALLBACK( epsilon_function ), NULL );

g_signal_connect( G_OBJECT( Term_TYPE_COUNT ),"clicked",
                      G_CALLBACK(  count_function ), NULL );

g_signal_connect( G_OBJECT( Term_TYPE_EPS_PLUS_COUNT), "clicked",
                      G_CALLBACK(  epsilonpluscount_function ), NULL );



/////////////////////////////////////////////////////////////////////////////////////////
 // ///THE TRAINING PARAMETERS  BOX
////////////////////////////////////////////////////////////////////////////////////////




TrainingMethodComboBox = gtk_combo_box_new_text();
gtk_combo_box_append_text( GTK_COMBO_BOX( TrainingMethodComboBox ), "BackProp" );
gtk_combo_box_append_text( GTK_COMBO_BOX( TrainingMethodComboBox ), "Rprop" );
gtk_widget_set_tooltip_text (   (GtkWidget *) TrainingMethodComboBox    , "Select a training algorithm");
g_signal_connect( G_OBJECT(TrainingMethodComboBox), "changed",
                      G_CALLBACK(  settings_function ), NULL );




GtkAdjustment *Tpara1;
GtkAdjustment *Tpara2;
GtkAdjustment *Tpara3;
GtkAdjustment *Tpara4;
GtkAdjustment *Tpara5;






//fparam_adj_one = (GtkAdjustment *) gtk_adjustment_new (2.500, 0.0, 5.0, 0.001, 0.1, 0.1);
//GtkAdjustment*  test = gtk_adjustment_new(0,0,  120,  1 ,0,0);
Tpara1 = (GtkAdjustment *) gtk_adjustment_new (0.1 , 0 ,100, 0.00001, 0, 0);
Tpara2 = (GtkAdjustment *) gtk_adjustment_new (FLT_EPSILON, 0, 100, 0.0000001, 0, 0);
Tpara3 = (GtkAdjustment *) gtk_adjustment_new (1.2 , 1.01 ,100, 0.01, 0, 0);
Tpara4 = (GtkAdjustment *) gtk_adjustment_new (0.5,  -10, 0.99, 0.00001, 0, 0);
Tpara5 = (GtkAdjustment *) gtk_adjustment_new (50,  1, 1001, 1, 0, 0);

   




rp_dw0         = (GtkSpinButton *)  gtk_spin_button_new ( Tpara1 ,  1  ,  5  );
rp_dw_min         = (GtkSpinButton *)  gtk_spin_button_new ( Tpara2 ,  1  ,  8  );
rp_dw_plus         = (GtkSpinButton *)  gtk_spin_button_new ( Tpara3 ,  1  ,  3  );
rp_dw_minus         = (GtkSpinButton *)  gtk_spin_button_new ( Tpara4 ,  1  ,  5  );
rp_dw_max        = (GtkSpinButton *)  gtk_spin_button_new ( Tpara5 ,  1  ,  0  );





//gtk_widget_set_tooltip_text (   (GtkWidget *) rp_dw0     ,"rp_dw0 /  bp_dw_scale");
//gtk_widget_set_tooltip_text (   (GtkWidget *) rp_dw_min    , "rp_dw_min   / bp_moment_scale");
//gtk_widget_set_tooltip_text (   (GtkWidget *) rp_dw_plus     ,"rp_dw_plus");
//gtk_widget_set_tooltip_text (   (GtkWidget *) rp_dw_minus     , "rp_dw_minus");
//gtk_widget_set_tooltip_text (   (GtkWidget *) rp_dw_max    , "rp_dw_max");


GtkWidget * algo_label  =         gtk_label_new  ("Training algorithm");
GtkWidget * rp_dw0_label  =         gtk_label_new  ("Initial weight value:");
GtkWidget * rp_dw_min_label  =         gtk_label_new  ("Minimum weight value:");
GtkWidget * rp_dw_plus_label  =         gtk_label_new  ("Weight increase value:");
GtkWidget * rp_dw_minus_label  =         gtk_label_new  ("Weight decrease value:");
GtkWidget * rp_dw_max_label  =         gtk_label_new  ("Maximum weight value:");



gtk_container_add(GTK_CONTAINER(labels_TrainingParamBox), algo_label);
gtk_container_add(GTK_CONTAINER(TrainingParamBox), TrainingMethodComboBox);


gtk_widget_set_tooltip_text ( (GtkWidget *)rp_dw0 , "The initial size of the weights.  rp_dw0");
gtk_container_add(GTK_CONTAINER(labels_TrainingParamBox), rp_dw0_label);
gtk_container_add(GTK_CONTAINER(TrainingParamBox), (GtkWidget *) rp_dw0);


gtk_widget_set_tooltip_text ( (GtkWidget *)rp_dw_min , "The minimum value a weight can be set to.  rp_dw_min");
gtk_container_add(GTK_CONTAINER(labels_TrainingParamBox), rp_dw_min_label);
gtk_container_add(GTK_CONTAINER(TrainingParamBox),  (GtkWidget *) rp_dw_min);


gtk_widget_set_tooltip_text ( (GtkWidget *)rp_dw_plus , "This is how much a weight  can increase by each iteration. rp_dw_plus");
gtk_container_add(GTK_CONTAINER(labels_TrainingParamBox), rp_dw_plus_label);
gtk_container_add(GTK_CONTAINER(TrainingParamBox), (GtkWidget *) rp_dw_plus);

gtk_widget_set_tooltip_text ( (GtkWidget *)rp_dw_minus , "This is the quanity that can be subtracted from weight through each iteration. rp_dw_minus");
gtk_container_add(GTK_CONTAINER(labels_TrainingParamBox), rp_dw_minus_label);
gtk_container_add(GTK_CONTAINER(TrainingParamBox),  (GtkWidget *) rp_dw_minus);

gtk_widget_set_tooltip_text ( (GtkWidget *)rp_dw_max , "The Maximum value any weight can be set to. rp_dw_max");
gtk_container_add(GTK_CONTAINER(labels_TrainingParamBox), rp_dw_max_label);
gtk_container_add(GTK_CONTAINER(TrainingParamBox),  (GtkWidget *) rp_dw_max);

////////////////////////////////////////////////////
//NETWORK TOPOLOGY BOX
///////////////////////////////////////////////////

ActivationFunctionComboBox = gtk_combo_box_new_text();
gtk_combo_box_append_text( GTK_COMBO_BOX(ActivationFunctionComboBox), "IDENTITY" );
gtk_combo_box_append_text( GTK_COMBO_BOX(ActivationFunctionComboBox), "SIGMOID_SYM" );
gtk_combo_box_append_text( GTK_COMBO_BOX(ActivationFunctionComboBox), "GAUSSIAN" );

g_signal_connect( G_OBJECT(ActivationFunctionComboBox), "changed",
                      G_CALLBACK(  settings_function ), NULL );
GtkAdjustment *fparam_adj_one;
GtkAdjustment *fparam_adj_two;
//fparam_adj_one = (GtkAdjustment *) gtk_adjustment_new (2.500, 0.0, 5.0, 0.001, 0.1, 0.1);
//GtkAdjustment*  test = gtk_adjustment_new(0,0,  120,  1 ,0,0);
fparam_adj_one = (GtkAdjustment *) gtk_adjustment_new (1, -10.0,120, 0.0001, 0, 0);
fparam_adj_two = (GtkAdjustment *) gtk_adjustment_new (1, -10.0,120, 0.0001, 0, 0);
alpha_activation        =   (GtkSpinButton *) gtk_spin_button_new (   fparam_adj_one ,  1  ,  4  );
beta_activation        =   (GtkSpinButton *) gtk_spin_button_new (   fparam_adj_two ,  1  ,  4  );

gtk_widget_set_tooltip_text (   (GtkWidget *) alpha_activation     , "alpha_activation");
gtk_widget_set_tooltip_text (   (GtkWidget *) beta_activation     , "beta activation");
 // GtkWidget *alpha_activation;
 // GtkWidget *beta_activation;

                         //     freeParamActiOne =           SpinButton(1.0, 100.0 , 1.0);
 GtkWidget * activation_label  =         gtk_label_new  ("activation function:");
 GtkWidget * alpha_label  =         gtk_label_new  ("sigmoid alpha:"); 
 GtkWidget * beta_label  =         gtk_label_new  ("sigmoid beta:");  

  gtk_container_add(GTK_CONTAINER(labels_NetworkTopologyBox), activation_label);
 gtk_container_add(GTK_CONTAINER(NetworkTopologyBox), ActivationFunctionComboBox);

   gtk_container_add(GTK_CONTAINER(labels_NetworkTopologyBox), alpha_label);
 gtk_container_add(GTK_CONTAINER(NetworkTopologyBox), (GtkWidget *) alpha_activation);

   gtk_container_add(GTK_CONTAINER(labels_NetworkTopologyBox), beta_label);
 gtk_container_add(GTK_CONTAINER(NetworkTopologyBox), (GtkWidget *) beta_activation);

////////////////////////////////////////////////////
//NETWORK LAYERsS BOX
///////////////////////////////////////////////////
GtkAdjustment *layer_adj;
GtkAdjustment *neurons_adj;
layer_adj = (GtkAdjustment *) gtk_adjustment_new (1, 0,120, 1, 0, 0);
neurons_adj = (GtkAdjustment *) gtk_adjustment_new (12, 2,10000, 1, 0, 0);






hidden_layer_spin              =   (GtkSpinButton *) gtk_spin_button_new (   layer_adj ,  1  , 0  );
hidden_layer_neurons_spin      =   (GtkSpinButton *) gtk_spin_button_new (   neurons_adj ,  1  ,  0  );

GtkWidget * hiddenlayers_label  =         gtk_label_new  ("Hidden Layers:");  
GtkWidget * neurons_label  =         gtk_label_new  ("Neurons per hidden layer:"); 


gtk_container_add(GTK_CONTAINER(labels_NetworkLayerBox ), hiddenlayers_label);
gtk_container_add(GTK_CONTAINER(NetworkLayerBox ), (GtkWidget *) hidden_layer_spin );

gtk_container_add(GTK_CONTAINER(labels_NetworkLayerBox ), neurons_label );
gtk_container_add(GTK_CONTAINER(NetworkLayerBox), (GtkWidget *)  hidden_layer_neurons_spin );



////////////////////////////////////////////////////////////////////////////
//TRAIN AND TEST BOX
////////////////////////////////////////////////////////////////////////////
   //TrainButton = gtk_button_new_with_label ("TRAIN");

//g_signal_connect(G_OBJECT(TrainButton), "clicked",
   //   G_CALLBACK( trainNetwork ), NULL);


   //TestButton = gtk_button_new_with_label ("TEST");

//g_signal_connect(G_OBJECT(TestButton), "clicked",
  //    G_CALLBACK( test_network ), NULL);
 // gtk_container_add(GTK_CONTAINER(TrainTestButtonBox),TrainButton);
 // gtk_container_add(GTK_CONTAINER(TrainTestButtonBox), TestButton);


////////////////////////////////////////////////////////////////////////////
//LOAD AND SAVE BUTTON
////////////////////////////////////////////////////////////////////////////


 //LoadButton = gtk_button_new_with_label ("LOAD");

//g_signal_connect(G_OBJECT(LoadButton), "clicked",
 //     G_CALLBACK(load_network), NULL);


 //SaveButton = gtk_button_new_with_label ("SAVE");

//g_signal_connect(G_OBJECT(SaveButton), "clicked",
  //    G_CALLBACK(save_network), NULL);

//SaveTextBox =  gtk_entry_new    ();

 // gtk_container_add(GTK_CONTAINER(LoadSaveButtonBox), LoadButton);
 // gtk_container_add(GTK_CONTAINER(LoadSaveButtonBox), SaveButton);
  //gtk_container_add(GTK_CONTAINER(LoadSaveButtonBox), SaveTextBox);


/////////////////////////////////////////////////////////////////////////////
//KFoldButtonBox  
/////////////////////////////////////////////////////////////////////////////


KFoldButton = gtk_button_new_with_label ("KFOLD TRAIN");


Train_again_button = gtk_button_new_with_label ("Repeat Training");

//This prevents a user the train again button, before data has been gathered.
gtk_widget_set_sensitive(Train_again_button, false);

GtkAdjustment *kfold_adj;
kfold_adj = (GtkAdjustment *) gtk_adjustment_new (2, 2,100, 1, 0, 0);

number_of_KFolds       =   (GtkSpinButton *) gtk_spin_button_new ( kfold_adj ,  1  ,  0  );


g_signal_connect(G_OBJECT(KFoldButton), "clicked", G_CALLBACK(check_for_folders), NULL);
g_signal_connect(G_OBJECT(Train_again_button), "clicked", G_CALLBACK(train_k_fold_again ), NULL);

 

 GtkWidget * kfolds_label  =         gtk_label_new  ("Number of K-Folds:"); 

 gtk_container_add(GTK_CONTAINER(labels_KFoldButtonBox ), gtk_label_new  ("   "));
 gtk_container_add(GTK_CONTAINER(KFoldButtonBox), KFoldButton );

  gtk_container_add(GTK_CONTAINER(labels_KFoldButtonBox ), gtk_label_new  ("   "));
  gtk_container_add(GTK_CONTAINER(KFoldButtonBox), Train_again_button );

 gtk_container_add(GTK_CONTAINER(labels_KFoldButtonBox ), kfolds_label);
gtk_container_add(GTK_CONTAINER(KFoldButtonBox), (GtkWidget *) number_of_KFolds);


/////////////////////////////////////////////////////////////////////////////
//TEST RESULTS BOX
/////////////////////////////////////////////////////////////////////////////






  //Test_results_text_box  =  gtk_frame_new   ("TEST RESULTS");

// GtkAdjustment *testres_horiz;
// GtkAdjustment *testres_vert;
//testres_horiz = (GtkAdjustment *) gtk_adjustment_new (0.0, 0.0, 101.0, 0.1, 1.0, 1.0);
//testres_vert = (GtkAdjustment *) gtk_adjustment_new (0.0, 0.0, 101.0, 0.1, 1.0, 1.0);
 //Test_results_text_box  = (GtkScrolledWindow *) gtk_scrolled_window_new     (NULL,NULL);
 //gtk_widget_set_usize((GtkWidget *)Test_results_text_box, 250, 150);



   //GtkWidget *  testing_label =   gtk_label_new         ("test");
   
//gtk_container_add(GTK_CONTAINER(Test_results_text_box ), testing_label);
   // gtk_scrolled_window_set_policy (GTK_SCROLLED_WINDOW (Test_results_text_box ),
         //                           GTK_POLICY_AUTOMATIC, 
          //                          GTK_POLICY_AUTOMATIC);
   

//gtk_container_add(GTK_CONTAINER(Test_result_box),(GtkWidget *) Test_results_text_box);
//gtk_widget_show((GtkWidget *)Test_results_text_box);
  



/////////////////////////////////////////////////////////////////////////////
//MERGING ALL  
/////////////////////////////////////////////////////////////////////////////

gtk_container_add(GTK_CONTAINER(SetupBox),labels_TrainingDataBox);
gtk_container_add(GTK_CONTAINER(SetupBox),TrainingDataBox);
 
gtk_container_add(GTK_CONTAINER(SetupBox),labels_ImageProcessBox);
gtk_container_add(GTK_CONTAINER(SetupBox),ImageProcessBox);

gtk_container_add(GTK_CONTAINER(SetupBox),labels_TermCriteriaBox );
gtk_container_add(GTK_CONTAINER(SetupBox),TermCriteriaBox );

gtk_container_add(GTK_CONTAINER(SetupBox),labels_TrainingParamBox);
gtk_container_add(GTK_CONTAINER(SetupBox),TrainingParamBox);

gtk_container_add(GTK_CONTAINER(SetupBox2),labels_NetworkTopologyBox);
gtk_container_add(GTK_CONTAINER(SetupBox2),NetworkTopologyBox);

gtk_container_add(GTK_CONTAINER(SetupBox2),labels_NetworkLayerBox);
gtk_container_add(GTK_CONTAINER(SetupBox2),NetworkLayerBox);
      
//gtk_container_add(GTK_CONTAINER(SetupBox),TrainTestButtonBox);
//gtk_container_add(GTK_CONTAINER(SetupBox),LoadSaveButtonBox);
gtk_container_add(GTK_CONTAINER(SetupBox2),labels_KFoldButtonBox);
gtk_container_add(GTK_CONTAINER(SetupBox2),KFoldButtonBox);


gtk_container_add(GTK_CONTAINER(Top_Layer_Box),SetupBox);
gtk_container_add(GTK_CONTAINER(Top_Layer_Box),SetupBox2);



gtk_container_add(GTK_CONTAINER(Top_Layer_Box),Test_result_box);
gtk_container_add(GTK_CONTAINER(window),Top_Layer_Box);
    /*
    ** Assign the variable "label" to a new GTK label,
    ** with the text ", world!"
    */
    //label = gtk_label_new("Hello, world!");

    /* Plot the label onto the main window */
   // gtk_container_add(GTK_CONTAINER(window), label);

gtk_widget_show (ImageProcessBox);
gtk_widget_show (TrainingDataBox);
gtk_widget_show (TermCriteriaBox);
gtk_widget_show (TrainingParamBox);
gtk_widget_show (NetworkTopologyBox);
gtk_widget_show (NetworkLayerBox);
//gtk_widget_show (TrainTestButtonBox);
//gtk_widget_show (LoadSaveButtonBox);
gtk_widget_show (Test_result_box);


    /* Make sure that everything, window and label, are visible */
    gtk_widget_show_all(window);

    /*
    ** Start the main loop, and do nothing (block) until
    ** the application is closed
    */
    gtk_main();

    return 0;
}
