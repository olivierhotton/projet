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

     Lieu(int const& idNoeud=1, double  const& lattitude=.0, double const& longitude=.0, double const&   altitude=.0, string const&  name="");



     Lieu& operator=(const Lieu& ) = default;
     bool operator!=(const Lieu& n)   const;
     bool operator==(const Lieu& n)   const;
     bool operator<(const Lieu& l) const;
   //  bool operator<(Lieu* l) const;

     void print(std::ostream& ost) const override;




     double get_lattitude() const override ;
     double get_longitude() const override ;
     double get_altitude() const override;
     string get_nom() const;


     ~Lieu() ;
static void test();
    private:
        double  d_lattitude;
        double  d_longitude;
        double  d_altitude;
        string  d_nom;
    };

std::ostream& operator<<(std::ostream& , const Lieu& );
std::istream& operator>>(std::istream& , Lieu& );



#endif






