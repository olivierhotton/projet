#ifndef CHEMIN_H
#define CHEMIN_H
#include <climits>
#include <iostream>
#include <fstream>
#include <vector>
#include"Arete.h"

using namespace std;






class Chemin{

    public :

          Chemin(vector<Arete*> const&);

          bool operator!=(const Chemin& g )   const;
         bool operator==(const Chemin& g )   const;
         void print(std::ostream& ost) const;

          ~Chemin() ;

    private:
        vector<Arete*> d_tableauAretes;


};

std::ostream& operator<<(std::ostream& , const Chemin& );
std::istream& operator>>(std::istream& , Chemin& );






#endif







