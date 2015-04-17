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
    /*
     * Constructeur
     **/
            Manipulateur(Graphe *g=new Graphe());
           // Manipulateur();

            /* Graphe */
            static std::vector<Lieu> lieux(); //retourne la liste triée des sommets du graphe
            void afficher_fsaps();
            void GNO2GO();
            void graphe2fs_aps();
            void graphe2tableau_aretes();
            Graphe& creerGraphe();
            void creerLieux(const std::vector<Position>& vl);
            void trierLieux(); // par ordre croissant sans doublon
            void renumeroterLieux();
            /* Algo */
            double coutChemin(vector<int> indiceAretes);
            double miseAJourCout(int modeCalcul); // entier contenant le mode de calcul
            bool contientCircuit();
            bool orienteON();
            void updateMadj(const int id1, const int id2); // n = nombre de sommets du graphes
            void initMadj();

            static int indicePosition(const Position& pos, const std::vector<Position>& vpos);
            /* Gpx */
            static std::string recupererChampGPX(std::string& s,const std::string& tag);
            static Gpx lireGPX(const std::string& str); // lit un fichier GPX et retourne un objet gpx

            void toGeoJSON(const Gpx& g); //devrait retourner un geoJSON mais plante


            /* Geojson */
            void ecrire_fichier(); //ecrire un fichier geojson

            static std::vector<Position> positionAsc(const GeoJson& gj); // par ordre croissant sans doublon

           // static void creerArete(const GeoJson& gj); // n = nombre de sommets du graphes

            // static std::vector<Arete>& aretes(const Position& p1, const Position& p2);//a faire pour mise a jour du graphe


            /* Fichiers */

            /* Affichage */

            static void testGraphe();
            static void testGPX();
            static void testGeoJSON();
            static void testAlgo();
           //static std::vector<Arete *> creerArete(const std::vector<Arete>& va);



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
