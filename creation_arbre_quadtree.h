#ifndef __CREATION_ARBRE_QUADTREE__
#define __CREATION_ARBRE_QUADTREE__

#include <stdio.h>
#include <MLV/MLV_all.h>


typedef struct noeud{
    int valeur;
    struct noeud *fg1;
    struct noeud *fg2;
    struct noeud *fd1;
    struct noeud *fd2;

}Noeud, *Arbre;

#include "dessin_image.h"

/* Cette fonction va allouer un noeud pour notre arbre.*/
Noeud* alloueNoeud(int val);

void prefixe(Arbre a);

/* Cette fonction prend les pixels a `debut_x` et `debut_y` et compare aux pixels suivant jusqu'a taille.
 * Si un pixel est different on renvoyee 0 sinon 1.*/
int parcours_zone(MLV_Image *image, int debut_x, int debut_y, int taille, int *gris_init);

/* Cette fonction va prendre l'arbre et l'image en parametre.
 * On parcourt les pixels et on le compare avec le premier.
 * Si la couleur est different on cree 4 nouvelles branches avec la partie de l'image divise en 4.*/
int creation_arbre(Arbre *a, MLV_Image *image, int taille, int debut_x, int debut_y, int niveau);

void dessiner_pixel_image(Arbre a, int debut_x, int debut_y, int taille);

/* Cette fonction sert a cree l'image à partir de l'arbre sert a verifier si l'arbre est bien cree.
 * En faisant un parcours prefixe on recupere les feuilles.
 * Cette fonction utilise la fonction `MLV_draw_partial_image`.*/
void inverser(Arbre a, MLV_Image *image, int taille, int debut_x, int debut_y);

/* Cette fonction va servir à écrire l'arbre dans un fichier.*/
void ecrire_arbre_fichier(Arbre a, FILE *fichier);

/* Cette fonction va servir à écrire l’arbre à partir d’un fichier.*/
int ecrire_fichier_arbre(Arbre *a, FILE *fichier);

/* Convertir le texte .jpg en .quad en changeant les dernieres caracteres.*/
int nom_fichier_quad(char *nom_image, char *nouv_nom);

/* Si `veri` est egale à 2 elle va creer larbre à partir des fichiers sinon à partir de l'image.*/
int creation_copie_arbre(Arbre *original, Arbre *copie, MLV_Image *image, FILE **fichier, char *nom_image, int niveau, int veri);

/* Avec un parcours suffixe on detruit l'arbre.*/
void detruit_arbre(Arbre *a);

#endif