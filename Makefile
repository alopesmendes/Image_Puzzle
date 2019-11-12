CC = gcc
CFLAGS = -ansi -pedantic -Wall -Wfatal-errors 
OBJ = main.o separation_images.o creation_arbre_quadtree.o gestion_image.o resolution_puzzle.o dessin_image.o couleur.o page_accueil.o menu_option.o clic_menu_option.o rentre_nombre.o boites_saisies.o jeu.o aide.o
LDFLAGS = -lMLV

quadTree: $(OBJ)
	$(CC) -o $@ $^ $(LDFLAGS)

main.o: main.c separation_images.h creation_arbre_quadtree.h gestion_image.h resolution_puzzle.h dessin_image.h couleur.h page_accueil.h menu_option.h clic_menu_option.h rentre_nombre.h boites_saisies.h jeu.h aide.h

rentre_nombre.o: rentre_nombre.h rentre_nombre.c 

boites_saisies.o: boites_saisies.c boites_saisies.h rentre_nombre.h menu_option.h clic_menu_option.h couleur.h gestion_image.h

jeu.o: jeu.c jeu.h separation_images.h gestion_image.h creation_arbre_quadtree.h resolution_puzzle.h couleur.h page_accueil.h menu_option.h clic_menu_option.h aide.h

couleur.o: couleur.h couleur.c

clic_menu_option.o: clic_menu_option.c clic_menu_option.h couleur.h menu_option.h

menu_option.o: menu_option.c menu_option.h 

page_accueil.o: page_accueil.c page_accueil.h menu_option.h clic_menu_option.h couleur.h

dessin_image.o: dessin_image.c dessin_image.h  creation_arbre_quadtree.h

resolution_puzzle.o : resolution_puzzle.c resolution_puzzle.h creation_arbre_quadtree.h gestion_image.h dessin_image.h couleur.h menu_option.h clic_menu_option.h

separation_images.o: separation_images.c separation_images.h  creation_arbre_quadtree.h gestion_image.h dessin_image.h

creation_arbre_quadtree.o: creation_arbre_quadtree.c creation_arbre_quadtree.h gestion_image.h dessin_image.h

gestion_image.o: gestion_image.c gestion_image.h

aide.o: aide.c aide.h

%.o: %.c
	$(CC) -c $< $(CFLAGS)

clean:
	rm -f *.o

mrproper: clean
	rm -f $EXEC
