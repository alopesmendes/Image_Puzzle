
#ifndef __RENTRE_NOMBRE__
#define __RENTRE_NOMBRE__

/* Convertir chaine en int et renvoyee le resultat
 * Si ce n'est pas une chaine numerique positif renvoyee 0*/
int convertir_ChaineChiffres_int(char *s);

/* Si la fonction `convertir_ChaineChiffres_int` renvoyee 0 efface notre chaine*/
int verifie_nombre(char *texte);

#endif