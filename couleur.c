#include <stdio.h>
#include <stdlib.h>
#include <MLV/MLV_all.h>
#include "couleur.h"

void tester_couleur() {
	MLV_clear_window(COULEUR_FOND_PARTIE);
	MLV_wait_seconds(1);
	MLV_actualise_window();
	MLV_clear_window(PARTIE_FOND);
	MLV_wait_seconds(1);
	MLV_actualise_window();
	MLV_clear_window(BOITE_COULEUR);
	MLV_wait_seconds(1);
	MLV_actualise_window();
}