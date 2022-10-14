#ifndef FIFO_H_INCLUDED
#define FIFO_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include "cellule.h"
#include "Graphe.h"

struct _file {
    int longueur;
    Cellule tete;
    Cellule queue;
};

typedef struct _file* File;

#define fileEstVide(F) ((F)->longueur == 0)

File fileVide();
int longueur(File F);
void enfiler(File F, typage element);
typage tete(File F);
void defiler(File F);
typage defilement(File F);
void ecrireFile(File F);

#endif // FIFO_H_INCLUDED