/**
 * @file sound.c
 *
 * @brief Gestiona la reproducción de sonido en el modo difícil
 *
 * @author Ricardo Sánchez Zepeda
 *
 * @date 08/05/2024
*/

#include "header.h"

/**
 * @fn Plays hardmode soundtrack
 * @return void
 */
void startMusic() {
  system("aplay ./MEDIA/hercules.wav &");
}


/**
 * @fn Stops all music
 * @return void
 */
void stopMusic() {
  system("killall aplay");
}
