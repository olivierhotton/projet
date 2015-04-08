#include "Gpx.h"
using namespace gpx_ns;

//Point

TrkPt::TrkPt(double lattitude, double longitude,double elevation):d_lattitude(lattitude),d_longitude(longitude),d_elevation(elevation){}
double TrkPt::lattitude()const{ return d_lattitude;}
double TrkPt::longitude()const{ return d_longitude;}
double TrkPt::altitude()const{ return d_elevation;}
void TrkPt::afficher(std::ostream &o)const {o << "lattitude : " << d_lattitude << " | longitude : " << d_longitude << " | altitude : " << d_elevation << std::endl;}
std::ostream& operator <<(std::ostream& o ,const TrkPt& p){
    p.afficher(o);
    return o ;
}


// Segment
TrkSeg::TrkSeg():d_trkpt(){}
TrkSeg::TrkSeg(const TrkSeg &ts):d_trkpt(ts.d_trkpt){}
void TrkSeg::ajouterPoint(const TrkPt &p){d_trkpt.push_back(p);}
std::vector<TrkPt> TrkSeg::points() const {return d_trkpt;}
TrkPt TrkSeg::getPoint(int i) const{ return d_trkpt[i];}
void TrkSeg::afficher(std::ostream& o)const {
    for(unsigned int i =0;i<d_trkpt.size();i++){
       d_trkpt[i].afficher(o);
    }

}

std::ostream& operator <<(std::ostream& os ,const TrkSeg& ts){
//    //A FAIRE
//    for(int i=0;i<ts.points().size();i++)
//    {
//         ts.getPoint(i).afficher(os);
//    }
//    return os;

}


// Track
//Trk::Trk():d_name(),d_trkseg(){}
void Trk::changerNom(const std::string &nom){d_name=nom;}
Trk::Trk(const std::string& nom): d_name(nom),d_trkseg(){}
Trk::Trk(const std::string &nom, const std::vector<TrkSeg>& trkseg): d_name(nom),d_trkseg(trkseg){}
void Trk::ajouterSegment(const TrkSeg &ts){    d_trkseg.push_back(ts);}
void Trk::afficher(std::ostream& o) const{

    for(unsigned int i =0;i<d_trkseg.size();i++){
        d_trkseg[i].afficher(o);
    }
}
std::string Trk::nom()const{return d_name;}
std::vector<TrkSeg> Trk::segments() const{ return d_trkseg;}
TrkSeg Trk::getSegment(int i) const{ return d_trkseg[i];}

//std::ostream& operator <<(std::ostream& o ,const Trk& t){

//        for(int i=0;i<t.segments().size();i++)
//        {
//             o << t.getSegment(i);

//        }
//        return o;
//}


//Gpx
Gpx::Gpx():d_trk(){}
Gpx::Gpx(const Gpx &g):d_trk(g.d_trk){}
void Gpx::ajouterTrack(const Trk &tr){d_trk.push_back(tr);}
void Gpx::afficher(std::ostream& o)const{
    for(unsigned int i =0;i<d_trk.size();i++){
        d_trk[i].afficher(o);
    }

}
