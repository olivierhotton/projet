#ifndef ParcoursS_H
#define Parcours_H
#include <climits>
#include <iostream>
#include <fstream>
#include <vector>
#include"Arete.h"
#include"Chemin.h"
#include"Lieu.h"
using namespace std;






class Parcours : public Chemin, Interface_Quantifiable{

    public :

          Parcours(vector<Arete*> const&,double const&,double const&,double const&);

        bool operator!=(const Parcours& par )   const;
         bool operator==(const Parcours& par )   const;
         void print(std::ostream& ost) const;

          ~Parcours() ;
         // implementation de la interface " class abstret  Interface_Quantifiable "

          double pente() override;
          double denivele()override;
          double denivele_montant() override;
          double duree()override;
          double distance()override ;
    private:

        double  d_pente;
        double  d_distance;
        double  d_denivele;


};

std::ostream& operator<<(std::ostream& , const Parcours& );
std::istream& operator>>(std::istream& , Parcours& );






#endif







