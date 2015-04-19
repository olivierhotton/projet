#include<iostream>
#include<cmath>
#include"Noeud.h"







     Noeud::Noeud(int idNoeud) : d_idNoeud(idNoeud){};
     Noeud::~Noeud(){};

   bool Noeud::operator==(const Noeud& n) const
    {
      return (d_idNoeud == n.d_idNoeud) ;
    }

    bool Noeud::operator!=(const Noeud& n) const
     {
      return (d_idNoeud != n.d_idNoeud) ;
     }
    void Noeud::print(std::ostream& ost) const
    {
      ost<<'('<<d_idNoeud<<')';
    }


    int Noeud::get_id() const
     {
      return d_idNoeud;
     }

    void Noeud::set_id(int i)
     {
       d_idNoeud = i;
     }
    std::ostream& operator<<(std::ostream& ost, const Noeud& n)
    {
      n.print(ost);
      return ost;
    }
//    std::ostream& operator<<(std::ostream& ost, Noeud* n)
//    {
//      n->print(ost);
//      return ost;
//    }



