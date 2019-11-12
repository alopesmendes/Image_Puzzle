#include <stdio.h>
#include <stdlib.h>
#include <MLV/MLV_all.h>
#include "couleur.h"
#include "aide.h"

void message_aide(int taille_x, int taille_y) {
    char* message = "quadTree - Jeu de puzzle :\n\n\n"
    "COMMENCER : commence partie (entre nom d'image pour les deux charger)\n"
    "choisir niveau\nRAPEL : niveau est la puissance de 4 qui donne nombre pieces\n"
    "(Exemple niveau 2 = 16 pieces 4 puissance 2)\n\n\n"
    "CLIQUER sur les cases pour les echanger\n\n\n"
    "Indice : mauvaises pieces\nTRES RARE case en haut a gauche peut donne mauvaises indications\n"
    "indication reste tant qu'on a pas selectionne nouvelle case\n"
    "Quitter boutton Quitter\n"
    "Appuyer sur clavier pour revenir";
    MLV_clear_window( PARTIE_FOND );
    
    MLV_draw_text_box(
        0, 0,
        taille_x, taille_y,
        message, 5,
        MLV_COLOR_RED, MLV_COLOR_RED, PARTIE_FOND,
        MLV_TEXT_CENTER,
        MLV_HORIZONTAL_CENTER, MLV_VERTICAL_CENTER);

    MLV_actualise_window();
    MLV_wait_keyboard(NULL, NULL, NULL);
}