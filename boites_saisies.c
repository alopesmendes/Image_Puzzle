#include <stdio.h>
#include <stdlib.h>
#include <MLV/MLV_all.h>
#include <string.h>
#include "rentre_nombre.h"
#include "menu_option.h"
#include "clic_menu_option.h"
#include "boites_saisies.h"
#include "couleur.h"
#include "gestion_image.h"

#define NB_X 0
#define NB_Y 2



Coord_saisie init_boite_saisie(int taille_x, int taille_y) {
    Coord_saisie coord;

    coord.x = taille_x / (3);
    coord.y = taille_y / 8 - taille_y / 10;
    coord.largeur_x = taille_x / 3;
    coord.largeur_y = taille_y / 10;

    return coord;
}

int verifie_clic_boite(int x, int y, int *veri, char *texte1, Coord_saisie coord) {

    if ( coord.y <= y && y <= coord.y + coord.largeur_y ) {
        if ( coord.x <= x && x <= coord.x + coord.largeur_x ) {
            if ('\0' == texte1[0])
                *veri = 0;
            else {
                *veri = 1;
                texte1[0] = '\0';
            }
            return 1;
        }
    }

    return 0;
}

int nom_fichier_jpg(char *nom_quad, char *nouv_nom) {
    int i = 0;

    strcpy(nouv_nom, nom_quad);    
    for (i = 0; nouv_nom[i] != '.'; i++);
    if (nouv_nom[i + 1] != 'q' || nouv_nom[i + 2] != 'u' || nouv_nom[i + 3] != 'a' || nouv_nom[i + 4] != 'd') {
        nouv_nom[0] = '\0';
        return 0;
    }
    nouv_nom[i + 1] = 'j';
    nouv_nom[i + 2] = 'p';
    nouv_nom[i + 3] = 'g'; 
    nouv_nom[i + 4] = '\0';
    return 1;

}

void affichage(char* texte1, char *texte, MLV_Input_box *box1) {

    MLV_change_informative_message_of_input_box(box1, "%s%s", texte, texte1);


    MLV_draw_input_box(box1);

}


int boite_saisie_nombre(int taille_x, int taille_y, MLV_Image *image) {

    char* texte, *texte1;
    int x = -1, y = -1, veri = -1, i = -1, n = -1, val_ret = -1;
    MLV_Input_box *input_box, *input_box_1;
    MLV_Event event;
    Coord_saisie coord = init_boite_saisie(taille_x, taille_y);

    char *message[NB_Y] = {"VALIDER", "RETOUR"};
    Menu_option menu  = initialisation_Menu_option(taille_x, taille_y, NB_X, NB_Y, message);
    coord.x = LARG_HAUT + 10; coord.largeur_x = taille_x - 2 * LARG_HAUT - 20;

    menu.x[0] = coord.x; menu.largeur_x = coord.largeur_x;
    menu.largeur_y = menu.largeur_y / 2;
    menu.y[0] += menu.largeur_y;
    menu.y[1] += menu.largeur_y;


    menu_depart(menu, NB_X, NB_Y);


    input_box_1 = MLV_create_input_box(
        coord.x, coord.y,
        coord.largeur_x, coord.largeur_y, 
        MLV_COLOR_GREEN, MLV_COLOR_GREEN,
        BOITE_COULEUR, "NIVEAU : "
    );
    texte1 = (char*) malloc( 1*sizeof(char) ); *texte1 = '\0';




    veri = 0;
    affichage(texte1, "NIVEAU : ", input_box_1);

    while (1) {
        MLV_clear_window( COULEUR_FOND_PARTIE );
        MLV_draw_image( image, taille_x - LARG_HAUT, 0 );

        MLV_get_mouse_position(&x, &y);
        if ( MLV_get_mouse_button_state( MLV_BUTTON_LEFT ) == MLV_PRESSED || MLV_get_mouse_button_state( MLV_BUTTON_RIGHT ) == MLV_PRESSED)
            verifie_clic_boite(x, y, &veri, texte1, coord);


        event = MLV_get_event( 
            NULL, NULL, NULL,
            &texte, &input_box,
            NULL, NULL, NULL,
            NULL
        );


        if( event == MLV_INPUT_BOX ){

            if( input_box == input_box_1 ){
                free( texte1 );
                texte1 = texte;
            }


        }
        n = verifie_nombre(texte1);
        
        affichage(texte1, "NIVEAU : ", input_box_1);
        i = verification_position_souris(menu, MLV_rgba(255, 217, 102, 255), x, y, NB_X, NB_Y, &val_ret);
        MLV_actualise_window();
        if (MLV_get_mouse_button_state( MLV_BUTTON_LEFT ) == MLV_PRESSED && i == 1) {
            if (n > 0) 
                break;
            if (val_ret == 2)
                return 42;
        }

        MLV_actualise_window();

    };
    while (MLV_get_mouse_button_state( MLV_BUTTON_LEFT ) == MLV_PRESSED);

    free( texte1 );

    MLV_free_input_box( input_box_1 );
    return n;

}

int boite_saisie_image(int taille_x, int taille_y, MLV_Image **image, MLV_Image **image_red, char text[], int veri) {
    char  *texte1;
    char *texte2 = "NOM IMAGE.jpg : ", *texte3 = "NOM IMAGE.quad : ";
    char texte_const[100] = {'\0'}, texte_const2[100] = {'\0'};
    Coord_saisie coord = init_boite_saisie(taille_x, taille_y);

    coord.y = taille_y / 2;
    
    if (veri == 2)
        strcpy(texte_const, texte3);
    else
        strcpy(texte_const, texte2);

    texte1 = (char*) malloc( 1*sizeof(char) ); *texte1 = '\0';
    while ( 1 ) {
        MLV_clear_window( COULEUR_FOND_PARTIE );
        if (veri == 2)
            nom_fichier_jpg(texte1, texte_const2);
        else
            strcpy(texte_const2, texte1);
        if (!convertir_pixel_image(texte_const2, image, image_red))
            *texte1 = '\0';
        else
            break;
        
        MLV_wait_input_box(
            coord.x, coord.y,
        	coord.largeur_x, coord.largeur_y, 
        	MLV_COLOR_GREEN, MLV_COLOR_GREEN, BOITE_COULEUR,
        	 "%s", &texte1, texte_const
        );

        MLV_actualise_window();
        
    }
    strcpy(text, texte1);
    free( texte1 );

    return 1;

}