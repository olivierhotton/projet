#include "Gpx.h"
#include "Geojson.h"
using namespace gpx_ns;
using namespace geojson_ns;




std::string recupererChamp(std::string& ligne,const std::string& tag){
    unsigned int pos;
    std::string champ;

    if( (pos = ligne.find(tag )) != std::string::npos ){
        champ = tag;

        //cas d'une balise trk

        //cas d'une balise quelconque
        //nettoyage de la balise pour récupérer le champ
        if( (pos = champ.find("<")) != std::string::npos ){
            champ.replace (pos,pos + 1 ,"");
        }
        if( (pos = champ.find(">")) != std::string::npos ){
            champ.replace (pos,pos + 1 ,"");
        }
        if( (pos = champ.find("/")) != std::string::npos ){
            champ.replace (pos,pos + 1 ,"");
        }

        //supprimer la balise fermante
        if( (pos = ligne.find("</" + champ + ">")) != std::string::npos )
        {
            ligne.replace (pos,pos + champ.length()+2 ,"<" + champ + ">");
        }

        //supprimer la balise ouvrante
        while( (pos = ligne.find("<" + champ + ">")) != std::string::npos )
        {
            ligne.replace (pos,pos + champ.length()+2 ,"");
        }

        //   std::cout << ligne << std::endl;


        return ligne;
    }
    else return "";



}



/**
 * @fn lireGPX
 * @brief lit un fichier GPX
 * @param str chaîne de caractères représentant le chemin d'accès au fichier GPX
 * @return    un objet gpx
 */

Gpx lireFichier(const std::string& str){
    // A CORRIGER ATOF
        Gpx g;   std::ifstream fs;
    if(! fs.is_open() )
    {
        std::string ligne;
        fs.open(str.c_str());

        std::string res;


        Trk track;
        TrkSeg seg;
        TrkPt p;

         long double coord[3];
        while(getline(fs, ligne))
        {
            //trk
            if ( (ligne.find("<trk>")) != std::string::npos)
            {
//                std::cout << "trk" << std::endl;

            }
            //nom
            if ( !(res=recupererChamp(ligne,"<name>")).empty())
            {
//                std::cout << res << std::endl;
                track = Trk(res);
//track.afficher();
            }
//            else
//            {
//                track = Trk();
//            }

            if ( (ligne.find("<trkseg>")) != std::string::npos)
            {
//                std::cout << "trkseg" << std::endl;
                seg = TrkSeg();
            }

            //extraire lattitude, longitude, altitude
            if (((ligne.find("<trkpt lat=\"")) != std::string::npos)&&((ligne.find("\" lon=\"")) != std::string::npos)&&((ligne.find("\">")) != std::string::npos))
            {

                //   std::cout << "traitement des coordonnees " << std::endl;

                int pos[4];*pos=0;


                // std::cout << ligne<<std::endl ;

                *pos=ligne.find("\"")+1;

                for(int i=1;i<4;i++)
                {
                    pos[i]=(ligne.substr(pos[i-1],ligne.length()-1)).find("\"")+1 + pos[i-1];
                }
                *coord = atof(ligne.substr(*pos,pos[1]-1).c_str());
                coord[1] = atof(ligne.substr(pos[2],pos[3]-1).c_str());
                //    std::cout << "ligne: "<< ligne << " |"<< *pos << " |"<< pos[1]<< " |" << pos[2] << " |"<< pos[3]<< std::endl;

//                std::cout << "lattitude: "<<*coord << " longitude: "<<coord[1];

            }

            //altitude
            if ( ligne.find("<ele>") != std::string::npos)
            {
                coord[2] =atof(recupererChamp(ligne,"<ele>").c_str());
//                std::cout << " altitude: " << coord[2] << std::endl;
                p = TrkPt(coord[0],coord[1],coord[2]);
                //p.afficher(std::cout);

            }



            //fin trkpt
            if ( ligne.find("</trkpt>") != std::string::npos)
            {
//                std::cout << "creer et ajouter le point dans le trkseg "  << std::endl;
            seg.ajouterPoint(p);

            }
            //fin trkseg
            if ( ligne.find("</trkseg>") != std::string::npos)
            {
           //seg.afficher(std::cout);
                track.ajouterSegment(seg);

            }
            //fin trk
            if ( ligne.find("</trk>") != std::string::npos)
            {
           // track.afficher(std::cout);
                g.ajouterTrack(track);
            }


        }
    }


    fs.close();
//g.afficher(std::cout);
    return g;
}



void toGeoJSON(const Gpx& g){

   // int i,j,k;
// récupérer mes tracks g.tracks()
    std::vector<Trk> tr;
    std::vector<TrkSeg> trs;
    std::vector<TrkPt> trp;
   // TrkSeg seg;
    Position p;
    LineString l= LineString();
    MultiLineString mls = MultiLineString();
         FeatureCollection fc = FeatureCollection();
        Feature f = Feature();
    tr = g.tracks();


    //pour chaque track
    for (auto i: tr){
        //récupérer le nom de la track    g.getTrack(0).nom()
   // std::cout << "Track\n";
        //récupérer les segments        g.getTrack(0).segments()


        trs = i.segments();
        //récupérer un segment     g.getTrack(0).getSegment(0)
        for (auto j: trs){
            //récupérer les points du segment     g.getTrack(0).getSegment(0).points()
  //  std::cout << "Segment\n";

            trp = j.points();



            //récupérer un point du segment     g.getTrack(0).getSegment(0).getPoint(0)
            for (auto k: trp){

                l.addPosition(Position(k.lattitude(),k.longitude(),k.altitude()));
            }
            //std::cout << l;
            mls.addLineString(l);
        }
       // std::cout << mls;
       /* property pr;
        pr.d_name ="";
        pr.d_value ="";

        f.addProperty(pr);*/
        f.setMember(&mls);
       // std::cout << f;
      fc.addFeature(&f);
    }



   //return GeoJson(&fc);
createFile("test_conversion.geojson",GeoJson(&fc));

}

