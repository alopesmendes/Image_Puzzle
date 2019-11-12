#ifndef __RESOLUTION_PUZZLE__
#define __RESOLUTION_PUZZLE__

#include <MLV/MLV_all.h>
#include "gestion_image.h"
#include "creation_arbre_quadtree.h"
#include "menu_option.h"
 /* Va verifier sur quelle noued on a clique puis renvoyee 1.
  * Sinon 0.*/
int noeud_clique(Arbre a, Arbre *pere, Arbre *fils, int debut_x, int debut_y, int taille, int x, int y, int i, int niveau);

/* Cette fonction va verifier quelle fils du `pere2` est le meme que `fils2`.
 * Ensuite elle va echanger le `pere2` et la `cible` en appelant `echanger_images.`*/
int echanger_images_sup(Arbre *cible, Arbre pere2, Arbre fils2);

/* Va recevoir deux arbres en parametré et va dans la meme logique que `echanger_images_sup` echange un fils avec un autre.*/
int echanger_images(Arbre *premier, Arbre *deuxieme);

/* Cette fonction attend une premier clic si on clique sur une piece on fait appel à `noeud_clique`.
 * Sinon elle verifie si on clique sur les cases en bas. Si oui elle renvoyee 0 mais `veri` devient la case clique.
 * Si on clique sur une piece on doit cliquer sur une deuxieme et l'echange est fait.*/
int clic_sur_deux_piece(Arbre *premier, Arbre *deuxieme, int niveau, int *x, int *y, Menu_option menu, int *veri);

/* Cette fonction fonctionne avec un parcours suffixe.
 * Elle va compare les valeurs des fils `originals` au noeud courant de `modifie` et l'inverse.
 * Si les valeur sont differents `variable` devient 0 et on redessiner la piece. Ensuite `variable` devient 1.
  * Sinon on fait rien et on continue a parcourir.*/
int parcours_arbre(Arbre original, Arbre modifie, int *variable, int *variable2, int veri, int taille, int debut_x, int debut_y, int niveau);

/* Cette fonction va reunir l'idee des fonctions precedents pour creer une partie.*/
int jeu_puzzle(Arbre original, Arbre *modifie, int niveau, MLV_Image *image, int taille_x, int taille_y);


#endif