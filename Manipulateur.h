#ifndef MANIPULATEUR_H
#define MANIPULATEUR_H

#include <climits>
#include <iostream>
#include <fstream>
#include <vector>
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
            Manipulateur(Graphe *g=new Graphe(), GeoJson* gj=nullptr);
           // Manipulateur();

            /* Graphe */
            static std::vector<Lieu> lieux(); //retourne la liste triée des sommets du graphe
            void afficher_fsaps();
            void GNO2GO();
            void graphe2fs_aps();
            void graphe2tableau_aretes();
            void creerGraphe(const Gpx& g);
            void ajouterLieu(int i, double lattitude, double longitude, double altitude, const std::string& nom);
            void renumeroterLieux();
            /* Algo */
            double coutChemin(vector<int> indiceAretes);
            double miseAJourCout(int modeCalcul); // entier contenant le mode de calcul
            bool contientCircuit();
            bool orienteON();
            void updateMadj(const int i, const int j); // n = nombre de sommets du graphes
            void initMadj();
            void afficheAdj() const;
            int indicePosition(int g, int d, Noeud* n);
            /* Gpx */
            static std::string recupererChampGPX(std::string& s,const std::string& tag);
            static Gpx lireGPX(const std::string& str); // lit un fichier GPX et retourne un objet gpx

            void toGeoJSON(); //devrait retourner un geoJSON mais plante


            /* Geojson */
            void ecrire_fichier(); //ecrire un fichier geojson

            //static std::vector<Position> positionAsc(const GeoJson& gj); // par ordre croissant sans doublon

            void updateArete(); // maj vecteur arete a partir de m_adj

            // static std::vector<Arete>& aretes(const Position& p1, const Position& p2);//a faire pour mise a jour du graphe


            /* Fichiers */

            /* Affichage */
            void supprime_sommet(int *fs,int *aps,int index,vector<algo_ns::arete> &g);
            static void testGraphe();
            static void testGPX();
            static void testGeoJSON();
            static void testAlgo();
           //static std::vector<Arete *> creerArete(const std::vector<Arete>& va);

            /* Manipulation de données */

            void trier(std::vector<Noeud *> &tmp);

     private :
	
            Graphe* monGraphe;
            GeoJson* monGeoJson;
		    vector<Arete> tabAretes; 
            int* fs;
            int* aps;
            int** M_adj;
		    vector<double> tabCouts; // couts des aretes


};

}
#endif
