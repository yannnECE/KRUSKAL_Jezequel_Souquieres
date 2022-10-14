#include "Graphe.h"

///SOURCES
// https://www.programiz.com/dsa/kruskal-algorithm
// https://www.thecrazyprogrammer.com/2014/03/kruskals-algorithm-for-finding-minimum-cost-spanning-tree.html

int main()
{
    ///On créer le graphe
    Graphe * g = lire_graphe("grapheKruskal.txt");

    ///On appele lafonction KRUSKAL
    KRUSKAL(g);

    return 0;
}
