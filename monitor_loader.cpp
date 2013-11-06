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
 
 GtkSpinButton   *mode;
 GtkSpinButton   *number_of_camera_spinner;

 char  *dir1;

 char  *dir2;

 char  *dir3;

 char  *dir4;

 char  *dir5;

 char  *dir6;
 






void get_network_name1(GtkWidget *widget, gpointer data)
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
                         // string  sfilename;
                          dir1 = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(dialog));

                          

                       }
gtk_widget_destroy(dialog);

}

void get_network_name2(GtkWidget *widget, gpointer data)
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
                          //string  sfilename;
                          dir2 = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(dialog));

                       }
gtk_widget_destroy(dialog);

}

void get_network_name3(GtkWidget *widget, gpointer data)
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
                       //   string  sfilename;
                          dir3 = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(dialog));

                       }
gtk_widget_destroy(dialog);

}

void get_network_name4(GtkWidget *widget, gpointer data)
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
                      //    string  sfilename;
                          dir4 = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(dialog));

                       }
gtk_widget_destroy(dialog);

}

void get_network_name5(GtkWidget *widget, gpointer data)
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
                         // string  sfilename;
                          dir5 = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(dialog));

                       }
gtk_widget_destroy(dialog);

}

void get_network_name6(GtkWidget *widget, gpointer data)
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
                          //string  sfilename;
                          dir6 = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(dialog));

                    }
gtk_widget_destroy(dialog);

}





void Start_monitor(GtkWidget *widget, gpointer data)
{


int cams = (int) gtk_spin_button_get_value(number_of_camera_spinner);
int md = (int )gtk_spin_button_get_value(mode);



    
    string  d1;
    string  d2;
    string  d3;
    string  d4;
    string  d5;
    string  d6;

    d1.assign(dir1);



       
        


 stringstream config;
config<< "./mon" <<" ";
        //add number to the stream
if(md ==1)
{
   config<< md <<" "<< cams  <<" "<< d1 ; //" "  << dir2 << " "  << dir3 << " "  << dir4 << " "  << dir5 << " "  << dir6 << " "
}

if(md ==2)
{

   
  //d1.assign(dir1);
   d2.assign(dir2);
   d3.assign(dir3);
   d4.assign(dir4);
   d5.assign(dir5);
   d6.assign(dir6);

   config << md <<" "<< cams  <<" "<< d1 << " "  << d2 << " "  << d3 << " "  << d4 << " "  << d5 << " "  << d6 << " ";
  
}

   //save_network("./saves", file.str() );

string mconfig;
//monitor_config << config;

mconfig.assign(config.str());
char* monitor_config  = (char*)mconfig.c_str();
system(monitor_config);


}



/////////////////////BEGINS MAIN////////////////////////////////////////////////////////////////////////////////
int main (int argc, char *argv[])
{
    //GtkWidget *window;

GtkWidget *TopBox;//hold all other boxes


GtkWidget *LoadStartButtonBox;//holds positive and negative folder address for image files


GtkWidget *LoadButton1;
GtkWidget *LoadButton2;
GtkWidget *LoadButton3;
GtkWidget *LoadButton4;
GtkWidget *LoadButton5;
GtkWidget *LoadButton6;

GtkWidget *StartButton;


gtk_init(&argc, &argv);

    /* Create the main, top level window */
window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
gtk_window_set_title(GTK_WINDOW(window), "Load Networks");


g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

TopBox = gtk_hbutton_box_new ();
LoadStartButtonBox = gtk_vbutton_box_new ();


GtkAdjustment *mode_Adj         =  (GtkAdjustment *)     gtk_adjustment_new (1, 1, 2, 1, 0, 0);
 mode     =  (GtkSpinButton *)     gtk_spin_button_new( mode_Adj   ,  1  , 0  );

 gtk_widget_set_tooltip_text ( (GtkWidget *)mode  , "Set mode 1: test    2:expression detection");
gtk_container_add(GTK_CONTAINER(LoadStartButtonBox),(GtkWidget *) mode );


  GtkAdjustment *cam_adj         =  (GtkAdjustment *)     gtk_adjustment_new (1, 1, 10, 1, 0, 0);
  number_of_camera_spinner       =  (GtkSpinButton *)     gtk_spin_button_new( cam_adj  ,  1  ,  0  );
 


gtk_widget_set_tooltip_text ( (GtkWidget *)number_of_camera_spinner , "Set the number_of_camera(s)");
gtk_container_add(GTK_CONTAINER(LoadStartButtonBox),(GtkWidget *) number_of_camera_spinner);



 LoadButton1 = gtk_button_new_with_label ("Smile / Test");
 LoadButton2 = gtk_button_new_with_label ("Fear");
 LoadButton3 = gtk_button_new_with_label ("Sadness");
 LoadButton4 = gtk_button_new_with_label ("Disgust");
 LoadButton5 = gtk_button_new_with_label ("Anger");
 LoadButton6 = gtk_button_new_with_label ("Surprise");

 StartButton = gtk_button_new_with_label ("START");

g_signal_connect(G_OBJECT(LoadButton1), "clicked",
      G_CALLBACK(get_network_name1), NULL);

g_signal_connect(G_OBJECT(LoadButton2), "clicked",
      G_CALLBACK(get_network_name2), NULL);

g_signal_connect(G_OBJECT(LoadButton3), "clicked",
      G_CALLBACK(get_network_name3), NULL);

g_signal_connect(G_OBJECT(LoadButton4), "clicked",
      G_CALLBACK(get_network_name4), NULL);

g_signal_connect(G_OBJECT(LoadButton5), "clicked",
      G_CALLBACK(get_network_name5), NULL);

g_signal_connect(G_OBJECT(LoadButton6), "clicked",
      G_CALLBACK(get_network_name6), NULL);






      g_signal_connect(G_OBJECT(StartButton), "clicked",
      G_CALLBACK(Start_monitor), NULL);


 gtk_container_add(GTK_CONTAINER(LoadStartButtonBox), LoadButton1);
 gtk_container_add(GTK_CONTAINER(LoadStartButtonBox), LoadButton2);
 gtk_container_add(GTK_CONTAINER(LoadStartButtonBox), LoadButton3);
 gtk_container_add(GTK_CONTAINER(LoadStartButtonBox), LoadButton4);
 gtk_container_add(GTK_CONTAINER(LoadStartButtonBox), LoadButton5);
 gtk_container_add(GTK_CONTAINER(LoadStartButtonBox), LoadButton6);




 
  gtk_container_add(GTK_CONTAINER(LoadStartButtonBox), StartButton);



/////////////////////////////////////////////////////////////////////////////
//MERGING ALL
/////////////////////////////////////////////////////////////////////////////

gtk_container_add(GTK_CONTAINER(TopBox),LoadStartButtonBox);


gtk_container_add(GTK_CONTAINER(window),TopBox);


gtk_widget_show (LoadStartButtonBox);


gtk_widget_show_all(window);


    gtk_main();

    return 0;
}
