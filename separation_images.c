#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <MLV/MLV_all.h>
#include "gestion_image.h"
#include "separation_images.h"
#include "creation_arbre_quadtree.h"
#include "dessin_image.h"

int separe_partie(Arbre *a, int niveau) {

    if (niveau < 1)
        return 0;
    srand(time(NULL));
    separe_parties_aux(a, a, *a, *a, 0, niveau);
    dessiner_image(*a, LARG_HAUT, 0, 0);
    return 1;

}



Arbre piece_aleatoire(Arbre tmp, int niveau) {
    Arbre temp[4], cp_tmp = tmp;
    int i;
    for (i = 0; i < niveau; i++) {
        temp[0] = cp_tmp->fg1; temp[1] = cp_tmp->fd1; temp[2] = cp_tmp->fg2; temp[3] = cp_tmp->fd2;
        cp_tmp = temp[rand() % 4];
    }
    
    return cp_tmp;
}

void echanger(Arbre *soure, Arbre *cible) {
    Arbre tmp;
    tmp = *soure;
    *soure = *cible;
    *cible = tmp;
}

void echanger_sup(Arbre *source, Arbre cible) {
    int j;
    j = rand() % 4;
    if (j == 0)
        echanger(source, &(cible->fg1));
    if (j == 1)
        echanger(source, &(cible->fd1));
    if (j == 2)
        echanger(source, &(cible->fg2));
    if (j == 3)
        echanger(source, &(cible->fd2));

}

int separe_parties_aux(Arbre *a, Arbre *tmp, Arbre parcours, const Arbre racine, int i, int niveau) {
    Arbre cp;
    if (NULL != parcours) {

        if (i < niveau) {
            if (i + 1 == niveau) {
                cp = piece_aleatoire(racine, i);
                if (NULL != (*a)->fg1) 
                    echanger_sup(&((*a)->fg1), cp);
                cp = piece_aleatoire(racine, i);
                if (NULL != (*a)->fd1) 
                    echanger_sup(&((*a)->fd1), cp);
                cp = piece_aleatoire(racine, i);
                if (NULL != (*a)->fg2)
                    echanger_sup(&((*a)->fg2), cp);
                cp = piece_aleatoire(racine, i);
                if (NULL != (*a)->fd2)
                    echanger_sup(&((*a)->fd2), cp);

                return 1;
            }
            
            if (!separe_parties_aux(&((*a)->fg1), tmp, parcours->fg1, racine, i + 1, niveau))
                return 0;
            if (!separe_parties_aux(&((*a)->fd1), tmp, parcours->fd1, racine, i + 1, niveau))
                return 0;
            if (!separe_parties_aux(&((*a)->fg2), tmp, parcours->fg2, racine, i + 1, niveau))
                return 0;
            if (!separe_parties_aux(&((*a)->fd2), tmp, parcours->fd2, racine, i + 1, niveau))
                return 0;

        }
    }
    return 1;
}