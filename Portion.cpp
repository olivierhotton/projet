#include<iostream>
#include<cmath>
#define pi 3.14159265358979323846
#define earthRadiusKm 6371.0
#include"Portion.h"
#include"Arete.h"


using namespace std ;


double deg2rad(double deg) {
  return (deg * pi / 180);
}


double rad2deg(double rad) {
  return (rad * 180 / pi);
}




     Portion::Portion(int id , Noeud* n1 , Noeud* n2 , double pente , double distance, double denivele  ): Arete(id,n1,n2),d_pente(pente),d_distance(distance),d_denivele(denivele){



     }
//     Portion::Portion(int id, Noeud *n1, Noeud *n2):Arete(id, n1,n2),d_pente(),d_distance(),d_denivele(){

//     }
     Portion::~Portion(){}

bool Portion::operator==(const Portion& p) const
    {

return ( d_idArete == p.d_idArete &&
         d_n1 ==  p.d_n1 &&
         d_n2 == p.d_n2 &&
         d_pente == p.d_pente  &&
         d_distance == p.d_distance &&
         d_denivele == p.d_denivele ) ;

    }

    bool Portion::operator!=(const Portion& p) const
     {
      return !(*this == p ) ;
     }
    void Portion::print(std::ostream& ost) const
    {
       ost <<"["  ;
       Arete::print(ost) ;
       ost << "/pente : "<< d_pente << "/distance : "<< d_distance << "/denivele :" << d_denivele << "]" ;
    }




   double Portion::distance()
{
  double lat1r, lon1r, lat2r, lon2r, u, v;
  lat1r = deg2rad(d_n1->get_lattitude());

  lon1r = deg2rad(d_n1->get_longitude());
  lat2r = deg2rad(d_n2->get_lattitude());
  lon2r = deg2rad(d_n2->get_longitude());
  u = sin((lat2r - lat1r)/2);
  v = sin((lon2r - lon1r)/2);
  return 2.0 * earthRadiusKm * asin(sqrt(u * u + cos(lat1r) * cos(lat2r) * v * v));

}

    double Portion::denivele() {
       return d_n2->get_altitude() - d_n1->get_altitude();}

    double Portion::pente() {

    double c1,c2,c3;
    c3= distance();
    if ((c2 = denivele()) != .0)
    {
        c1 = sqrt((c3*c3) -(c2*c2));
        return rad2deg(atan2(c2,c1));
    }
    else return .0;

    }

    double Portion::denivele_montant(){
       double d;
       if ( (d=denivele()) < .0)
            return .0;
        else

        return  d;
 }

    double Portion::duree(){
        double p = pente();
        double d = distance();
        if (p<0){ return d/15;}
        else
            if (p < 3){return d/10;}
            else if(p < 5) {return d/8;}
                else return d/5;

        }








    std::ostream& operator<<(std::ostream& ost, const Portion& p)
    {
      p.print(ost);
      return ost;
    }



