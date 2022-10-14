#ifndef GRAPHE_H_INCLUDED
#define GRAPHE_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include "fifo.h"

/* Structure d'un arc*/
struct Arc
{
    int depart;
    int sommet; // numéro de sommet d'un arc adjacent au sommet initial
    int poids;
    struct Arc* arc_suivant;

};

/* Alias de pointeur sur un Arc */
typedef struct Arc* pArc;

/* Structure d'un sommet*/
struct Sommet
{
    struct Arc* arc;
    int valeur;
    char couleur;
    int distance;
};

/* Alias de pointeur sur un Sommet */
typedef struct Sommet* pSommet;

/* Alias d'un Graphe */
typedef struct Graphe
{
    int taille;
    int ordre;
    pSommet* pSommet;
    pArc* pArc;

} Graphe;

typedef struct Arbre{
    int parent;
    int rang;
} Arbre;

Graphe* CreerGraphe(int ordre);

Graphe * lire_graphe(char * nomFichier);

pSommet* CreerArete(pSommet* sommet,int s1, int s2, int poids);

void afficher_successeurs(pSommet * sommet, int num);

void graphe_afficher(Graphe* graphe);


#define MAX 30

typedef struct edge_list {
    pArc *data;
    int n;
} edge_list;

struct Subset
{
    int Parent;
    int Rank;
};


void kruskalAlgo();
int find(int belongs[], int vertexno);
void applyUnion(int belongs[], int c1, int c2);
void sort(struct edge_list* elist);
void print();

///fonctions utilisées pour KRUSKAL
void union1(int belongs[],int c1,int c2, int n);
int find(int belongs[],int vertexno);
void KRUSKAL(Graphe* g);

#endif // GRAPHE_H_INCLUDED
