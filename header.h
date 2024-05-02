/**
 * Area funcional (R)
*/
#include <gtk-2.0/gtk/gtk.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * La ficha de cada jugador se infiere de su índice.
 */
typedef struct def_jugador {
  char nombre[256];
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
  char tablero[9];
  ESTADO *inicio;
  JUGADOR jugadores[2];
  int jugadorActual;

  GtkWidget *playingImg; // <-- L
  GtkWidget *playingBox; // <-- L

  gboolean hardMode; // bool
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
  GtkWidget *image; // <-- L
  int id;
} GSTRUCT;

/**
 * estadoTablero.c (M)
 */
char estadoTablero(char tab[9]);

/**
 * ai.c (R)
 */
/**
 * Esencialmente una forma de mandar un
 * arreglo como variable y no apuntador
 * if that makes sense
 */
typedef struct def_boardstruct {
  char a;
  char b;
  char c;
  char d;
  char e;
  char f;
  char g;
  char h;
  char i;
} BOARDSTRUCT;

typedef struct def_mmscore { //TODO: remove- i dont think this is used
  int score;
  char exists;
} MMSCORE;


void printBoard(BOARDSTRUCT board);
char *getBoardItem(BOARDSTRUCT *board, int index);
void makeBoardArray(BOARDSTRUCT *board, char array[]);
char getPiece(int index);
int getScore(BOARDSTRUCT board, int piece, int square);
int mm2(BOARDSTRUCT board, int square, int piece, int ogpiece, int depth);

