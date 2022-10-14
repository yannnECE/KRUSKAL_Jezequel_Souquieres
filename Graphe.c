#include <stdio.h>
#include <stdlib.h>
#include "Graphe.h"

void afficher_successeurs(pSommet * sommet, int num)
{

    //printf(" sommet %d :\n",num);


    pArc arc = sommet[num]->arc;
    while(arc!=NULL)
    {
        printf("%d -> %d poids: %d \n",num, arc->sommet, arc->poids);
        arc=arc->arc_suivant;
    }

}

pSommet* CreerArete(pSommet* sommet,int s1,int s2, int poids)
{
    if(sommet[s1]->arc==NULL)
    {
        pArc Newarc=(pArc)malloc(sizeof(struct Arc));
        Newarc->depart = s1;
        Newarc->sommet=s2;
        Newarc->arc_suivant=NULL;
        Newarc->poids = poids;
        sommet[s1]->arc=Newarc;
        return sommet;
    }

    else
    {
        pArc temp = sommet[s1]->arc;
        while( !(temp->arc_suivant==NULL))
        {
            temp=temp->arc_suivant;
        }
        pArc Newarc=(pArc)malloc(sizeof(struct Arc));
        Newarc->depart = s1;
        Newarc->sommet=s2;
        Newarc->arc_suivant=NULL;
        Newarc->poids = poids;

        if(temp->sommet>s2)
        {
            Newarc->arc_suivant=temp->arc_suivant;
            Newarc->sommet=temp->sommet;
            Newarc->poids = temp->poids;
            Newarc->depart = s1;
            temp->sommet=s2;
            temp->poids=poids;
            temp->arc_suivant=Newarc;
            return sommet;
        }

        temp->arc_suivant=Newarc;
        return sommet;
    }
}

Graphe* CreerGraphe(int ordre)
{

    Graphe * Newgraphe=(Graphe*)malloc(sizeof(Graphe));
    Newgraphe->pSommet = (pSommet*)malloc(ordre*sizeof(pSommet));

    for(int i=0; i<ordre; i++)
    {
        Newgraphe->pSommet[i]=(pSommet)malloc(sizeof(struct Sommet));
        Newgraphe->pSommet[i]->valeur=i;
        Newgraphe->pSommet[i]->arc=NULL;
    }
    return Newgraphe;
}

Graphe * lire_graphe(char * nomFichier)
{
    Graphe* graphe;
    FILE * ifs = fopen(nomFichier,"r");
    int taille, ordre, s1, s2, poids;

    if (!ifs)
    {
        printf("Erreur de lecture fichier\n");
        exit(-1);
    }


    fscanf(ifs,"%d",&ordre);
    graphe = CreerGraphe(ordre); // créer le graphe d'ordre sommets

    graphe->ordre = ordre;

    //fscanf(ifs,"%d",&orientation);
    //graphe->orientation=orientation;

    for(int i=0; i<graphe->ordre; i++)
    {
        fscanf(ifs, "%d", &graphe->pSommet[i]->valeur);
    }


    fscanf(ifs,"%d",&taille);
    graphe->taille=taille;

    // créer les arêtes du graphe
    for (int i=0; i<taille; ++i)
    {
        fscanf(ifs,"%d%d%d",&s1,&s2, &poids);
        graphe->pSommet=CreerArete(graphe->pSommet, s1, s2, poids);
        graphe->pSommet=CreerArete(graphe->pSommet, s2, s1, poids);

        //if(!orientation)
            //graphe->pSommet=CreerArete(graphe->pSommet, s2, s1, poids);
    }

    return graphe;
}

void graphe_afficher(Graphe* graphe)
{
    printf("graphe\n");

    printf("ordre = %d\n",graphe->ordre);
    //printf("listes d'adjacence :\n");

    for (int i=0; i<graphe->ordre; i++)
    {

        afficher_successeurs(graphe->pSommet, i);

    }
    printf("\n");
}


void union1(int belongs[],int c1,int c2, int n)
{
    int i;
    for(i=0;i<n;i++)
        if(belongs[i]==c2)
            belongs[i]=c1;
}

int find(int belongs[],int vertexno)
{
    return(belongs[vertexno]);
}


void KRUSKAL(Graphe* g)
{
    int i, j, belongs[MAX], cno1, cno2;

    ///listeArrete est une liste d'arrete qui stock toutes les arretes du graphe
    edge_list *listeArrete;
    listeArrete = (edge_list *) malloc(sizeof(edge_list));
    listeArrete->data = (pArc *) malloc(listeArrete->n * sizeof(pArc));
    listeArrete->n = 0;

    ///ListeMST est une liste d'arrete qui sotck toutes les arretes de l'arbre couvrant de poids minimum
    edge_list *ListeMST;
    ListeMST = (edge_list *) malloc(sizeof(edge_list));
    ListeMST->data = (pArc *) malloc(ListeMST->n * sizeof(pArc));
    ListeMST->n = 0;

    ///Creation liste arrete
    for(i=0; i<g->ordre; i++)
    {
        pArc arc = g->pSommet[i]->arc;
        while(arc!=NULL)
        {
            listeArrete->data[listeArrete->n] = arc;
            arc=arc->arc_suivant;
            listeArrete->n++;
        }
    }

    ///tri de la liste d'arrete selon l'ordre croissant des poids
    pArc temp;
    for (i = 1; i < listeArrete->n; i++)
    {
        for (j = 0; j < listeArrete->n - 1; j++)
        {
            if (listeArrete->data[j]->poids > listeArrete->data[j + 1]->poids) {
                temp = listeArrete->data[j];
                listeArrete->data[j] = listeArrete->data[j + 1];
                listeArrete->data[j + 1] = temp;
            }
        }
    }

    ///affichage liste triée
    printf("LISTE TRIEEEEEEE :\n");
    for(i=0; i<listeArrete->n; i++)
    {

        printf("%d -> %d poids: %d \n",listeArrete->data[i]->depart, listeArrete->data[i]->sommet, listeArrete->data[i]->poids);

    }


    for (i = 0; i < g->ordre; i++)
    {
        belongs[i] = i;
    }

    for (i = 0; i < listeArrete->n; i++)
    {
        ///cno1 et cno2 sont les sommet de départ et d'arrivée d'un arrete
        cno1 = find(belongs, listeArrete->data[i]->depart);
        cno2 = find(belongs, listeArrete->data[i]->sommet);

        ///Si le sommet de départ est différent de celui d'arrivée on ajoute l'arrete dans l'arbre couvrant
        ///C'est pour éviter les boucles 
        if (cno1 != cno2)
        {
            ListeMST->data[ListeMST->n] = listeArrete->data[i];
            ListeMST->n = ListeMST->n + 1;
            union1(belongs, cno1, cno2, g->ordre);
        }
    }

    ///On affiche l'arbre et son poids
    int cost=0;
    printf("\n\nLes arretes qui composent l'arbre de poids couvrant minimum sont :\n");
    for(i=0;i<ListeMST->n;i++)
    {
        printf("\n%d --> %d , Poids : %d",ListeMST->data[i]->depart,ListeMST->data[i]->sommet,ListeMST->data[i]->poids);
        cost=cost+ListeMST->data[i]->poids;
    }

    printf("\n\nLe poids total de l'arbre couvrant de poids minimum est : %d",cost);

}