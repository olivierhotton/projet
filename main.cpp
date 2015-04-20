/*
 * Manquent implémentation parcours, chemin, interface
 * */

#include <iostream>
#include "Manipulateur.h"

using namespace manip_ns;
using namespace std;
int main()
{

    Gpx g = Manipulateur::lireGPX("c:/gpx/test.gpx");
    std::cout << g;
    Manipulateur m;
    m.testAlgo();
    return 0;
}

