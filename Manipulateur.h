#ifndef MANIPULATEUR_H
#define MANIPULATEUR_H

#include <climits>
#include <iostream>
#include <fstream>
#include "Gpx.h"
#include "Geojson.h"
#include "Graphe.h"
#include "Arete.h"
#include "Lieu.h"
#include "Noeud.h"
#include "Portion.h"
#include "Algorithme.h"

using namespace gpx_ns;
using namespace geojson_ns;

namespace manip_ns{


 class Manipulateur{
     
 public :
	
            Manipulateur(Graphe *g);
            void ecrire_fichier(); //ecrire un fichier geojson
            Graphe& creerGraphe();
		    void graphe2fs_aps();
		    void graphe2tableau_aretes();
		    void afficher_fsaps();
		    void GNO2GO();
		    double coutChemin(vector<int> indiceAretes);
		    double miseAJourCout(int modeCalcul); // entier contenant le mode de calcul
		    bool contientCircuit();
		    bool orienteON();
            static Gpx lireGPX(const std::string& str); // lit un fichier GPX et retourne un objet gpx
            static std::string recupererChampGPX(std::string& s,const std::string& tag);

            static void toGeoJSON(const Gpx& g); //devrait retourner un geoJSON mais plante
            static void testGraphe();
            static void testGPX();
            static void testGeoJSON();
            static void testAlgo();
     private :
	
            Graphe* monGraphe;
		    vector<Arete> tabAretes; 
		    vector<int> fs;
		    vector<int> aps;
            int** M_adj;
		    vector<double> tabCouts; // couts des aretes


};

}
#endif
