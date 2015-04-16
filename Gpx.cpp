#include "Gpx.h"
#include <iomanip>
using namespace gpx_ns;

//Point

TrkPt::TrkPt(double lattitude, double longitude, double elevation):d_lattitude(lattitude*1.0f),d_longitude(longitude*1.0f),d_elevation(elevation*1.0f){}
TrkPt::TrkPt(const TrkPt &p):d_lattitude(p.d_lattitude),d_longitude(p.d_longitude),d_elevation(p.d_elevation){}
double TrkPt::lattitude()const{ return d_lattitude;}
double TrkPt::longitude()const{ return d_longitude;}
double TrkPt::altitude()const{ return d_elevation;}
void TrkPt::afficher(std::ostream &o)const {
    o<<"<trkpt lat=\"" << std::setprecision(8) << d_lattitude << "\" lon=\""  <<  d_longitude <<"\"> \n<ele>" << d_elevation << "</ele>\n</trkpt>\n";
    //   o << "lattitude : " << d_lattitude << " | longitude : " << d_longitude << " | altitude : " << d_elevation << std::endl;}
}
std::ostream& gpx_ns::operator <<(std::ostream& o ,const TrkPt& p){
    p.afficher(o);
    return o ;
}

bool TrkPt::operator <(const TrkPt& p) const{

    if (d_lattitude < p.d_lattitude) return true;
    else
        if (d_lattitude == p.d_lattitude){
            if (d_longitude < p.d_longitude) return true;
                else
                if (d_longitude == p.d_longitude){
                    return d_elevation < p.d_elevation;
                }
            else return false;

        }
    else return false;

}

bool TrkPt::operator ==(const TrkPt& p) const{
    if(d_lattitude != p.d_lattitude) return false;
    if(d_longitude != p.d_longitude) return false;
    if(d_elevation != p.d_elevation) return false;
    return true;
}

bool TrkPt::operator !=(const TrkPt& p) const{ return !(*this == p);}

void TrkPt::test() {


TrkPt p = TrkPt(47.907214,7.217248,289);
TrkPt pp = TrkPt(p.d_lattitude,p.d_longitude,p.d_elevation);

if (p<pp) std::cout <<"inferieur"<<std::endl;

}

// Segment

TrkSeg::TrkSeg(const std::vector<TrkPt> &trkpt):d_trkpt(trkpt){}
TrkSeg::TrkSeg(const TrkSeg &ts):d_trkpt(ts.d_trkpt){}
void TrkSeg::ajouterPoint(const TrkPt &p){d_trkpt.push_back(p);}
std::vector<TrkPt> TrkSeg::points() const {return d_trkpt;}
TrkPt TrkSeg::getPoint(int i) const{ return d_trkpt[i];}
void TrkSeg::afficher(std::ostream& o)const {
    for(unsigned int i =0;i<d_trkpt.size();i++){
        d_trkpt[i].afficher(o);
    }
}



std::ostream& gpx_ns::operator <<(std::ostream& os ,const TrkSeg& ts){
    os << "<trkseg>\n";
    for(unsigned int i=0;i<ts.points().size();i++)
    {
        os << ts.getPoint(i);
    }
    os << "</trkseg>\n";
    return os;

}
void TrkSeg::test() {
    std::vector<TrkPt> v;
    v.push_back(TrkPt());
    v.push_back(TrkPt(1.1,2.2,3.3));
    std::cout << TrkSeg(v);
}

// Track
//Trk::Trk():d_name(),d_trkseg(){}
void Trk::changerNom(const std::string &nom){d_name=nom;}
//Trk::Trk(const std::string& nom): d_name(nom),d_trkseg(){}
Trk::Trk(const std::string &nom, const std::vector<TrkSeg>& trkseg): d_name(nom),d_trkseg(trkseg){}
void Trk::ajouterSegment(const TrkSeg &ts){    d_trkseg.push_back(ts);}
void Trk::afficher(std::ostream& o) const{


    o << "<trk>\n<name>"<<d_name<<"</name>\n<trkseg>";
  for(unsigned int i=0;i<d_trkseg.size();i++)
    {
        //    o << "segment : " << i <<std::endl;
        o << d_trkseg[i];
    }
    o << "\n</trkseg>\n</trk>\n";

}
std::string Trk::nom()const{return d_name;}
std::vector<TrkSeg> Trk::segments() const{ return d_trkseg;}
TrkSeg Trk::getSegment(int i) const{ return d_trkseg[i];}

std::ostream& gpx_ns::operator <<(std::ostream& o ,const Trk& t){
    t.afficher(o);
    return o;
}



void Trk::test(){


    std::vector<TrkPt> v,w;
    v.push_back(TrkPt());
    v.push_back(TrkPt(1.1,2.2,3.3));
    w.push_back(TrkPt(5,6,7.99));
    w.push_back(TrkPt(11,122.2,3.3));

    std::vector<TrkSeg> z;
    z.push_back(v);

    Trk t1=Trk("test 1",z);
    z.push_back(w);
    Trk t2=Trk("test 2",z);
    std::cout <<  t2;


}

//Gpx
Gpx::Gpx(const Gpx &g):d_trk(g.d_trk){}
Gpx::Gpx(const std::vector<Trk> &tr):d_trk(tr){}
void Gpx::ajouterTrack(const Trk &tr){d_trk.push_back(tr);}
void Gpx::afficher(std::ostream& o)const{


    o << "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\" ?>\n<gpx>\n";
    for(unsigned int i=0;i<d_trk.size();i++)
    {
        o << d_trk[i];

    }
    o << "</gpx>\n";

}
std::vector<Trk> Gpx::tracks() const {return d_trk;}
Trk Gpx::getTrack(int i) const {return d_trk[i];}
std::ostream& gpx_ns::operator <<(std::ostream& o, const Gpx& g){

g.afficher(o);
    return o;

}


void Gpx::test(){
    std::vector<TrkPt> v,w;
    v.push_back(TrkPt());
    v.push_back(TrkPt(47.907107,7.216957,290));
    w.push_back(TrkPt(47.907175,7.217138,289));
    w.push_back(TrkPt(47.907214,7.217248,289));

    std::vector<TrkSeg> z;
    z.push_back(v);

    Trk t1=Trk("test 1",z);
    z.push_back(w);
    Trk t2=Trk("test 2",z);
    //std::cout <<  t2;
    std::vector<Trk> vtrk;
    vtrk.push_back(t1);


    //for(auto i:vtrk) std::cout << i <<",";
    Gpx g=Gpx(vtrk);
    //std::cout << g;
    g.ajouterTrack(t2);
    std::cout << g;



}

void gpx_ns::createFile(const std::string &path, Gpx &g){

    std::ofstream fs;
    if(! fs.is_open() )
    {
        fs.open(path.c_str());
        g.afficher(fs);
    }
    fs.close();

}

