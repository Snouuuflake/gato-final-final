#include "header.h"

/**
 *@fn Para debugear- imprime un BOARDSTRUCT a la terminal
 *@param board BOARDSTRUCT que se va a imprimir
 *@return void
 */
void printBoard(BOARDSTRUCT board) {
  int i, j;
  char boardArr[9];
  makeBoardArray(&board, boardArr);
  for (i = 0; i < 3; i++) {
    for (j = 0; j < 3; j++) {
      g_print("%d:%c ",(i*3)+j, boardArr[(i*3)+j]);
    }
    printf("\n");
  }
}


/**
 *@fn Función que regresa un apuntador a uno de los elementos de
 * un BOARDSTRUCT como si fuera un arreglo
 *@example *getBoardItem(b, 3) es similar a b[3] con un arreglo
 *@param board Apundaor al BOARDSTRUCT a acceder
 *@index index Índice (tal como en un arreglo) del elemento que
 * se desea acceder
 *@return Un apundaor a un elemento de board, o en caso de que
 * index < 0 || index > 8, NULL
 */
char *getBoardItem(BOARDSTRUCT *board, int index) {
  switch (index) {
  case 0:
    return &(board->a);
    break;
  case 1:
    return &(board->b);
    break;
  case 2:
    return &(board->c);
    break;
  case 3:
    return &(board->d);
    break;
  case 4:
    return &(board->e);
    break;
  case 5:
    return &(board->f);
    break;
  case 6:
    return &(board->g);
    break;
  case 7:
    return &(board->h);
    break;
  case 8:
    return &(board->i);
    break;
  default:
    printf("Error: attempted to access index (%d)\n", index);
    return NULL; // causes segfault so i know where I messed up. Can also be validted as a boolean
    break;
  }
}

/**
 *@fn Copia cada elemento de un BOARDSTRUCT a un arreglo
 *@param board Apuntador a un BOARDSTRUCT
 *@param array Un arreglo
 *@return void
 */
void makeBoardArray(BOARDSTRUCT *board, char array[]) {
  int i;
  for (i = 0; i < 9; i++) {
    array[i] = (*getBoardItem(board, i));
  }
}

/**
 *@fn Regresa la pieza correspondiente al número de jugador
 *@param index Número de jugador
 *@return 'X' si index==0 y 'O' si index==1
 */
char getPiece(int index) {
  char arr[] = {'X','O'};
  return arr[index];
}

/**
 *@fn Revisa si terminaría el juego al colocar la pieza del
 * jugador piece en el tablero square [0,8]. Si si, regresa
 * 10; un valor de califiación a la jugada utilizado en el
 * algoritmo que utiliza la IA. Si no, regresa 0.
 *@param board BOARDSTRUCT donde se va a probar la jugada
 *@param piece Numero de jugador cuyo tiro se va a simular [0,1]
 *@param square Índice de espacio donde se va a simular jugar [0,8]
 *@return 10 si terminaría el juego, 0 si no
 */
int getScore(BOARDSTRUCT board, int piece, int square) {
  char arr[9];
  char c;
  char state;

  c = getPiece(piece);
  *(getBoardItem(&board,square)) = c;

  makeBoardArray(&board, arr);

  state = estadoTablero(arr);

  if (state) {
    return 10;
  } else {
    return 0;
  }
}


/**
 *@fn Función que, con un algoritmo basado en Minimax (no es una copia exacta),
 * intenta determinar dónde debería jugar la computadora.
 * El algoritmo es recursivo. Dado un estado de juego, prueba todas las posibles
 * jugadas hasta encontrar la que más le convenga*, al encontrar esta, recursivamente
 * simula la jugada optima del oponente y, usando el nuevo tablero, de nuevo intenta
 * encontrar su jugada optima. Si la compu ganaría, regresa un valor de 10, si perdería,
 * -10, y si no pasa nada, 0 + la siguiente jugada ideal recursivamente.
 * Cada instancia de la función recibe un valor de profunidad, el cual se le resta al
 * resultado, de tal manera que las jugadas que ganen más pronto generen tengan
 * calificaciones más altas.
 *
 *@param board El tablero donde se va a simular la jugadar
 *@param square El indice en el tablero de la jugada a simular [0,8]
 *@param piece Indice del jugador actual (este cambia cada siguiente turno que se
 * simula recursivamente) [0,1]
 *@param ogpiece Indice de la pieza original; con la que inicia la recursión; la pieza
 * que realmente va a usar la computadora [0,1]
 *@param depth Valor de profunidad. Empieza en 0 e incrementa por 1 con cada recursión
 *
 *@return La calificación de la jugada; entre mayor sea, más conveniente es.
 * 
 */
int mm2(BOARDSTRUCT board, int square, int piece, int ogpiece, int depth) {
  char c = 0; // paranoia
  int i = 0;
  int crit = 0;
  int chosenMove = -1;
  int tmpScore = 0;
  int res = 0;
  int s = 0;
  int nextPiece = 0;

  s = getScore(board, piece, square);
  if (s == ogpiece) {
    res = (10 - depth);
  } else if (s) {
    res = (10 - depth) * (-1);
  }
  else {
    res = 0;
  }

  *(getBoardItem(&board,square)) = getPiece(piece);

  nextPiece = (piece + 1) % 2;

  for (i = 0; i < 9; i++) {
    if ((*getBoardItem(&board, i)) == ' ') {
      if (chosenMove == -1) {
        chosenMove = i;
        crit = getScore(board, nextPiece, i);
      } else {
        
        tmpScore = getScore(board, nextPiece, i);
        if (tmpScore > crit) {
          crit = tmpScore;
          chosenMove = i;
        }
      }
    }
  }

  if (chosenMove == -1 || getScore(board, piece, square)) {
    return (res);
  } else {
    return (res) + mm2(board, chosenMove, (piece+1)%2, ogpiece, (depth+1));
  }
  
}

// I'm keeping this around for the sake of testing.
//
// int main(void) {
// BOARDSTRUCT realBoard;
// char boardArr[9];
// int i;
// int j;
// int input;
// int cpuInput;
// int tmpScore;
// int highestScore;
// char b;
// 
// srand(time(NULL)); 
// 
// for (i = 0; i < 9; i++) {
    // *(getBoardItem(&realBoard, i)) = ' ';
// }
  // // 0 1 2
  // // 3 4 5
  // // 6 7 8
// 
// makeBoardArray(&realBoard, boardArr);
// while (!estadoTablero(boardArr)) {
// for (i = 0; i < 3; i++) {
// for (j = 0; j < 3; j++) {
// printf("%d:%c ",(i*3)+j, boardArr[(i*3)+j]);
// }
// printf("\n");
// }
// 
// b = 0;
// while (!b) {
// __fpurge(stdin);
// scanf("%d", &input);
// if (*getBoardItem(&realBoard, input) == ' ') {
// b = 1;
// (*getBoardItem(&realBoard, input)) = getPiece(0);
// }
// }
// 
// makeBoardArray(&realBoard, boardArr);
// b = 0;
// 
// if (!estadoTablero(boardArr)) {
// for (i = 0; i < 9; i++) {
// if (*getBoardItem(&realBoard, i) == ' ') {
          // //printf("score of %d:%d\n", i, minimax(realBoard, i, 1, 1, 0));
          // //tmpScore = minimax(realBoard, i, 1, 1, 0);
          // //tmpScore = minimax(realBoard, i, 1, 1, 1);
// tmpScore = mm2(realBoard, i, 1, 1, 1);
          // //printf("\n");
// printf("%d: %d\n", i, tmpScore);
// 
// 
// if (!b) {
// b = 1;
// cpuInput = i;
// highestScore = tmpScore;
// } else if (tmpScore > highestScore) {
// cpuInput = i;
// highestScore = tmpScore;
// }
          // // we get the highest score and if theres multiple, we pick a random one
          // // or we just use the last one because im lazy
// }
// }
// (*getBoardItem(&realBoard, cpuInput)) = getPiece(1);
// makeBoardArray(&realBoard, boardArr);
// }
// }
// 
// printf("final gametsate:\n");
// printBoard(realBoard);
// 
// return 0;
// }
// 
