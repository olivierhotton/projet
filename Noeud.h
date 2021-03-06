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
     bool operator==(const Noeud& n) const;
     virtual void print(std::ostream& ost) const;
     void read(std::istream& ist);

     virtual double get_lattitude() const=0;
     virtual double get_longitude() const =0 ;
     virtual double get_altitude() const =0;
     virtual string get_nom() const=0;
     int get_id() const;
     void set_id(int i) ;
     virtual void set_lattitude(double lattitude)  =0;
     virtual void set_longitude(double longitude)  =0;
     virtual void set_altitude(double altitude)  =0;
     virtual void set_nom(const std::string& nom)  =0;
     virtual ~Noeud() ;

    protected:
        int d_idNoeud;




    };

//std::ostream& operator<<(std::ostream& , Noeud* );
std::ostream& operator<<(std::ostream& , const Noeud& );
std::istream& operator>>(std::istream& , Noeud& );







 #endif

