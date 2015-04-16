#ifndef GPX_H
#define GPX_H


#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>    // std::sort
#include <vector>       // std::vector


namespace gpx_ns{

/*
 * @class TrkP
 *
 */

class TrkPt{

public:
    TrkPt(double lattitude=.0, double longitude=.0,double elevation=.0);
    TrkPt(const TrkPt& p);
    double lattitude() const;
    double longitude() const;
    double altitude() const;
    bool operator <(const TrkPt& p) const;
    bool operator ==(const TrkPt& p) const;
    bool operator !=(const TrkPt& p) const;
    void afficher(std::ostream& o) const;
    static void test() ;


private:
    double d_lattitude,d_longitude,d_elevation;


};
std::ostream& operator<<(std::ostream& o, const TrkPt& p);

/*
 * @class TrkSeg
 *
*/

class TrkSeg
{
public:

    TrkSeg(const std::vector<TrkPt>& trkpt=std::vector<TrkPt>());
    TrkSeg(const TrkSeg &ts);
    void ajouterPoint(const TrkPt& p);
    TrkPt getPoint(int i) const;
    std::vector<TrkPt> points() const;

    void afficher(std::ostream& o) const;
    static void test() ;

private:
    std::vector<TrkPt> d_trkpt;
};
std::ostream& operator<<(std::ostream& os, const TrkSeg& ts);

/*
 * @class Trk
 * */
class Trk{
public:

    Trk(const std::string& nom="", const std::vector<TrkSeg>& trkseg=std::vector<TrkSeg>());
    void changerNom(const std::string &nom);
    void ajouterSegment(const TrkSeg& ts);
    void afficher(std::ostream& o) const;
    std::string nom()const;
    std::vector<TrkSeg> segments() const;
    TrkSeg getSegment(int i) const;
    static void test();

private:
    std::string d_name;
    std::vector<TrkSeg> d_trkseg;

};

std::ostream& operator<<(std::ostream& o, const Trk& t);


/*
 * @class GPX
 */
class Gpx
{
public:

    Gpx(const Gpx& g);
    Gpx(const std::vector<Trk>& tr=std::vector<Trk>());
    void ajouterTrack(const Trk& tr);
    void afficher(std::ostream &o) const;
    std::vector<Trk> tracks() const;
    Trk getTrack(int i) const;
    static void test();

private:
    std::vector<Trk> d_trk;

};
std::ostream& operator<<(std::ostream& o, const Gpx& g);


void createFile(const std::string& path, Gpx& g);

}


#endif // GPX_H
