#include "Graphe.h"

///SOURCES
// https://www.programiz.com/dsa/kruskal-algorithm
// https://www.thecrazyprogrammer.com/2014/03/kruskals-algorithm-for-finding-minimum-cost-spanning-tree.html

///Lien GITHUB
// https://github.com/yannnECE/TP2_a_completer.cbp.git

int main()
{
    ///On créer le graphe
    Graphe * g = lire_graphe("grapheKruskal.txt");

    ///On appele lafonction KRUSKAL
    KRUSKAL(g);

    return 0;
}
