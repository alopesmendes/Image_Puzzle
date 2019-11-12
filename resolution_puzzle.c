#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <MLV/MLV_all.h>
#include "resolution_puzzle.h"
#include "creation_arbre_quadtree.h"
#include "gestion_image.h"
#include "dessin_image.h"
#include "separation_images.h"
#include "couleur.h"
#include "menu_option.h"
#include "clic_menu_option.h"

#define NB_X 2
#define NB_Y 0

int noeud_clique(Arbre a, Arbre *pere, Arbre *fils, int debut_x, int debut_y, int taille, int x, int y, int i, int niveau) {
    if (NULL != a) {
        if (i <= niveau) {
            
            if ((debut_x <= x && x <= debut_x + taille) && (debut_y <= y && y <= debut_y + taille)) {
                if (i + 1 == niveau)
                    *pere = a;
                if (i == niveau) {
                    *fils = a;
                    dessiner_contour_piece_image(taille, debut_x, debut_y, MLV_COLOR_GREEN);
                }
            }
            
            if (!noeud_clique(a->fg1, pere, fils, debut_x, debut_y, taille / 2, x, y, i + 1, niveau))
                return 0;
            if (!noeud_clique(a->fd1, pere, fils, debut_x + taille / 2, debut_y, taille / 2, x, y, i + 1, niveau))
                return 0;
            if (!noeud_clique(a->fg2, pere, fils, debut_x, debut_y + taille / 2, taille / 2, x, y, i + 1, niveau))
                return 0;
            if (!noeud_clique(a->fd2, pere, fils, debut_x + taille / 2, debut_y + taille / 2, taille / 2, x, y, i + 1, niveau))
                return 0;

        }
    }
    return 1;
}

int echanger_images(Arbre *premier, Arbre *deuxieme) {
    Arbre tmp;
    if (NULL == *premier || NULL == deuxieme) {
        return 0;
    }
    tmp = *premier;
    *premier = *deuxieme;
    *deuxieme = tmp;
    return 1;
}

int echanger_images_sup(Arbre *cible, Arbre pere2, Arbre fils2) {
    if (pere2->fg1 == fils2) {
        if (echanger_images(cible, &(pere2->fg1)))
            return 1;
    }
    if (pere2->fd1 == fils2) {
        if (echanger_images(cible, &(pere2->fd1)))
            return 1;
    }
    if (pere2->fg2 == fils2) {
        if (echanger_images(cible, &(pere2->fg2)))
            return 1;
    }
    if (pere2->fd2 == fils2) {
        if (echanger_images(cible, &(pere2->fd2)))
            return 1;
    }
    return 0;
}

int clic_sur_deux_piece(Arbre *premier, Arbre *deuxieme, int niveau, int *x, int *y, Menu_option menu, int *veri) {
    Arbre pere1 = NULL, pere2 = NULL, fils1 = NULL, fils2 = NULL; 
    MLV_get_mouse_position(x, y);
    while (MLV_get_mouse_button_state( MLV_BUTTON_LEFT ) != MLV_PRESSED) {
        if (!verification_position_souris(menu, MLV_rgba(255, 217, 102, 255), *x, *y, NB_X, NB_Y, veri))
            *veri = -1;
        MLV_get_mouse_position(x, y);
    }

    while (MLV_get_mouse_button_state( MLV_BUTTON_LEFT ) != MLV_RELEASED);
    if (*veri != -1)
        return 0;
    pere1 = *premier;

    if (!noeud_clique(*premier, &pere1, &fils1, 0, 0, LARG_HAUT, *x, *y, 0, niveau))
        return 0;
    MLV_get_mouse_position(x, y);
    while (MLV_get_mouse_button_state( MLV_BUTTON_LEFT ) != MLV_PRESSED)
        MLV_get_mouse_position(x, y);
    while (MLV_get_mouse_button_state( MLV_BUTTON_LEFT ) != MLV_RELEASED);
    pere2 = *deuxieme;
    if (!noeud_clique(*deuxieme, &pere2, &fils2, 0, 0, LARG_HAUT, *x, *y, 0, niveau))
        return 0;
    
    if (pere1->fg1 == fils1) {
        if (echanger_images_sup(&(pere1->fg1), pere2, fils2))
            return 1;
    }
    if (pere1->fd1 == fils1) {
        if (echanger_images_sup(&(pere1->fd1), pere2, fils2))
            return 1;
    }
    if (pere1->fg2 == fils1) {
        if (echanger_images_sup(&(pere1->fg2), pere2, fils2))
            return 1;
    }
    if (pere1->fd2 == fils1) {
        if (echanger_images_sup(&(pere1->fd2), pere2, fils2))
            return 1;
    }
    return 0;

}


int parcours_arbre(Arbre original, Arbre modifie, int *variable, int *variable2, int veri, int taille, int debut_x, int debut_y, int niveau) {
    if (NULL != original && NULL != modifie) {


        if(!parcours_arbre(original->fg1, modifie->fg1, variable, variable2, veri, taille / 2, debut_x, debut_y, niveau - 1))
            return 0;
        if(!parcours_arbre(original->fd1, modifie->fd1, variable, variable2, veri, taille / 2, debut_x + taille / 2, debut_y, niveau - 1))
            return 0;
        if(!parcours_arbre(original->fg2, modifie->fg2, variable, variable2, veri, taille / 2, debut_x, debut_y + taille / 2, niveau - 1))
            return 0;
        if(!parcours_arbre(original->fd2, modifie->fd2, variable, variable2, veri, taille / 2, debut_x + taille / 2, debut_y + taille / 2, niveau - 1))
            return 0;

        if (NULL == original->fg1 && NULL == original->fd1 && NULL == original->fg2 && NULL == original->fd2) {
            if (original->valeur != modifie->valeur) {
                *variable2 = 0;
                *variable = 0;
                }
        }

        if (NULL == modifie->fg1 && NULL == modifie->fd1 && NULL == modifie->fg2 && NULL == modifie->fd2) {
            if (original->valeur != modifie->valeur) {
                *variable2 = 0;
                *variable = 0;
                }
        }

        if(niveau == 0 && veri == 1) {
            if (*variable == 0) {
                dessin_piece_image(taille, debut_x, debut_y, MLV_rgba(102, 204, 255, 150));
                *variable = 1;
            }
        }
            
    }
    return 1;
}



int jeu_puzzle(Arbre original, Arbre *modifie, int niveau, MLV_Image *image, int taille_x, int taille_y) {
    int variable = 2, veri = -1, variable2 = 1, x, y, score = 0;
    char *texte[NB_X + NB_Y] = {"Indice", "Retour"};
    Menu_option menu  = initialisation_Menu_option(taille_x, taille_y, NB_X, NB_Y, texte);
    menu.y[0] = LARG_HAUT + LARG_HAUT / 16; menu.largeur_y = LARG_HAUT / 16;
    menu.largeur_x = LARG_HAUT / 4;
    menu.x[0] = (LARG_HAUT - menu.largeur_x) / 2; menu.x[1] = (taille_x - LARG_HAUT) + (LARG_HAUT - menu.largeur_x) / 2;
    separe_partie(modifie, niveau);
    
    while (1){

        MLV_clear_window(COULEUR_FOND_PARTIE);
        MLV_draw_text_box(
            (taille_x - menu.largeur_x) / 2, (taille_y - menu.largeur_y) / 2, menu.largeur_x, menu.largeur_y, 
            "coups : %d", 0, MLV_COLOR_RED, MLV_COLOR_RED, COULEUR_FOND_PARTIE,
            MLV_TEXT_CENTER, MLV_HORIZONTAL_CENTER, MLV_VERTICAL_CENTER, score
        );

        dessiner_image(*modifie, LARG_HAUT, 0, 0);
        parcours_arbre(original, *modifie, &variable, &variable2, veri, LARG_HAUT, 0, 0, niveau);
        MLV_draw_image( image, taille_x - LARG_HAUT, 0 );
        if (variable2 || veri == 2)
            break;
        else 
            variable2 = 1;
        veri = -1;
        score += clic_sur_deux_piece(modifie, modifie, niveau, &x, &y, menu, &veri);
        dessiner_image(*modifie, LARG_HAUT, 0, 0);
        MLV_actualise_window();

    }
    MLV_clear_window(COULEUR_FOND_PARTIE);
    MLV_draw_text_box(
        (taille_x - menu.largeur_x) / 2, (taille_y - menu.largeur_y) / 2, menu.largeur_x, menu.largeur_y, 
        "Total : %d", 0, MLV_COLOR_RED, MLV_COLOR_RED, COULEUR_FOND_PARTIE,
        MLV_TEXT_CENTER, MLV_HORIZONTAL_CENTER, MLV_VERTICAL_CENTER, score
    );
    MLV_actualise_window();
    MLV_wait_seconds(2);
    
    return 1;
}

