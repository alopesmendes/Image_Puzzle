#include <stdio.h>
#include <stdlib.h>
#include <MLV/MLV_all.h>
#include "separation_images.h"
#include "gestion_image.h"
#include "creation_arbre_quadtree.h"
#include "resolution_puzzle.h"
#include "couleur.h"
#include "page_accueil.h"
#include "menu_option.h"
#include "clic_menu_option.h"
#include "rentre_nombre.h"
#include "boites_saisies.h"
#include "jeu.h"
#include "aide.h"

int main(int argc, char const *argv[]) {
    int taille_x, taille_y;

    taille_x = MLV_get_desktop_width();
    taille_y = MLV_get_desktop_height();
    MLV_create_window( "advanced - 6 - image", "image", taille_x, taille_y );

    jeu(taille_x, taille_y);
    
    return 0;
}