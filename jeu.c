#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <MLV/MLV_all.h>
#include "separation_images.h"
#include "gestion_image.h"
#include "creation_arbre_quadtree.h"
#include "resolution_puzzle.h"
#include "couleur.h"
#include "page_accueil.h"
#include "menu_option.h"
#include "clic_menu_option.h"
#include "boites_saisies.h"
#include "jeu.h"
#include "aide.h"

int jeu(int taille_x, int taille_y) {
    MLV_Image *image = NULL, *image_red = NULL;
    Arbre original = NULL, copie = NULL;
    FILE *fichier = NULL;
    char text[100] = {'\0'};
    int veri = 0, niveau = 0;
    while (veri != 4) {
        MLV_clear_window(COULEUR_FOND_PARTIE);
        veri = cliquer_sur_menu_depart(taille_x, taille_y);
        if (veri == 1 || veri == 2) {
            boite_saisie_image(taille_x, taille_y, &image, &image_red, text, veri);

            niveau = boite_saisie_nombre(taille_x, taille_y, image_red);
            if (niveau != 42) {
                if (creation_copie_arbre(&original, &copie, image_red, &fichier, text, niveau, veri)) {
                    jeu_puzzle(original, &copie, niveau, image_red, taille_x, taille_y);
                    MLV_free_image( image_red );
                    image_red = NULL;
                }
            }
                        
        }
        if (veri == 3)
            message_aide(taille_x, taille_y);
        MLV_actualise_window();

    }
    detruit_arbre(&original);
    detruit_arbre(&copie);
    MLV_free_window();
    return 1;
}
