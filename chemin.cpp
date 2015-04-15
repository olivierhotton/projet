#include"Chemin.h"
#include"Arete.h"



using namespace std ;



Chemin::Chemin(vector<Arete*> const& tableauAretes) {
    for(unsigned int i=0;i<tableauAretes.size();i++)

        d_tableauAretes.push_back(tableauAretes[i]) ;

}

Chemin::~Chemin() {}


bool Chemin::operator==(const Chemin& c )   const {

        for(unsigned int i=0;i<d_tableauAretes.size();i++) {
         if 	(d_tableauAretes[i]!=c.d_tableauAretes[i]) return false ;
         }
          return true ;

}

bool Chemin::operator!=(const Chemin& c )   const {
 return !(*this == c);
}


void Chemin::print(std::ostream& ost) const{
 for(unsigned int i=0;i<d_tableauAretes.size();i++)
  ost << *(d_tableauAretes[i]) << endl;

}

ostream& operator<<(ostream& ost,const Chemin& c){
c.print(ost);
return ost;
}


