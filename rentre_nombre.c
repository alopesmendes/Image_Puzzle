#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "rentre_nombre.h"

int convertir_ChaineChiffres_int(char *texte) {
    int resultat = 0, valeur, i = 0;
    assert(NULL != texte);

    for(valeur = texte[i] - '0'; '\0' != texte[i]; i++, valeur = texte[i] - '0') {
        if (valeur > 9 || valeur < 0){
            return 0;
        }

        resultat = (resultat * 10) + valeur;
    }

    return resultat;
}

int verifie_nombre(char *texte) {
    int nb;
    assert(NULL != texte);
    if (!(nb = convertir_ChaineChiffres_int(texte)))
        texte[0] = '\0';
    return nb;
}