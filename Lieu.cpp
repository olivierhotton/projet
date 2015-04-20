#include<iostream>
#include<cmath>
#include<string>
#include"Lieu.h"



using namespace std ;




Lieu::Lieu(int const& idNoeud, double  const& lattitude, double const& longitude, double const&   altitude, string const&  name) : Noeud(idNoeud),d_lattitude(lattitude),d_longitude(longitude),d_altitude(altitude),d_nom(name){};
Lieu::~Lieu(){};

bool Lieu::operator==(const Lieu& l) const
{
    return ( d_lattitude == l.d_lattitude && d_longitude == l.d_longitude && d_altitude == l.d_altitude && d_nom == l.d_nom ) ;

}

bool Lieu::operator!=(const Lieu& l) const
{
    return !(*this == l ) ;
}
void Lieu::print(std::ostream& ost) const
{
    ost << "[" ;
    Noeud::print(ost) ;
    ost << "/lattitude : "<< d_lattitude << " /longitude :" << d_longitude << "/altitude : "<< d_altitude<< " /nom :" << d_nom << "]"   ;

}


bool Lieu::operator <(const Lieu& l) const{

    if (d_longitude < l.d_longitude) return true;
    else
        if (d_longitude == l.d_longitude){
            if (d_lattitude < l.d_lattitude) return true;
            else
                if (d_lattitude == l.d_lattitude){
                    return d_altitude < l.d_altitude;
                }
                else return false;

        }
        else return false;
}
bool Lieu::operator <=(const Lieu& l) const {return *this<l || *this == l;}


double Lieu::get_lattitude() const { return d_lattitude ;  }
double Lieu::get_longitude() const{ return d_longitude ; }
double Lieu::get_altitude() const{ return d_altitude ;}
string Lieu::get_nom() const { return d_nom ; }

void Lieu::set_lattitude(double lattitude) {d_lattitude=lattitude;}
void Lieu::set_longitude(double longitude){d_longitude=longitude;}
void Lieu::set_altitude(double altitude){d_altitude=altitude;}
void Lieu::set_nom(const string &nom){d_nom=nom;}






std::ostream& operator<<(std::ostream& ost, const Lieu& l)
{
    l.print(ost);
    return ost;
}


void Lieu::test(){

    /*Lieu l1 = Lieu();
    std::cout << " L1: "<< l1 << std::endl;
    Lieu l2 = Lieu(l1.d_idNoeud,l1.d_lattitude ,l1.d_longitude,l1.d_altitude+1);
      std::cout << " L2: " << l2 << std::endl;
      if (l1<l2) std::cout <<  "<"  <<std::endl;
*/
}
