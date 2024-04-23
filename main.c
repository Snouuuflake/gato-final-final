#include "ttt.h"

void populateButtonArray(JUEGO *juego, GtkWidget *parent);
GtkWidget *makeButton(JUEGO *juego, int index);
void buttonCallback(GtkButton *button, gpointer data);

int main(gint argc, gchar *argv[]) {
  GtkWidget *window;
  GtkWidget *verticalbox;
  JUEGO juego;

  gtk_init(&argc, &argv);

  window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
  gtk_window_set_default_size(GTK_WINDOW(window),240,200);
  gtk_container_border_width(GTK_CONTAINER(window),5);

  verticalbox = gtk_vbox_new(TRUE,5);
  populateButtonArray(&juego, verticalbox);

  gtk_container_add(GTK_CONTAINER(window), verticalbox);
  gtk_widget_show_all(window);

  gtk_main();

  return 0;
}

/**
 * makes buttons, puts them in array, and puts them in parent box thing
 */
void populateButtonArray(JUEGO *juego, GtkWidget *parent) {
  int i;
  for (i = 0; i < 9; i++) {
    juego->gstructArr[i] = (void *) malloc(sizeof(GSTRUCT));

    juego->botones[i] = makeButton(juego, i);
    // \/ this is temporary
    gtk_box_pack_start(GTK_BOX(parent), juego->botones[i], TRUE, TRUE, 5);
  }
}

GtkWidget *makeButton(JUEGO *juego, int index) {
  GtkWidget *button;
  GSTRUCT *buttonData;
  char buffer[2];
  // making label text
  buffer[1] = 0;
  sprintf(buffer, "%d", index);

  buttonData = (GSTRUCT *) juego->gstructArr[index];
  buttonData->juego = juego;
  buttonData->id = index;

  button = gtk_button_new_with_label(buffer);
  gtk_signal_connect(GTK_OBJECT(button), "clicked", GTK_SIGNAL_FUNC(buttonCallback), buttonData);

  return button;
}

void buttonCallback(GtkButton *button, gpointer data) {
  g_print("id: %d\n", ((GSTRUCT *) data)->id);
}
   
