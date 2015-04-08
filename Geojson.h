#ifndef GEOJSON_H
#define GEOJSON_H
#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>    // std::sort
#include <vector>       // std::vector

namespace geojson_ns{

class Geometry {
public:
Geometry(const std::string& s="");
void afficher(std::ostream& o) const;
private :
    std::string d_type;
};

class GeometryCollection {
public:
GeometryCollection(const std::string& s="GeometryCollection");
void ajouterGeometry(const Geometry& g);
Geometry getGeometry(int i) const;
std::vector<Geometry> geometries() const;
friend std::ostream& operator<<(std::ostream& os, const GeometryCollection& gc);
void afficher(std::ostream& o) const;


private :
    std::string d_type;
    std::vector<Geometry> d_collection;
};


class Point : Geometry{

public:
    Point(double lattitude=.0, double longitude=.0);
    Point(const Point& p);
    double lattitude() const;
    double longitude() const;
    friend std::ostream& operator<<(std::ostream& o, const Point& c);
    void afficher(std::ostream& o) const;

protected :
     double d_lattitude,d_longitude;
};


class Position : public Point{

public:
    Position(const Point& p,double elevation=.0);
    Position(double lattitude=.0, double longitude=.0,double elevation=.0);
    double lattitude() const;
    double longitude() const;
    double altitude() const;
    friend std::ostream& operator<<(std::ostream& o, const Position& p);
    void afficher(std::ostream& o) const;

private :
     Point d_point;
     double d_altitude;
};



class LineString : Geometry {
public:
    LineString(const std::vector<Position>& p);
    LineString(const LineString &ls);
    void ajouterPosition(const Position& p);
    Position getPosition(int i) const;
    std::vector<Position> positions() const;
    friend std::ostream& operator<<(std::ostream& os, const LineString& ls);
    void afficher(std::ostream& o) const;

private:

    std::vector<Position> d_positions;
};

class MultiLineString : Geometry {
public:
    MultiLineString(const std::vector<LineString>& ls);
    MultiLineString(const MultiLineString &mls);
    void ajouterLineString(const LineString& ls);
    LineString getLineString(int i) const;
    std::vector<LineString> linestrings() const;
    friend std::ostream& operator<<(std::ostream& os, const MultiLineString& mls);
    void afficher(std::ostream& o) const;

private:

    std::vector<LineString> d_linestrings;
};





}



#endif // GEOJSON_H


/*
 *
{
    "type": "FeatureCollection",
    "features": [
        {
            "type": "Feature",
            "properties": {
                "name": "Circuit 01"
            },
            "geometry": {
                "type": "LineString",
                "coordinates": [
                    [
                        7.216833,
                        47.907057,
                        288
                    ],
                    [
                        7.21684,
                        47.90696,
                        288
                    ]
                ]
            }
        }
    ]
}
 * */
