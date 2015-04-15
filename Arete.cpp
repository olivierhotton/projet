#include"Arete.h"
#include"Noeud.h"
using namespace std ;


Arete::Arete(int id , Noeud* n1, Noeud* n2 ):d_idArete(id),d_n1(n1),d_n2(n2){}

int Arete::get_id() const { return d_idArete;}

bool Arete::operator==(const Arete& a) const {
if(d_idArete != a.d_idArete) return false;
if(d_n1 != a.d_n1) return false;
if(d_n2 != a.d_n2) return false;
return true;
}

bool Arete::operator!=(const Arete& a) const { return !(*this == a); }
void Arete::print(ostream& o) const{
o << "id:" << d_idArete << "(" << "noeud 1: " << *d_n1 << "noeud 2: " << *d_n2 << ")" << endl ;
}
ostream& operator<<(ostream& o,const Arete& a){
a.print(o);
return o;
}
