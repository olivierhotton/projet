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

vector<Noeud*>& Graphe::noeuds() {
    return d_tabNoeuds;
}

vector<Arete*>& Graphe::aretes() {
    return d_tableauAretes;
}

void Graphe::setNoeuds(const std::vector<Noeud *> &n){ d_tabNoeuds = n;}
Noeud *Graphe::getNoeud(int i){
    Noeud* tmp = d_tabNoeuds[i];
    return tmp;
}
void Graphe::addNoeud(Noeud* n){d_tabNoeuds.push_back(n);}

void Graphe::setAretes(const std::vector<Arete*> a){ d_tableauAretes = a;}
void Graphe::addArete(Arete* a){d_tableauAretes.push_back(a);}
Arete* Graphe::getArete(int i){return d_tableauAretes[i];}
