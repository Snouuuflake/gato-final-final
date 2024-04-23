#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <gtk/gtk.h>

typedef struct def_jugador {
  char nombre[256];
  char pieza;
  char esCPU;
} JUGADOR;

/**
 * Estado o "judada"
 * Formato: "XXOXXOXOO"
 */
typedef struct def_estado {
  char val[9];
  struct def_estado *sigiente;
  struct def_estado *anterior;
} ESTADO;

typedef struct def_juego {
  GtkWidget *botones[9];
  void *gstructArr[9];
  char **tablero;
  ESTADO *inicio;
  JUGADOR jugadores[2];
  int juadorActual;
} JUEGO;

/**
 * Argumento del callback de los botones
 * del tablero
 *
 * Cuando presionas un botón, manda esta
 * estructura, con el id del botón que
 * se presionó.
 *
 * Cuando la ia tira, cambia el valor de
 * id al botón que quiere presionar y
 * vuelve a llamar la función de cuando
 * se presiona un botón.
 */
typedef struct def_gstruct {
  JUEGO *juego;
  int id;
} GSTRUCT;
  
