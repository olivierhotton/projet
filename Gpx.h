#ifndef GPX_H
#define GPX_H

#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>    // std::sort
#include <vector>       // std::vector

namespace gpx_ns{

class TrkPt{

public:
    TrkPt(double lattitude=.0, double longitude=.0,double elevation=.0);
    double lattitude() const;
    double longitude() const;
    double altitude() const;
    friend std::ostream& operator<<(std::ostream& o, const TrkPt& p);
    void afficher(std::ostream& o) const;

private:
    double d_lattitude,d_longitude,d_elevation;


};



class TrkSeg
{
public:
    TrkSeg();
    TrkSeg(const TrkSeg &ts);
    void ajouterPoint(const TrkPt& p);
    TrkPt getPoint(int i) const;
    std::vector<TrkPt> points() const;
     friend std::ostream& operator<<(std::ostream& os, const TrkSeg& ts);
    void afficher(std::ostream& o) const;


private:
    std::vector<TrkPt> d_trkpt;
};

class Trk{
public:
    //Trk();
    Trk(const std::string &nom="");
    Trk(const std::string& nom, const std::vector<TrkSeg>& trkseg);
    void changerNom(const std::string &nom);
    void ajouterSegment(const TrkSeg& ts);
    void afficher(std::ostream& o) const;
    friend std::ostream& operator<<(std::ostream& o, const Trk& t);
    std::string nom()const;
    std::vector<TrkSeg> segments() const;
    TrkSeg getSegment(int i) const;
private:
    std::string d_name;
    std::vector<TrkSeg> d_trkseg;

};

class Gpx
{
public:
    Gpx();
    Gpx(const Gpx& g);
    void ajouterTrack(const Trk& tr);
    void afficher(std::ostream &o) const;
    friend std::ostream& operator<<(std::ostream& o, const Gpx& g);

private:
    std::vector<Trk> d_trk;
};

}
#endif // GPX_H
