/*
 * Manquent implémentation parcours, chemin, interface
 * */

#include <iostream>
#include "Manipulateur.h"

using namespace manip_ns;
using namespace std;
int main()
{
//Manipulateur::testAlgo();
//Manipulateur::testGraphe();
//Manipulateur::testGPX();
    cout<<"Ca marche"<<endl;
   Manipulateur::testGeoJSON();

//    Noeud* n1 = new Lieu();
//    Noeud* n2 = new Lieu(0,1,2,3,"");

////    std::cout << *n1 << std::endl <<*n2 << std::endl;
//    std::vector<Arete*> a;
//    a.push_back(new Arete(0,n1,n2));
//    for (auto i :a)
//    {
//        std::cout << *i;
//}

    //Position::test();
    return 0;
}

