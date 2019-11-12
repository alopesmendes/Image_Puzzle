
#ifndef __NOMBRE_PARTIES__
#define __NOMBRE_PARTIES__

#include <MLV/MLV_all.h>

typedef struct COORDONNEES_BOITE_SAISIE
 {
    int x;
    int y;
    int largeur_x;
    int largeur_y;     

 }Coord_saisie;

/* Initialise coordonnees de la premier boite saisie*/
Coord_saisie init_boite_saisie(int taille_x, int taille_y);

/* Renvoie 1 si on a clique sur une boite de saisie
 * Sinon 0*/
int verifie_clic_boite(int x, int y, int *veri, char *texte1, Coord_saisie coord);

/* Affiche les boites de saisie*/
void affichage(char* texte1, char *texte, MLV_Input_box *box1);

int nom_fichier_jpg(char *nom_quad, char *nouv_nom);

/* Recupere les evenements pour ecrire dans une boite.
 * Renvoyee 1 seulement quand on rentre un nombre*/
int boite_saisie_nombre(int taille_x, int taille_y, MLV_Image *image);

/* Recupere aussi les evenements pour ecrire dans une boite. 
 * Renvoyee 1 seulement on rentre une image qui existe.*/
int boite_saisie_image(int taille_x, int taille_y, MLV_Image **image, MLV_Image **image_red, char text[], int veri);
 

#endif