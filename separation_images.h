#ifndef __SEPARATION_IMAGES__
#define __SEPARATION_IMAGES__

#include "creation_arbre_quadtree.h"

/* Cette fonction va servir pour séparer l'image en 16 ou 64 parties.*/
int separe_partie(Arbre *a, int niveau);

/* Cette fonction va cherche un noued aleatiore au niveau - 1.*/
Arbre piece_aleatoire(Arbre tmp, int niveau);

/* Cette fonction va echanger les deux noeuds*/
void echanger(Arbre *soure, Arbre *cible);

/* Va echanger avec un fils aleatoire.*/
void echanger_sup(Arbre *source, Arbre cible);

/* Cette fonction va echanger tous les fils d'un pere avec dautres fils aleatoire.*/
int separe_parties_aux(Arbre *a, Arbre *tmp, Arbre parcours, const Arbre racine, int i, int niveau);
#endif