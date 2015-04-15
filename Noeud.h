#ifndef NOEUD_H
#define NOEUD_H



#include <climits>
#include <iostream>
#include <fstream>


using namespace std;




class Noeud{

    public :

     Noeud(int);



     Noeud& operator=(const Noeud& ) = default;
     bool operator!=(const Noeud& n)   const;
     bool operator==(const Noeud& n)   const;
     void print(std::ostream& ost) const;
     void read(std::istream& ist);

     virtual double get_lattitude() const=0;
     virtual double get_longitude() const =0 ;
     virtual double get_altitude() const =0;
      int get_id() const;
     ~Noeud() ;

    protected:
        int d_idNoeud;




    };

std::ostream& operator<<(std::ostream& , const Noeud& );
std::istream& operator>>(std::istream& , Noeud& );







 #endif

