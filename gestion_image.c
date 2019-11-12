#include <stdio.h>
#include <stdlib.h>
#include <MLV/MLV_all.h>
#include "gestion_image.h"

int charger_image(char *nom_image, MLV_Image **image) {
    FILE *fichier = NULL;
    if (NULL == (fichier = fopen(nom_image, "r+"))) 
        return 0;
    fclose(fichier);
    *image = MLV_load_image( nom_image );
    return 1;
}

int redimensionner_image(char *nom_image, MLV_Image **image, MLV_Image **image_red) {

	int hauteur, largeur, x, y;
    if (!charger_image(nom_image, image))
        return 0;

    MLV_resize_image_with_proportions( *image, LARG_HAUT, LARG_HAUT);
    MLV_get_image_size(*image, &hauteur, &largeur);

    x = (largeur > hauteur ? (LARG_HAUT - hauteur) / 2 : 0);
    y = (largeur < hauteur ? (LARG_HAUT - largeur) / 2 : 0);
    MLV_draw_image_on_image(*image, *image_red, x, y);


    return 1;
}

int init_Coord_Im(Coord_Im *coord_im, int rouge, int vert, int bleu, int alpha) {
    if (rouge < 0 || rouge > 256)
        return 0;
    (*coord_im).rouge = rouge * 0.299;

    if (vert < 0 || vert > 256)
        return 0;
    (*coord_im).vert = vert * 0.587;

    if (bleu < 0 || bleu > 256)
        return 0;
    (*coord_im).bleu = bleu * 0.114;

    if (alpha < 0 || alpha > 256)
        return 0;
    (*coord_im).alpha = alpha;

    (*coord_im).couleur = (*coord_im).rouge + (*coord_im).vert + (*coord_im).bleu;
    return 1;

}

int fixe_nouvelle_couleur(MLV_Image **image, Coord_Im coord_im, int x, int y) {
    if (x < 0 || x > LARG_HAUT)
        return 0;

    if (y < 0 || y > LARG_HAUT)
        return 0;
    MLV_set_pixel_on_image(x, y, MLV_rgba(coord_im.couleur, coord_im.couleur, coord_im.couleur, coord_im.alpha), *image);
    return 1;
}

int convertir_pixel_image(char *nom_image, MLV_Image **image, MLV_Image **image_red) { 
    Coord_Im coord_im;
    int x, y, rouge, vert, bleu, alpha;
    *image_red = MLV_create_image(LARG_HAUT, LARG_HAUT);
    if (NULL == *image_red)
        return 0;
    MLV_draw_filled_rectangle_on_image(
        0, 0, LARG_HAUT, LARG_HAUT, MLV_COLOR_WHITE, *image_red
    );

    if (!redimensionner_image(nom_image, image, image_red)) 
        return 0;

    for (x = 0; x < LARG_HAUT; x++) {
        for (y = 0; y < LARG_HAUT; y++) {
            MLV_get_pixel_on_image(
                *image_red, 
                x, y,
                &rouge, &vert, &bleu,
                &alpha);
            if (!init_Coord_Im(&coord_im, rouge, vert, bleu, alpha))
                return 0;

            if (!fixe_nouvelle_couleur(image_red, coord_im, x, y))
                return 0;
        }
    }
    MLV_free_image( *image );
    *image = NULL;
    return 1;

}