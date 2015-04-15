#ifndef LIREGPX_H
#define LIREGPX_H
#include "Gpx.h"
#include "Geojson.h"
using namespace gpx_ns;
using namespace geojson_ns;
Gpx lireFichier(const std::string& str);
std::string recupererChamp(std::string& s,const std::string& tag);
void toGeoJSON(const Gpx& g);
#endif // LIREGPX_H
