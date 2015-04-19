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

          Graphe(vector<Arete*> const& tableauAretes=vector<Arete*>(), vector<Noeud*> const& tabNoeuds=vector<Noeud*> ());

          bool operator!=(const Graphe& g )   const;
         bool operator==(const Graphe& g )   const;
         void print(std::ostream& ost) const;

         void setNoeuds(const std::vector<Noeud*>& n);
         void addNoeud(Noeud *n);
         Noeud* getNoeud(int i);
         Arete* getArete(int i);
         void setAretes(const std::vector<Arete *> a);

         void addArete(Arete *a);
          ~Graphe() ;
         vector<Arete*>& aretes();
         vector<Noeud *>& noeuds() ;


    private:
        vector<Arete*> d_tableauAretes;
        vector<Noeud*> d_tabNoeuds;

};

std::ostream& operator<<(std::ostream& , const Graphe& );
std::istream& operator>>(std::istream& , Graphe& );
//std::ostream& operator<<(std::ostream& o, std::vector<Arete*> a );





#endif







