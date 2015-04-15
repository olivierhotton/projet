#include<iostream>
#include<cmath>

#include"Lieu.h"



using namespace std ;




     Lieu::Lieu(int const& idNoeud, double  const& lattitude, double const& longitude, double const&   altitude, string const&  name) : Noeud(idNoeud),d_lattitude(lattitude),d_longitude(longitude),d_altitude(altitude),d_nom(name){};
     Lieu::~Lieu(){};

bool Lieu::operator==(const Lieu& l) const
    {
      return ( d_idNoeud == l.d_idNoeud && d_lattitude == l.d_lattitude && d_longitude == l.d_longitude && d_altitude == l.d_altitude && d_nom == l.d_nom ) ;

    }

    bool Lieu::operator!=(const Lieu& l) const
     {
      return !(*this == l ) ;
     }
    void Lieu::print(std::ostream& ost) const
    {
       ost << "[" ;
       Noeud::print(ost) ;
       ost << "/altitude : "<< d_altitude << "/lattitude : "<< d_lattitude << "/longitude :" << d_longitude << "/nom :" << d_nom << "]"   ;

    }



    double Lieu::get_lattitude() const { return d_lattitude ;  }
    double Lieu::get_longitude() const{ return d_longitude ; }
    double Lieu::get_altitude() const{ return d_altitude ;}
    string Lieu::get_nom() const { return d_nom ; }



    std::ostream& operator<<(std::ostream& ost, const Lieu& l)
    {
      l.print(ost);
      return ost;
    }



