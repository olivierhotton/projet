#include "Geojson.h"

using namespace geojson_ns;


//Property
Property::Property(const std::string &name, const std::string &value):d_name(name),d_value(value){}
std::string Property::name() const {return d_name;}
std::string Property::value() const {return d_value;}

//GJObject
GJObject::GJObject(const std::string &s):d_name(s){}
std::string GJObject::name()const{return d_name;}

//GeoJSON
GeoJson::GeoJson(GJObject *g):d_member(g){}
GeoJson::GeoJson(const GeoJson &g):d_member(g.d_member){}
void GeoJson::print(std::ostream& o) const{
    if (d_member != nullptr) d_member->print(o);
}

GJObject* GeoJson::member()const{return d_member;}
//std::vector<Feature*> FeatureCollection::collection() const{ return d_collection;}


void GeoJson::test(){
    FeatureCollection fc = FeatureCollection();

    MultiPoint mp = MultiPoint(std::vector<Position>(1,Position(1,2.5,3)));
    mp.addPosition(Position(10,72,300));
    mp.addPosition(Position(1,987,345));
    std::vector<Property> v ;
    Property p1 = Property("p1","val1");
    Property p2 = Property();
    v.push_back(p1);
    v.push_back(p2);
    Feature f1 =  Feature("Feature",v,&mp);

    LineString l1 = LineString(std::vector<Position>(1,Position(1,2.5,3)));
    LineString l2 = LineString(std::vector<Position>(1,Position(59.5,753)));
    //MultiLineString mls = MultiLineString();
    //mls.addLineString(l1);
   // mls.addLineString(l2);



    Property p4 = Property("p3","val3");
    Property p3 = Property();
    v.push_back(p3);
    v.push_back(p4);
    //Feature f2 =  Feature("Feature",v,&mls);


    fc.addFeature(&f1);
    //fc.addFeature(&f2);


    std::cout << GeoJson(&f1);

}

std::ostream& geojson_ns::operator <<(std::ostream& o , const GeoJson& g){
    g.print(o);
    return o;
}


//Geometry
Geometry::Geometry(const std::string &s):GJObject(s){}
void Geometry::print(std::ostream& o)const {
    o <<d_name << std::endl;
}


std::ostream& geojson_ns::operator <<(std::ostream& o, const Geometry& g){

    g.print(o);
    return o;
}
void Geometry::test(){

    //std::cout <<  Geometry("test");

}



//Position

Position::Position(double lattitude, double longitude, double elevation):d_lattitude(lattitude*1.0f), d_longitude(longitude*1.0f), d_elevation(elevation*1.0f){}
Position::Position(const Position &p):d_lattitude(p.d_lattitude),d_longitude(p.d_longitude),d_elevation(p.d_elevation){}
double Position::lattitude()const{ return d_lattitude;}
double Position::longitude()const{ return d_longitude;}
double Position::elevation()const{ return d_elevation;}
void Position::print(std::ostream &o) const { o << "["  << std::setprecision(8) <<longitude() << ", "<< lattitude() << ", "  <<elevation() << "]"; }


bool Position::operator <(const Position& p) const{

    if (d_longitude < p.d_longitude) return true;
    else
        if (d_longitude == p.d_longitude){
            if (d_lattitude < p.d_lattitude) return true;
                else
                if (d_lattitude == p.d_lattitude){
                    return d_elevation < p.d_elevation;
                }
            else return false;

        }
    else return false;

}

bool Position::operator ==(const Position& p) const{
    if(d_lattitude != p.d_lattitude) return false;
    if(d_longitude != p.d_longitude) return false;
    if(d_elevation != p.d_elevation) return false;
    return true;
}

bool Position::operator !=(const Position& p) const{ return !(*this == p);}


std::ostream& geojson_ns::operator<<(std::ostream& o ,const Position &p){
    p.print(o);
    return o ;
}

std::ostream& geojson_ns::operator <<(std::ostream& o ,const std::vector<Position>& v){
    int nb=v.size()-1;
    for(int i=1;i<=nb;i++){

        o << v[i-1] << ",";
        if (i%5 ==0 ) o<<"\n     ";
    }
    o << v[nb] <<"\n";

    return o;
}

void Position::test(){
    Position p =Position(47.907107,7.216957,290);

    Position pp = Position(p.d_lattitude,p.d_longitude+1,p.d_elevation);
    if (p < pp) std::cout << p << " inferieur a " <<pp<<std::endl;
    if (p == pp) std::cout << p << " egal a " <<pp<<std::endl;
    if (p != pp) std::cout << p << " different de " <<pp<<std::endl;
}

//Point
Point::Point(const Point& p):Geometry("Point"),d_pos(p.d_pos){}
Point::Point(const Position& pos):Geometry("Point"),d_pos(pos){}
void Point::print(std::ostream &o) const  {
    o << "{ \"type\": \"" << name() << "\", \"coordinates\": " << d_pos << " }\n";
}
std::ostream& geojson_ns::operator <<(std::ostream& o ,const Point& p){
    p.print(o);
    return o ;
}

std::vector<Position> Point::positions() const{
    return std::vector<Position>(1,d_pos);
}

void Point::test(){
    Point p = Point(Position(47.907107,7.216957,290));
    std::cout << Point(p);

}


// MultiPoint
MultiPoint::MultiPoint(const std::vector<Position> &v):Geometry("MultiPoint"),d_positions(v){}
MultiPoint::MultiPoint(const MultiPoint &mp):Geometry("MultiPoint"),d_positions(mp.d_positions){}
void MultiPoint::addPosition(const Position &p){d_positions.push_back(p); }
std::vector<Position> MultiPoint::positions() const {

    return d_positions;


}
Position MultiPoint::getPosition(int i) const{ return d_positions[i];}
void MultiPoint::print(std::ostream& o)const {
    signed int nb=d_positions.size() -1;
    o << "{\"type\": \"" << name() << "\",\n \"coordinates\": [ ";
    if(nb>=0){
    for(signed int i =0;i<nb;i++){
        d_positions[i].print(o);
        o << ", ";
    }
    d_positions[nb].print(o);
    }
    o << " ]\n}\n";
}

std::ostream& geojson_ns::operator <<(std::ostream& o, const MultiPoint& mp){
    mp.print(o);
    return o;
}
void MultiPoint::test(){

    MultiPoint mp = MultiPoint(std::vector<Position>(1,Position(1,2.5,3)));
    mp.addPosition(Position(10,72,300));
    std::cout << mp;
}


// LineString
LineString::LineString(const std::vector<Position> &v):Geometry("LineString"),d_positions(v){}
LineString::LineString(const LineString &ls):Geometry("LineString"),d_positions(ls.d_positions){}
void LineString::addPosition(const Position &p){d_positions.push_back(p); }
std::vector<Position> LineString::positions() const {return d_positions;}
Position LineString::getPosition(int i) const{ return d_positions[i];}
void LineString::print(std::ostream& o)const {

    signed int nb=d_positions.size()-1;
    o << "{\"type\": \"" << name() << "\",\n \"coordinates\": [ ";
    if(nb>=0){
    for(signed int i =0;i<nb;i++){
        d_positions[i].print(o);
        o << ", ";

    }
    d_positions[nb].print(o);
    }
    o << " ]\n}\n";
}


std::ostream& geojson_ns::operator <<(std::ostream& o, const LineString& ls){
    ls.print(o);
    return o;
}
void LineString::test(){

    LineString l = LineString(std::vector<Position>(1,Position(1,2.5,3)));
    l.addPosition(Position(10,72,300));
    std::cout << l;
}


// MultiLineString
MultiLineString::MultiLineString(const std::vector<LineString>& ls):Geometry("MultiLineString"),d_linestrings(ls){}
MultiLineString::MultiLineString(const MultiLineString &mls):Geometry("MultiLineString"),d_linestrings(mls.d_linestrings){}
void MultiLineString::addLineString(const LineString &ls){d_linestrings.push_back(ls);}
std::vector<LineString> MultiLineString::linestrings() const {return d_linestrings;}
LineString MultiLineString::getLineString(int i) const{ return d_linestrings[i];}
void MultiLineString::print(std::ostream& o)const {
    signed int nb=d_linestrings.size() -1;
    o << "{ \"type\": \"" << name() << "\",\n  \"coordinates\": [\n";
    if (nb>=0){
    for(signed int i =0;i< nb ;i++){
        o << "   [ " << d_linestrings[i].positions() << " ] ,\n";

    }
    o << "   [ " << d_linestrings[nb].positions() << " ] \n";
    }
    o <<"]\n}\n";
}
std::ostream& geojson_ns::operator <<(std::ostream& o, const MultiLineString& mls){

    mls.print(o);
    return o;
}

std::vector<Position> MultiLineString::positions()const {
    std::vector<Position> tmp;
    std::vector<Position> pos;
    for(auto i : d_linestrings){ // pr chaque obj lineString

        tmp = i.positions();//recupérer le vecteur de positions

        for(auto j: tmp) //recupérer chaque position du vecteur
        {
         pos.push_back(j);
        }

    }



    return pos;

}
void MultiLineString::test(){
/*
    LineString l1 = LineString(std::vector<Position>(1,Position(1,2.5,3)));
    LineString l2 = LineString(std::vector<Position>(1,Position(59.5,753)));
    //MultiLineString mls = MultiLineString();
    //mls.addLineString(l1);
    mls.addLineString(l2);
    std::cout << mls;
*/

}

GeometryCollection::GeometryCollection(const std::string &s, const std::vector<Geometry*> &v):GJObject(s),d_collection(v){}
GeometryCollection::GeometryCollection(const GeometryCollection &gc):GJObject(gc.d_name),d_collection(gc.d_collection){}

void GeometryCollection::addGeometry(Geometry *g){ d_collection.push_back(g);}
Geometry* GeometryCollection::getGeometry(int i) const {return d_collection[i];}
std::vector<Geometry*> GeometryCollection::geometries() const {return d_collection;}
void GeometryCollection::print(std::ostream& o) const {

    o << "{ \"type\": \"" << d_name <<"\n \"geometries\": [\n{\n";
    signed int nb=d_collection.size() -1;
    if (nb >=0){
    for(signed int i =0;i< nb ;i++){

        d_collection[i]->print(o);
        o << ",";
    }
    d_collection[nb]->print(o);
    // o << " \n ]";
    }
    o << " \n ]\n}\n";

}
std::vector<Position> GeometryCollection::positions()const {
    std::vector<Position> tmp;
    std::vector<Position> pos;
    for(auto i : d_collection){ // pr chaque obj geometry

        tmp = i->positions();//recupérer le vecteur de positions

        for(auto j: tmp) //recupérer chaque position du vecteur
        {
         pos.push_back(j);
        }

    }



    return pos;

}
std::ostream& geojson_ns::operator<<(std::ostream& o, const GeometryCollection& gc){
    gc.print(o);
    return o;

}

//std::vector<Geometry*> GeometryCollection::collection() const{ return d_collection;}

void GeometryCollection::test() {
   /* GeometryCollection g = GeometryCollection();

    LineString l1 = LineString(std::vector<Position>(1,Position(1,2.5,3)));
    LineString l2 = LineString(std::vector<Position>(1,Position(59.5,753)));
    //MultiLineString mls = MultiLineString();
    Point p = Point(Position(1,2.5,3));
    MultiPoint mp = MultiPoint(std::vector<Position>(1,Position(1,2.5,3)));
    mp.addPosition(Position(10,72,300));

    //mls.addLineString(l1);
    mls.addLineString(l2);
    g.addGeometry(&mls);

    g.addGeometry(&l1);
    g.addGeometry(&p);
    g.addGeometry(&l2);
    g.addGeometry(&mp);
    std::cout << g;*/
}



//Feature
Feature::Feature(const std::string &name, const std::vector<Property> &properties, Geometry *member):GJObject(name),d_properties(properties),d_member(member){}
Feature::Feature(const Feature &f):GJObject(f.d_name),d_properties(f.d_properties),d_member(f.d_member){}
Geometry* Feature::member()const {return d_member;}
void Feature::addProperty(const Property &p){d_properties.push_back(p);}
//std::string Feature::nom() const{return d_name;}
std::vector<Property> Feature::properties() const {return d_properties;}
void Feature::setMember(Geometry *member){d_member=member;}
void Feature::print(std::ostream &o) const{
    o << "{ \"type\": \"Feature\",\n\"geometry\":\n";
    d_member->print(o);
    o<< ",\n";
    o <<  "\"properties\": { ";

    int nb = d_properties.size() -1;
    if(nb >0){
        for (int i=0;i<nb;i++){ o << "\"" << d_properties[i].name() <<"\": \"" << d_properties[i].value() << " \", ";    }
        o << "\"" << d_properties[nb].name() <<"\": \"" << d_properties[nb].value() << "\" }\n}\n";
    }
    else
    {
        o << "}\n";
    }

    }
              std::ostream& geojson_ns::operator <<(std::ostream& o , const Feature& f){
              f.print(o);
              return o;
    }

              void Feature::test(){
              MultiPoint mp = MultiPoint(std::vector<Position>(1,Position(1,2.5,3)));
              mp.addPosition(Position(10,72,300));
              mp.addPosition(Position(1,987,345));
              std::vector<Property> v =std::vector<Property>();
              Feature f =  Feature("Feature",v,&mp);
              f.print(std::cout);
    }

std::vector<Position> Feature::positions()const { return d_member->positions();}

              //FeatureCollection
        FeatureCollection::FeatureCollection(const std::string &s,  const std::vector<Feature *> &v):GJObject(s),d_collection(v){}
        FeatureCollection::FeatureCollection(const FeatureCollection &fc):GJObject(fc.d_name),d_collection(fc.d_collection){}
        void FeatureCollection::addFeature(Feature *f){d_collection.push_back(f);}
        Feature* FeatureCollection::getFeature(int i) const {return d_collection[i];}
        std::vector<Feature*> FeatureCollection::features() const { return d_collection;}
        void FeatureCollection::print(std::ostream& o) const {
            o << "{ \"type\": \"" << d_name <<"\", \n \"features\": [\n";
            unsigned int nb=d_collection.size() -1;
            for(unsigned int i =0;i< nb ;i++){
                d_collection[i]->print(o);
                o << "},\n";
            }
            d_collection[nb]->print(o);
            o << "\n}\n]\n}\n";
        }
std::vector<Position> FeatureCollection::positions()const {
    std::vector<Position> tmp;
    std::vector<Position> pos;

    for(auto i:d_collection) //pour chaque feature
    {
        //recuperer le vecteur de position
        tmp = i->positions();
        //ajouter chaque position du vecteur tmp dans le vecteur pos
        for(auto j:tmp) pos.push_back(j);

    }
    return pos;


}
        std::ostream& geojson_ns::operator<<(std::ostream& o, const FeatureCollection& fc){
            fc.print(o);
            return o;
        }

        void FeatureCollection::test() {
          /*  FeatureCollection fc = FeatureCollection();
            MultiPoint mp = MultiPoint(std::vector<Position>(1,Position(1,2.5,3)));
            mp.addPosition(Position(10,72,300));
            mp.addPosition(Position(1,987,345));
            std::vector<Property> v ;
            Feature f1 =  Feature("Feature",v,&mp);
            LineString l1 = LineString(std::vector<Position>(1,Position(1,2.5,3)));
            LineString l2 = LineString(std::vector<Position>(1,Position(59.5,753)));
            //MultiLineString mls = MultiLineString();
            //mls.addLineString(l1);
           // mls.addLineString(l2);
            Feature f2 =  Feature("Feature",v,&mls);
            fc.addFeature(&f1);
            fc.addFeature(&f2);
            std::cout << fc;
*/

        }

        void geojson_ns::createFile(const std::string& path,const GeoJson& g){
            std::ofstream fs;
            if(! fs.is_open() )
            {
                fs.open(path.c_str());
                g.print(fs);
      }
            fs.close();
        }



