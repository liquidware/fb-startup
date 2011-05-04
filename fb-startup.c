#include <unistd.h>
#include <sys/wait.h>
#include <gtk/gtk.h>
#include <gdk/gdkkeysyms.h>
#include <gdk/gdk.h>
#include <glade/glade.h>
#include <pthread.h>
#include <semaphore.h>
#include <cairo.h>
#include <math.h>
#include <time.h>
#include <string.h>

/* Global Variables */
#define UI_FILE "/usr/share/fb-startup/fb-startup.glade"

 const gchar filename_image3_active[] = "/usr/share/fb-startup/start.png";
 const gchar filename_image3_inactive[] = "/usr/share/fb-startup/stop.png";
 const gchar filename_image2_active[] = "/usr/share/fb-startup/45-on.png"; 
 const gchar filename_image2_inactive[] = "/usr/share/fb-startup/45-off.png";
 const gchar filename_image1_active[] = "/usr/share/fb-startup/33-on.png";
 const gchar filename_image1_inactive[] = "/usr/share/fb-startup/33-off.png";

GladeXML                *xml;
GtkWidget               *window;
GdkColor 	             g_col;

GtkWidget               *image3;
GtkWidget               *image2;
GtkWidget               *image1;

GtkWidget               *eventbox3;
GtkWidget               *eventbox2;
GtkWidget               *eventbox1;

int image3_button_state = 0;
int image2_button_state = 0;
int image1_button_state = 0;

int FirstIdleEvent = 1;
int Speed = 0;

void SetSpeed(int value)
{
 if (value == 35) {
     image2_button_state = 0;
     gtk_image_set_from_file(GTK_IMAGE(image1),(const gchar*)filename_image1_active);
     image1_button_state = 0;
     gtk_image_set_from_file(GTK_IMAGE(image2),(const gchar*)filename_image2_inactive);   

 } else if (value == 45) {
     image1_button_state = 0;
     gtk_image_set_from_file(GTK_IMAGE(image2),(const gchar*)filename_image2_active);
     image2_button_state = 0;
     gtk_image_set_from_file(GTK_IMAGE(image1),(const gchar*)filename_image1_inactive);
 }
}

/* Use event boxes to create buttons */
void on_eventbox1_button_release_event(GtkWidget      *event_box,
                                       GdkEventButton *event,
                                       gpointer        data)
{
  if (image3_button_state == 0) {
     image3_button_state = 1;
     gtk_image_set_from_file(GTK_IMAGE(image3),(const gchar*)filename_image3_inactive);
     g_print("Started\n");
  } else {
     image3_button_state = 0;
     gtk_image_set_from_file(GTK_IMAGE(image3),(const gchar*)filename_image3_active);
     g_print("Stopped\n");
  }
}

void on_eventbox2_button_release_event(GtkWidget      *event_box,
                                       GdkEventButton *event,
                                       gpointer        data)
{
  if (image2_button_state == 0) {
      SetSpeed(35);
      g_print("Switched speed to 35\n");
  }
}

void on_eventbox3_button_release_event(GtkWidget      *event_box,
                                       GdkEventButton *event,
                                       gpointer        data)
{
  if (image1_button_state == 0) {
      SetSpeed(45);
      g_print("Switched speed to 45\n");
  }
}


/* Get rid of the cursor */
gboolean program_idler(void) {
    if (FirstIdleEvent) {
        GdkCursor * cursor;
        GdkWindow *win;
    
        win = gtk_widget_get_window(window);
        cursor = gdk_cursor_new (GDK_BLANK_CURSOR);
        gdk_window_set_cursor (win, cursor);

        FirstIdleEvent = 0;
    }
}

int main (int argc, char *argv[])
{
    gtk_init (&argc, &argv);

    xml = glade_xml_new(UI_FILE, NULL, NULL);

    /* Connect the signals in the interface */
    glade_xml_signal_autoconnect(xml);

     window = glade_xml_get_widget(xml, "window");

     image3 = glade_xml_get_widget(xml, "image3");
     image2 = glade_xml_get_widget(xml, "image2");
     image1 = glade_xml_get_widget(xml, "image1");

     eventbox3 = glade_xml_get_widget(xml, "eventbox3");
     eventbox2 = glade_xml_get_widget(xml, "eventbox2");
     eventbox1 = glade_xml_get_widget(xml, "eventbox1");
   
    /* Change the background color */
    g_col.red=0;g_col.green=0;g_col.blue=0;
    gtk_widget_modify_bg (GTK_WIDGET(eventbox1), GTK_STATE_NORMAL,&g_col);
    gtk_widget_modify_bg (GTK_WIDGET(eventbox2), GTK_STATE_NORMAL,&g_col);
    gtk_widget_modify_bg (GTK_WIDGET(eventbox3), GTK_STATE_NORMAL,&g_col);

    gtk_widget_show (window);   

    /* Add idle routines */
    g_idle_add((GSourceFunc)program_idler, NULL);
    gtk_main ();

  return 0;
}
