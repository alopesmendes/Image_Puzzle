#include <stdio.h>
#include <stdlib.h>
#include <MLV/MLV_all.h>
#include "gestion_image.h"
#include "creation_arbre_quadtree.h"
#include "dessin_image.h"

Noeud* alloueNoeud(int val) {
    Noeud* a = (Noeud*)malloc(sizeof(Noeud));

    if (NULL != a) {
        a->valeur = val;
        a->fg1 = NULL;
        a->fg2 = NULL;
        a->fd1 = NULL;
        a->fd2 = NULL;
    }
    return a;
}

int parcours_zone(MLV_Image *image, int debut_x, int debut_y, int taille, int *gris_init) {
    int alpha_init = 0, gris = 0, alpha = 0, i = 0, j = 0;
    
    
    MLV_get_pixel_on_image(
        image, 
        debut_x, debut_y,
        gris_init, NULL, NULL,
        &alpha_init
    );

    for (i = 1; i < taille; i++) {
        for (j = 1; j < taille; j++) {
            MLV_get_pixel_on_image(
                image, 
                i + debut_x, j + debut_y,
                &gris, NULL, NULL,
                &alpha
            );
            if (gris != *gris_init || alpha != alpha_init) {
                return 0;
            }
        }
    }
    return 1;

}

void prefixe(Arbre a) {
    if (NULL != a) {
        printf("%d ", a->valeur);
        prefixe(a->fg1);
        prefixe(a->fd1);
        prefixe(a->fg2);
        prefixe(a->fd2);
    }
}

int creation_arbre(Arbre *a, MLV_Image *image, int taille, int debut_x, int debut_y, int niveau) {
    int gris_init = 0, i = 0;
    i = parcours_zone(image, debut_x, debut_y, taille, &gris_init);
    if (!i || (niveau > 0)) {
        if(!(*a = alloueNoeud(0)))
            return 0;
        if (!creation_arbre(&((*a)->fg1), image, taille / 2, debut_x, debut_y, niveau - 1))
            return 0;
        if (!creation_arbre(&((*a)->fd1), image, taille / 2, debut_x + taille / 2, debut_y, niveau - 1))
            return 0;
        if (!creation_arbre(&((*a)->fg2), image, taille / 2, debut_x, debut_y + taille / 2, niveau - 1))
            return 0;
        if (!creation_arbre(&((*a)->fd2), image, taille / 2, debut_x + taille / 2, debut_y + taille / 2, niveau - 1))
            return 0;
        return 1;
    }

    else {
        if(!(*a = alloueNoeud(gris_init)))
            return 0;
    }
    return i;
}


void inverser(Arbre a, MLV_Image *image, int taille, int debut_x, int debut_y) {
    if (NULL != a) {
        if (NULL == a->fg1 && NULL == a->fg2 && NULL == a->fd1 && NULL == a->fd2) 
            dessiner_pixel_image(a, debut_x, debut_y, taille);

        inverser(a->fg1, image, taille / 2, debut_x, debut_y);
        inverser(a->fd1, image, taille / 2, debut_x + taille / 2, debut_y);
        inverser(a->fg2, image, taille / 2, debut_x, debut_y + taille / 2);
        inverser(a->fd2, image, taille / 2, debut_x + taille / 2, debut_y + taille / 2);
    }

}


void ecrire_arbre_fichier(Arbre a, FILE *fichier) {
    if (NULL != a) {
        if (NULL == a->fg1 && NULL == a->fg2 && NULL == a->fd1 && NULL == a->fd2)
            fprintf(fichier, "1 %d ", a->valeur);
        else
            fprintf(fichier, "%d ", 0);
        ecrire_arbre_fichier(a->fg1, fichier);
        ecrire_arbre_fichier(a->fd1, fichier);
        ecrire_arbre_fichier(a->fg2, fichier);
        ecrire_arbre_fichier(a->fd2, fichier);
    }
}

int ecrire_fichier_arbre(Arbre *a, FILE *fichier) {
    int veri = 0, val1 = 0, val2 = 0;
    veri = fscanf(fichier, "%d ", &val1);
    if (veri < 1)
        return 0;
    if (1 == val1)
        fscanf(fichier, "%d ", &val2);
    else
        val2 = 0;
    if(!(*a = alloueNoeud(val2)))
        return 0;
    if (0 == val1) {
        if (!ecrire_fichier_arbre(&((*a)->fg1), fichier))
            return 0;
        if (!ecrire_fichier_arbre(&((*a)->fd1), fichier))
            return 0;
        if (!ecrire_fichier_arbre(&((*a)->fg2), fichier))
            return 0;
        if (!ecrire_fichier_arbre(&((*a)->fd2), fichier))
            return 0;
    }
    return 1;
}

void detruit_arbre(Arbre *a) {
    if (NULL != *a) { 
        return;

        detruit_arbre(&((*a)->fg1));
        detruit_arbre(&((*a)->fd1));

        detruit_arbre(&((*a)->fg2));
        detruit_arbre(&((*a)->fd2));

        free( *a );
        *a = NULL;
    }
}

int nom_fichier_quad(char *nom_image, char *nouv_nom) {
    int i = 0;

    strcpy(nouv_nom, nom_image);    
    for (i = 0; nouv_nom[i] != '.'; i++);
    nouv_nom[i + 1] = 'q';
    nouv_nom[i + 2] = 'u';
    nouv_nom[i + 3] = 'a'; 
    nouv_nom[i + 4] = 'd';
    nouv_nom[i + 5] = '\0';
    return 1;

}

int creation_copie_arbre(Arbre *original, Arbre *copie, MLV_Image *image, FILE **fichier, char *nom_image, int niveau, int veri) {
    char fichier_quad[100] = {'\0'};
    if(NULL == nom_image)
        return 0;
    if (veri != 2)
        nom_fichier_quad(nom_image, fichier_quad);
    else
        strcpy(fichier_quad, nom_image);
    if (NULL == (*fichier = fopen(fichier_quad, "r+"))) {
        if (NULL == (*fichier = fopen(fichier_quad, "w+")))
            return 0;
    }
    if (veri == 2) {
        if (!ecrire_fichier_arbre(original, *fichier)) {
            if (fclose(*fichier) != 0) {
                return -1;
            }
            return 0;
        }
        rewind(*fichier);
        if (!ecrire_fichier_arbre(copie, *fichier)) {
            if (fclose(*fichier) != 0) {
                return -1;
            }
            return 0;
        }
        if (fclose(*fichier) != 0) {
            return -1;
        }

    }

    else {
        if (fclose(*fichier) != 0)
            return -1;

        if (!creation_arbre(original, image, LARG_HAUT, 0, 0, niveau)) {
            return 0;
        }
        if (NULL == (*fichier = fopen(fichier_quad, "r+"))) {
            if (NULL == (*fichier = fopen(fichier_quad, "w+")))
                return 0;
        }
        ecrire_arbre_fichier(*original, *fichier);
        rewind(*fichier);
        if (!ecrire_fichier_arbre(copie, *fichier)) {
            if (!fclose(*fichier)) {
                return -1;
            }
            return 0;
        }

        if (fclose(*fichier) != 0)
            return -1;


    }

    return 1;

}