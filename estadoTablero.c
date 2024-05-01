#include "header.h"


/**
 *@fn función que revisa en que estado esta el tablero de juego; si contunua, es empate o hay algún ganador
 *@param recive la una cadena de caracteres que tiene la información de que tiene cada posición del tablero
 *@return en caso de que haya un ganador, regresa el símbolo de quien ganó, si es empate regresa 'g' de gato, si no es gato ni hay ganador regresa ' '
 */
char estadoTablero(char tab[9]){
  int i, cont=0;


  for(i=0; i < 9; i=i+3){
    if(tab[i] == tab[i+1] && tab[i] == tab[i+2]){
      if(tab[i] != ' '){
	return tab[i];
      }
    }
  }
  for(i = 0; i < 3; i++){
    if(tab[i] == tab[i+3] && tab[i] == tab[i+6]){
      if(tab[i] != ' '){
	return tab[i];
      }
    }
  }
  if(tab[0] == tab[4] && tab[0] == tab[8]){
    if(tab[0] != ' '){
      return tab[0];
    }
  }
  if(tab[2] == tab[4] && tab[2] == tab[6]){
    if(tab[2] != ' '){
      return tab[2];
    }
  }
  for(i = 0; i < 9; i++){
    if(tab[i] == ' '){
      cont++;
    }
  }
  if(cont == 0){
    return 'g';
  }
  else if(cont != 0){
    return 0;
  }  
}
