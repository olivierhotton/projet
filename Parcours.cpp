#include"Chemin.h"
#include"Arete.h"
#include"Parcours.h"



using namespace std ;



Parcours::Parcours(vector<Arete*> const& tableauAretes,double const& pente , double const& distance , double const& denivele ): Chemin(tableauAretes) ,
   d_pente(pente),d_distance(distance),d_denivele(denivele){}



Parcours::~Parcours() {}


bool Parcours::operator==(const Parcours& par )   const {
     Chemin::operator==(par);
     return ( d_pente == par.d_pente  && d_distance == par.d_distance &&  d_denivele == par.d_denivele ) ;
    }

bool Parcours::operator!=(const Parcours& par )   const {
 return !(*this == par);
}


void Parcours::print(std::ostream& ost) const{

    ost << "Parcours est : " <<endl ;
    Chemin::print(ost);
    ost << "("<< "/pente : "<< d_pente << "/distance : "<< d_distance << "/denivele :" << d_denivele << ")";


}

ostream& operator<<(ostream& ost,const Parcours& par){
par.print(ost);
return ost;
}


double Parcours::distance()
{

        return .0;

}

 double Parcours::denivele() {
     return .0;
 }

 double Parcours::pente() {  return .0;  }

 double Parcours::denivele_montant(){
    return .0;
}

 double Parcours::duree(){return 0;}





