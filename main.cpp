#include <iostream>
#include "lireGPX.h"
#include "Geojson.h"

using namespace gpx_ns;
using namespace geojson_ns;

int main()
{
  //  std::string fichier = "C:/Users/oliv/Downloads/gpx/test.gpx";
   // Gpx g = lireFichier(fichier);
 //   Point(1.0,2.0).afficher(std::cout);
    Position pos1 = Position(1.0,2.0,3.0);
    Position pos2 = Position(Point(1.1,2.0),3.0);
    std::vector<Position> v;
    v.push_back(pos1);
    v.push_back(pos2);
    LineString l = LineString(v);

    std::vector<LineString> mlsv;
    mlsv.push_back(l);
   LineString L2 = LineString(l);
   L2.ajouterPosition(Position(Point(10.0,15.5)));
           mlsv.push_back(L2);
    MultiLineString M = MultiLineString(mlsv);
    M.afficher(std::cout);

    return 0;
}

