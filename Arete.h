#ifndef ARETE_H
#define ARETE_H

#include<iostream>
#include"Noeud.h"
using namespace std;




/*
* Arete
*/


class Arete{
public:
    Arete(int id=0,Noeud* n1=nullptr,Noeud* n2=nullptr);
    int get_id()const;
    void print(ostream& o) const;
    bool operator==(const Arete& a) const;
    bool operator!=(const Arete& a) const;


protected :

    int d_idArete;
    Noeud *d_n1;
    Noeud *d_n2;
};

std::ostream& operator<<(std::ostream& , const Arete& );



 #endif
