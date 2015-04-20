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
     //bool operator==(Noeud* n)   const override;
    // bool operator<(Noeud* n)   const override;
    // bool operator<=(Noeud* n)   const override;
     bool operator==(const Lieu& n)   const;
     bool operator<(const Lieu& l) const;
    bool operator<=(const Lieu& l) const;
   //  bool operator<(Lieu* l) const;

     void print(std::ostream& ost) const override;



     void set_lattitude(double lattitude) override;
     void set_longitude(double longitude)  override;
     void set_altitude(double altitude)  override;
     void set_nom(const std::string& nom)  override;

     double get_lattitude() const override ;
     double get_longitude() const override ;
     double get_altitude() const override;
     string get_nom() const override;


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






