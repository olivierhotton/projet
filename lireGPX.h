#ifndef LIREGPX_H
#define LIREGPX_H
#include "Gpx.h"
using namespace gpx_ns;
Gpx lireFichier(const std::string& str);
std::string recupererChamp(std::string& s,const std::string& tag);
#endif // LIREGPX_H
