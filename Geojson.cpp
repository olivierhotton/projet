#include "Geojson.h"
using namespace geojson_ns;


//Geometry

Geometry::Geometry(const std::string &s):d_type(s){}
void Geometry::afficher(std::ostream& o)const {
 o << d_type << std::endl;
}

//GeometryCollection

GeometryCollection::GeometryCollection(const std::string &s):d_type(s),d_collection(){}
void GeometryCollection::ajouterGeometry(const Geometry& g){d_collection.push_back(g);}
Geometry GeometryCollection::getGeometry(int i) const { return d_collection[i];}
std::vector<Geometry> GeometryCollection::geometries() const { return d_collection;}
void GeometryCollection::afficher(std::ostream& o)const {
    for(unsigned int i =0;i<d_collection.size();i++){
        d_collection[i].afficher(o);
    }
}


//Point
Point::Point(const Point& p):Geometry("Point"),d_lattitude(p.d_lattitude),d_longitude(p.d_longitude){}
Point::Point(double lattitude, double longitude):Geometry("Point"),d_lattitude(lattitude),d_longitude(longitude){}
double Point::lattitude()const{ return d_lattitude;}
double Point::longitude()const{ return d_longitude;}
void Point::afficher(std::ostream &o) const {o << "lattitude : " << d_lattitude << " | longitude : " << d_longitude  << std::endl;}
std::ostream& operator <<(std::ostream& o ,const Point& p){
    p.afficher(o);
    return o ;
}



//Coordonnees
//protected ne marche pas
Position::Position(const Point &p, double elevation):d_point(p),d_altitude(elevation){}
Position::Position(double lattitude, double longitude, double elevation):d_point(lattitude,longitude),d_altitude(elevation){}
double Position::lattitude()const{ return d_point.lattitude();}
double Position::longitude()const{ return d_point.longitude();}
double Position::altitude()const{ return d_altitude;}
void Position::afficher(std::ostream &o) const {o << "lattitude : " << d_point.lattitude() << " | longitude : " << d_point.longitude() << " | altitude : " << d_altitude << std::endl;}
std::ostream& operator <<(std::ostream& o ,const Position& p){
    p.afficher(o);
    return o ;
}


// LineString
LineString::LineString(const std::vector<Position> &p):Geometry("LineString"),d_positions(p){}
LineString::LineString(const LineString &ls):Geometry("LineString"),d_positions(ls.d_positions){}
void LineString::ajouterPosition(const Position &p){d_positions.push_back(p); }
std::vector<Position> LineString::positions() const {return d_positions;}
Position LineString::getPosition(int i) const{ return d_positions[i];}
void LineString::afficher(std::ostream& o)const {
    for(unsigned int i =0;i<d_positions.size();i++){
        d_positions[i].afficher(o);
    }
}

// MultiLineString
    MultiLineString::MultiLineString(const std::vector<LineString>& ls):Geometry("MultiLineString"),d_linestrings(ls){}
MultiLineString::MultiLineString(const MultiLineString &mls):Geometry("MultiLineString"),d_linestrings(mls.d_linestrings){}
void MultiLineString::ajouterLineString(const LineString &ls){d_linestrings.push_back(ls);}
std::vector<LineString> MultiLineString::linestrings() const {return d_linestrings;}
LineString MultiLineString::getLineString(int i) const{ return d_linestrings[i];}
void MultiLineString::afficher(std::ostream& o)const {
    for(unsigned int i =0;i<d_linestrings.size();i++){
        d_linestrings[i].afficher(o);
    }
 }

