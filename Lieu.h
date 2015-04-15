#ifndef LIEU_H
#define LIEU_H

#include <climits>
#include <iostream>
#include <fstream>
#include  "Noeud.h"
#include "Interface_Quantifiable.h"

using namespace std;





class Lieu : public Noeud  {

    public :

     Lieu(int const&,double const&,double const&,double const&,string const& name="");



     Lieu& operator=(const Lieu& ) = default;
     bool operator!=(const Lieu& n)   const;
     bool operator==(const Lieu& n)   const;
    void print(std::ostream& ost) const;


     double get_lattitude() const override ;
     double get_longitude() const override ;
     double get_altitude() const override;
     string get_nom() const;

     ~Lieu() ;

    private:
        double  d_lattitude;
        double  d_longitude;
        double  d_altitude;
        string  d_nom;
    };

std::ostream& operator<<(std::ostream& , const Lieu& );
std::istream& operator>>(std::istream& , Lieu& );



#endif





