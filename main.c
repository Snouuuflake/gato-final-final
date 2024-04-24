#include "ttt.h"

void populateButtonArray(JUEGO *juego, GtkWidget *parent);
GtkWidget *makeButton(JUEGO *juego, int index);
void buttonCallback(GtkButton *button, gpointer data);
void onExit(GtkWidget *window, gpointer data);
char getPiece(int playerNum);
void initJuego(JUEGO *juego);
  

int main(gint argc, gchar *argv[]) {
  GtkWidget *window;
  GtkWidget *verticalbox;
  JUEGO juego;

  initJuego(&juego);

  gtk_init(&argc, &argv);

  window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
  gtk_window_set_default_size(GTK_WINDOW(window),240,200);
  gtk_container_border_width(GTK_CONTAINER(window),5);

  verticalbox = gtk_vbox_new(TRUE,5);
  populateButtonArray(&juego, verticalbox);

  // frees everything in callback
  gtk_signal_connect(GTK_OBJECT(window),"destroy",GTK_SIGNAL_FUNC(onExit),&juego);
  gtk_container_add(GTK_CONTAINER(window), verticalbox);
  gtk_widget_show_all(window);

  gtk_main();

  return 0;
}

/**
 * makes buttons, puts their addresses in juego->buttons, and puts them in parent box thing
 */
void populateButtonArray(JUEGO *juego, GtkWidget *parent) {
  int i;
  for (i = 0; i < 9; i++) {
    juego->botones[i] = makeButton(juego, i);

    // |
    // \/ this is temporary way to do this
    gtk_box_pack_start(GTK_BOX(parent), juego->botones[i], TRUE, TRUE, 5);
  }
}

/**
 * Makes a pointer, returns its addres, gives it a blank label,
 * signal connects to buttonCallback with a pointer to a GSTRUCT
 * containing index as data
 *
 * Assumes that juego->gsturctArr[index] has already been allocated
 */
GtkWidget *makeButton(JUEGO *juego, int index) {
  GtkWidget *button;
  GSTRUCT *buttonData;

  buttonData = (GSTRUCT *) juego->gstructArr[index];
  buttonData->juego = juego;
  buttonData->id = index;

  button = gtk_button_new_with_label(" ");
  gtk_signal_connect(GTK_OBJECT(button), "clicked", GTK_SIGNAL_FUNC(buttonCallback), buttonData);

  return button;
}

/**
 *
 */
void buttonCallback(GtkButton *button, gpointer data) {
  GSTRUCT *buttonData;
  char labelBuffer[2];

  buttonData = (GSTRUCT *) data;
  labelBuffer[1] = 0;

  if (buttonData->juego->tablero[ buttonData->id ] == ' ') {
    buttonData->juego->tablero[ buttonData->id ] = getPiece(buttonData->juego->jugadorActual);
    labelBuffer[0] = getPiece(buttonData->juego->jugadorActual);
    gtk_button_set_label(GTK_BUTTON(button), labelBuffer);
  }
  g_print("id: %d, val: %c\n", buttonData->id, buttonData->juego->tablero[ buttonData->id ]);
}
   
/**
 * Muy buenas prácticas
 */
char getPiece(int playerNum) {
  char arr[] = {'X', 'O'};
  return arr[playerNum];
}

void initJuego(JUEGO *juego) {
  int i;
  char strBuffer[64];

  for (i = 0; i < 9; i++) {
    juego->gstructArr[i] = (void *) malloc(sizeof(GSTRUCT));
  }

  for (i = 0; i < 9; i++) {
    juego->tablero[i] = ' ';
  }

  juego->inicio = NULL;

  for (i = 0; i < 2; i++) {
    sprintf(strBuffer, "Jugador No.%d", i);
    strcpy(juego->jugadores[i].nombre, strBuffer);
    juego->jugadores[i].esCPU = 0;
  }

  juego->jugadorActual = 0;

}


void onExit(GtkWidget *window, gpointer data) {
  int i;
  JUEGO *juego;
  
  juego = (JUEGO *) data;
  for (i = 0; i < 9; i++) {
    free(juego->gstructArr[i]);
  }

  gtk_main_quit();
}
