#ifndef __GESTION_IMAGE__
#define __GESTION_IMAGE__

#include <MLV/MLV_all.h>

#define LARG_HAUT 512
typedef struct COORDONNEES_IMAGE
{
    float rouge;
    float vert;
    float bleu;
    float alpha;
    float couleur;

}Coord_Im;

/* Cette fonction va recevoir le nom de l'image et si l'image existe va la charger et renvoyée 1 sinon 0.*/
int charger_image(char *nom_image, MLV_Image **image);

/* Cette fonction fait appelé à `charger_image` et si seulement l'image existe elle sera redimensionner en 2 puissance 9 c'est a dire 512.
 * Elle renvoyée 1 si tout se passe sinon 0.*/
int redimensionner_image(char *nom_image, MLV_Image **image, MLV_Image **image_red);

/* Attribue les coordonnes de `Coord_Im` les valeurs en paramètre.
 * Et au même temps va les convertir en nuance gris. 
 * Renvoyée 1 si valeurs compris entre 0 et 255 sinon 0.*/
int init_Coord_Im(Coord_Im *coord_im, int rouge, int vert, int bleu, int alpha);

/*Fixe la nouvelle couleur avec la fonction `MLV_set_pixel_on_image`.*/
int fixe_nouvelle_couleur(MLV_Image **image, Coord_Im coord_im, int x, int y);

/* Double boucle pour parcourir notre image. On recupere les coordonnées du pixel avec `MLV_get_pixel_on_image`.
 * Fait appelle à `redimensionner_image`, `init_Coord_Im`, `fixe_nouvelle_couleur`
 * Si une des fonctions appeler renvoyee 0 cette fonction renvoyee 0 sinon renvoyee 1.*/
int convertir_pixel_image(char *nom_image, MLV_Image **image, MLV_Image **image_red);
#endif