#include"Graphe.h"
#include"Arete.h"



using namespace std ;



Graphe::Graphe(vector<Arete*> const& tableauAretes, vector<Noeud*> const& tabNoeuds):d_tableauAretes(tableauAretes),d_tabNoeuds(tabNoeuds) {}

Graphe::~Graphe() {}


bool Graphe::operator==(const Graphe& g )   const {
         for(unsigned int i=0;i<d_tableauAretes.size();i++) {
         if 	(d_tableauAretes[i]!=g.d_tableauAretes[i]) return false ;
         }
          return true ;

}

bool Graphe::operator!=(const Graphe& g )   const {
 return !(*this == g);
}


void Graphe::print(std::ostream& ost) const{
 for(unsigned int i=0;i<d_tableauAretes.size();i++)
  ost << *(d_tableauAretes[i]) << endl;

}

ostream& operator<<(ostream& ost,const Graphe& g){
g.print(ost);
return ost;
}

