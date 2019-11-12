#ifndef __DESSIN_IMAGE__
#define __DESSIN_IMAGE__

#include "creation_arbre_quadtree.h"
#include <MLV/MLV_all.h>

/* Va dessiner les pixels jusqu'à la taille*/
void dessiner_pixel_image(Arbre a, int debut_x, int debut_y, int taille);

/* Cette fonction va dessiner toute l'image en recuperant des fils.*/
void dessiner_image(Arbre a, int taille, int debut_x, int debut_y);

/* Cette fonction va dessiner un rectangle avec `couleur` aux coordonnees donnee en parametre.*/
void dessiner_contour_piece_image(int taille, int debut_x, int debut_y, MLV_Color couleur);

/* Cette fonction va dessiner un rectangle rempli avec `couleur` aux coordonnees donnee en parametre.*/
void dessin_piece_image(int taille, int debut_x, int debut_y, MLV_Color couleur);

#endif