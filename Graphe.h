#ifndef GRAPHE_H
#define GRAPHE_H
#include <climits>
#include <iostream>
#include <fstream>
#include"Arete.h"
#include <vector>

using namespace std;






class Graphe{

    public :

          Graphe(vector<Arete*> const& tableauAretes, vector<Noeud*> const& tabNoeuds);

          bool operator!=(const Graphe& g )   const;
         bool operator==(const Graphe& g )   const;
         void print(std::ostream& ost) const;

          ~Graphe() ;

    private:
        vector<Arete*> d_tableauAretes;
        vector<Noeud*> d_tabNoeuds;

};

std::ostream& operator<<(std::ostream& , const Graphe& );
std::istream& operator>>(std::istream& , Graphe& );






#endif







