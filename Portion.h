#ifndef PORTION_H
#define PORTION_H

#include <climits>
#include <iostream>
#include <fstream>

#include "Interface_Quantifiable.h"
#include "Arete.h"

using namespace std;





class Portion : public Arete, Interface_Quantifiable {

    public :
    Portion(int id = 0 , Noeud* n1=nullptr , Noeud* n2 =nullptr , double pente = 0.0, double distance =  0.0, double denivele =0.0);

   // Portion(int id = 0 , Noeud* n1=nullptr , Noeud* n2 =nullptr);



     Portion& operator=(const Portion& ) = default;
     bool operator!=(const Portion& n)   const;
     bool operator==(const Portion& n)   const;
     void print(std::ostream& ost) const;
    // implementation de la interface " class abstret  Interface_Quantifiable "

     double pente() override;
     double denivele()override;
     double denivele_montant() override;
     double duree()override;
     double distance()override ;

     ~Portion() ;

    private:

        double  d_pente;
        double  d_distance;
        double  d_denivele;


    };

std::ostream& operator<<(std::ostream& , const Portion& );
std::istream& operator>>(std::istream& , Portion& );



#endif






