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
 GtkSpinButton   *number_of_camera_spinner;

 char  *dir1;

 char  *dir2;

 char  *dir3;

 char  *dir4;

 char  *dir5;

 char  *dir6;
 






void get_network_name(GtkWidget *widget, gpointer data)
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
                          dir1 = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(dialog));




            // sfilename.assign(file);
              // char* filename_  = (char*)sfilename.c_str();



                           //  mine.load_network( filename_);



                       }
gtk_widget_destroy(dialog);

}





void Start_monitor(GtkWidget *widget, gpointer data)
{
system("./monl ");


}

void Start_trainer(GtkWidget *widget, gpointer data)
{
system("./trainer ");


}



/////////////////////BEGINS MAIN////////////////////////////////////////////////////////////////////////////////
int main (int argc, char *argv[])
{
    //GtkWidget *window;

GtkWidget *TopBox;//hold all other boxes


GtkWidget *StartButtonBox;//holds positive and negative folder address for image files


GtkWidget *Monitor_button;
GtkWidget *Trainer_button;




gtk_init(&argc, &argv);

    /* Create the main, top level window */
window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
gtk_window_set_title(GTK_WINDOW(window), "Main");
g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

TopBox = gtk_hbutton_box_new ();
StartButtonBox =gtk_hbutton_box_new ();

 





 Monitor_button = gtk_button_new_with_label ("Monitoring");

 Trainer_button = gtk_button_new_with_label ("Training");



g_signal_connect(G_OBJECT(Monitor_button), "clicked",
      G_CALLBACK(Start_monitor), NULL);

 g_signal_connect(G_OBJECT(Trainer_button), "clicked",
      G_CALLBACK(Start_trainer), NULL);


  gtk_container_add(GTK_CONTAINER(StartButtonBox), Monitor_button);
  gtk_container_add(GTK_CONTAINER(StartButtonBox), Trainer_button);



gtk_container_add(GTK_CONTAINER(TopBox),StartButtonBox);


gtk_container_add(GTK_CONTAINER(window),TopBox);


gtk_widget_show (StartButtonBox);


gtk_widget_show_all(window);


    gtk_main();

    return 0;
}
