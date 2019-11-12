#include <stdio.h>
#include <stdlib.h>
#include <MLV/MLV_all.h>
#include "creation_arbre_quadtree.h"
#include "dessin_image.h"

void dessiner_pixel_image(Arbre a, int debut_x, int debut_y, int taille) {
    int i, j;
    for (i = 0; i < taille; i++) {
        for (j = 0; j < taille; j++)
            MLV_draw_pixel(i + debut_x, j + debut_y, MLV_rgba(a->valeur, a->valeur, a->valeur, 255));
    }
}


void dessin_piece_image(int taille, int debut_x, int debut_y, MLV_Color couleur) {
	MLV_draw_filled_rectangle(debut_x, debut_y, taille, taille, couleur);
	MLV_actualise_window();
}

void dessiner_contour_piece_image(int taille, int debut_x, int debut_y, MLV_Color couleur) {
    MLV_draw_rectangle(debut_x, debut_y, taille, taille, couleur);
    MLV_actualise_window();
}

void dessiner_image(Arbre a, int taille, int debut_x, int debut_y) {
    if (NULL != a) {
        if (NULL == a->fg1 && NULL == a->fg2 && NULL == a->fd1 && NULL == a->fd2)
            dessiner_pixel_image(a, debut_x, debut_y, taille);

        dessiner_image(a->fg1, taille / 2, debut_x, debut_y);
        dessiner_image(a->fd1, taille / 2, debut_x + taille / 2, debut_y);
        dessiner_image(a->fg2, taille / 2, debut_x, debut_y + taille / 2);
        dessiner_image(a->fd2, taille / 2, debut_x + taille / 2, debut_y + taille / 2);
    }
}