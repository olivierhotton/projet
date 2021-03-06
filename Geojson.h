#ifndef GEOJSON_H
#define GEOJSON_H
#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>    // std::sort
#include <vector>       // std::vector
#include<iomanip>
namespace geojson_ns{

class Property{
   public:
    Property(const std::string& name="",const std::string& value="");
    std::string name() const;
    std::string value() const;
private:
    std::string d_name;
    std::string d_value;

};

/*
 * @class Position
 * */
class Position{

public:
    Position(double lattitude=.0, double longitude=.0,double elevation=.0);
    Position(const Position& p);
    double lattitude() const;
    double longitude() const;
    double elevation() const;
    void print(std::ostream& o) const;
    static void test();
    bool operator <(const Position& p) const; //tri par ordre croissant longitude, lattitude,altitude
    bool operator ==(const Position& p) const;
    bool operator !=(const Position& p) const;
private :
    double d_lattitude,d_longitude,d_elevation;
};
std::ostream& operator<<(std::ostream&  o, const Position &p);
std::ostream& operator<<(std::ostream&  o, const std::vector<Position> &v);


class GJObject{
public:
    GJObject(const std::string& s="");
    virtual void print(std::ostream& o) const =0 ;
    std::string name() const;
    virtual std::vector<Position> positions() const=0;
    //virtual std::vector<Feature>& features() const =0;
protected :
    std::string d_name;

};

class GeoJson{
public:
    GeoJson(GJObject* g=nullptr);
    GeoJson(const GeoJson& g);
    void print(std::ostream& o) const;
    static void test();
    std::string content() const;
    GJObject* member() const;
//virtual std::vector<Feature>& features() const =0;
private:

GJObject* d_member;
};
std::ostream& operator <<(std::ostream& o, const GeoJson& g);






/*
 * @class Geometry
 * */
class Geometry : public GJObject{
public:
    Geometry(const std::string& s="");
    virtual void print(std::ostream& o) const override ;
    virtual std::vector<Position> positions()const =0;
    static void test();

};

std::ostream& operator <<(std::ostream& o, const Geometry& g);




/*
 * @class GeometryCollection
 *
 * */
class GeometryCollection : GJObject {
public:
    GeometryCollection(const std::string &s="GeometryCollection", const std::vector<Geometry *> &v=std::vector<Geometry*>());
    GeometryCollection(const GeometryCollection &gc);
    void addGeometry( Geometry *g= nullptr);
    Geometry *getGeometry(int i) const;
    std::vector<Geometry *> geometries() const;
    void print(std::ostream& o) const;
    static void test();
    std::vector<Position> positions()const override;
  //  std::vector<Geometry*> collection() const;

private :
    std::vector<Geometry*> d_collection;
};
std::ostream& operator<<(std::ostream& o, const GeometryCollection& gc);






/*
 * @class Point
 * */
class Point : public Geometry{

public:
    Point(const Position& pos=Position());
    Point(const Point& p);
    std::vector<Position> positions()const override;
    void print(std::ostream& o) const override ;
    static void test();
private :
    Position d_pos;
};
std::ostream& operator<<(std::ostream& o, const Point& p);

/*
 * @class MultiPoint
 * */

class MultiPoint : public Geometry {
public:
    MultiPoint(const std::vector<Position>& v=std::vector<Position>() );
    MultiPoint(const MultiPoint &mp);
    void addPosition(const Position& p=Position());
    Position getPosition(int i) const;
    std::vector<Position> positions() const override;
    void print(std::ostream& o) const override;
    static void test();

private:

    std::vector<Position> d_positions;
};

std::ostream& operator<<(std::ostream& o, const MultiPoint& mp);

/*
 * @class LineString
 * */
class LineString : public Geometry {
public:
    LineString(const std::vector<Position>& v=std::vector<Position>() );
    LineString(const LineString &ls);
    void addPosition(const Position& p=Position());
    Position getPosition(int i) const;
    std::vector<Position> positions() const override;
    void print(std::ostream& o) const override;
    static void test();

private:

    std::vector<Position> d_positions;
};

std::ostream& operator<<(std::ostream& o, const LineString& ls);



/*
 * @class MultiLineString
 * */
class MultiLineString : public Geometry {
public:
    MultiLineString(const std::vector<LineString>& ls=std::vector<LineString>());
    MultiLineString(const MultiLineString &mls);
    void addLineString(const LineString& ls=LineString());
    LineString getLineString(int i) const;
    std::vector<LineString> linestrings() const;
    void print(std::ostream& o) const override;
    std::vector<Position> positions()const override;
    static void test();

private:

    std::vector<LineString> d_linestrings;
};

std::ostream& operator<<(std::ostream& o, const MultiLineString& mls);


/*
 * @class Feature
 * */
class Feature : public GJObject {

public:
    Feature(const std::string& name="Feature", const std::vector<Property>& properties = std::vector<Property>(), Geometry* member=nullptr);
    Feature(const Feature& f);
   Geometry* member() const ;
    //std::string nom() const;
   void setMember(Geometry* member=nullptr);
    std::vector<Property> properties() const;
    void addProperty(const Property& p);
    void print(std::ostream& o) const ;
    static void test();
 std::vector<Position> positions()const override;
private:
   // std::string d_name;
    std::vector<Property> d_properties;
    Geometry* d_member;
};

std::ostream& operator<<(std::ostream& o, const Feature& f);



class FeatureCollection : public GJObject{
public:
    FeatureCollection(const std::string &s="FeatureCollection", const std::vector<Feature *> &v=std::vector<Feature*>());
    FeatureCollection(const FeatureCollection &fc);
    void addFeature( Feature *f= nullptr);
    Feature* getFeature(int i) const;
    std::vector<Feature*> features() const;
    void print(std::ostream& o) const;
    static void test();
    std::vector<Position> positions()const override;
    //std::vector<Feature*> collection() const;

private:

    std::vector<Feature* > d_collection;
};

std::ostream& operator <<(std::ostream& o , const FeatureCollection& fc);



void createFile(const std::string& path,const GeoJson& g) ;
}



#endif // GEOJSON_H



