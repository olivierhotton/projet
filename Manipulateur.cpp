#include "Manipulateur.h"
using namespace gpx_ns;
using namespace geojson_ns;
using namespace algo_ns;
using namespace manip_ns;
using namespace std;

Manipulateur::Manipulateur(Graphe* g):monGraphe(g){}

/*
 * @function récupérer champ gpx
 * */
std::string Manipulateur::recupererChampGPX(std::string& ligne,const std::string& tag){
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

Gpx Manipulateur::lireGPX(const std::string& str){

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
            if ( !(res=recupererChampGPX(ligne,"<name>")).empty())
            {
                track = Trk(res);
            }

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
                coord[2] =atof(recupererChampGPX(ligne,"<ele>").c_str());
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



void Manipulateur::toGeoJSON(const Gpx& g){

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

//std::cout << GeoJson(&fc);
//   return GeoJson(&fc);
createFile("test_conversion.geojson",GeoJson(&fc));

}

void Manipulateur::testGraphe()
{
    Lieu l1 =  Lieu(1,50.45,7.33,280.0);
    Lieu l2 =  Lieu(2,47.48,7.33,260.0);


    Portion p = Portion(1,&l1,&l2,0,0,0);

    //std::cout << p <<std::endl;
    std::cout << p.distance() <<std::endl;
       std::cout << p.denivele() <<std::endl;
   std::cout << p.pente() <<std::endl;
    std::cout << p.denivele_montant() <<std::endl;
    std::cout << p.duree() <<std::endl;

 /*      std::cout <<  l1 <<std::endl;
        std::cout << l2 <<std::endl;

        vector<Arete*> tab_Aretes;

        tab_Aretes.push_back(A1);
        tab_Aretes.push_back(A2);
        tab_Aretes.push_back(A3);



        Graphe G1(tab_Aretes);
        cout << "affichage du graphe :" <<  endl ;
        cout << G1  <<  endl ;

        Lieu L1(1,3.4,2.2,1.2,"Lieu 1")  ;

        cout << "affichage du Lieu :" <<  endl ;
        cout << L1 <<  endl ;

        Portion* P1 = new Portion(1,&n1,&n2,2,3,7);

        cout << "affichage de la portion  :" <<  endl ;
        cout << *P1 ;
*/
}
void Manipulateur::testGPX(){

    //test point GPX
    //   TrkPt::test();
    //std::cout << TrkPt();

    //test segment GPX
    //
    //TrkSeg::test();
    //test track GPX
//    std::cout << TrkSeg();
    //  Trk::test();
//    std::cout << Trk();
    //test  GPX
    //  Gpx::test();
//std::cout <<Gpx();



}
void Manipulateur::testGeoJSON(){
    /*
     * GeoJSON
     * */
    //tes//t position
    // Position::test();
//    std::cout << Position();
    //test point
     //  Point::test();
//    std::cout << Point();
    //test MultiPoint
    // MultiPoint::test();
//    std::cout << MultiPoint();
    //test LineString
    //  LineString::test();
//std::cout << LineString();
    //test MultiLineString
    //    MultiLineString::test();
//    std::cout << MultiLineString();
    //Geometry
    //       Geometry::test();
    //std::cout << Geometry();
    //GeometryCollection
    // a verifier  GeometryCollection::test();
//std::cout << GeometryCollection();
    //Feature
    //    Feature::test();

    //FeatureCollection
     //   FeatureCollection::test();
    //GeoJSON
  //   GeoJson::test();
   //  GeoJson gs = GeoJson();


    //   gpx_ns::createFile("C:/Users/oliv/Downloads/gpx/testEciture.gpx",g);
//
    Gpx g = Manipulateur::lireGPX("C:/Users/oliv/Downloads/gpx/quart.gpx");

//std::cout << g;
//     Manipulateur::toGeoJSON(g);
    Manipulateur::toGeoJSON(g);

}


void Manipulateur::testAlgo(){

    int *fs,*aps,**cout1,s,*pred,*d;
        int n = 7;
        int m = 12;
        fs = new int[n+m+1];fs[0]=n+m;
        aps = new int[n+1];aps[0]=n;
        cout1 = new int*[n+1];
        for(int i=0;i<=n;i++){
            cout1[i] = new int[n+1];
        }
        fs[1] = 2;
        fs[2] = 5;
        fs[3] = 0; //1
        fs[4] = 5;
        fs[5] = 6;
        fs[6] = 0; //2
        fs[7] = 1;
        fs[8] = 4;
        fs[9] = 0; //3
        fs[10] = 7;
        fs[11] = 0; //4
        fs[12] = 3;
        fs[13] = 4;
        fs[14] = 7;
        fs[15] = 0; //5
        fs[16] = 5;
        fs[17] = 0; //6
        fs[18] = 6;
        fs[19] = 0; //7

        aps[1] = 1;
        aps[2] = 4;
        aps[3] = 7;
        aps[4] = 10;
        aps[5] = 12;
        aps[6] = 16;
        aps[7] = 18;

        for(int i=1;i<=n;i++){
            for(int j=1;j<=n;j++){
                cout1[i][j] = INT_MAX;
            }
        }

        cout1[1][2] = 1;
        cout1[1][5] = 3;
        cout1[2][5] = 1;
        cout1[2][6] = 4;
        cout1[3][1] = 0;
        cout1[3][4] = 2;
        cout1[4][7] = 4;
        cout1[5][3] = 1;
        cout1[5][4] = 6;
        cout1[5][7] = 0;
        cout1[6][5] = 1;
        cout1[7][6] = 1;

        s = 1;

        Algorithme algo;

        algo.dijkstra(fs,aps,cout1,s,pred,d);
        cout<<"****Test Djikstra****"<<endl;
        cout<<"pred : ["<<pred[1];
        for(int i=2;i<=n;i++){
            cout<<","<<pred[i];
        }
        cout<<"]"<<endl;

        cout<<"d : ["<<d[1];
        for(int i=2;i<=n;i++){
            cout<<","<<d[i];
        }
        cout<<"]"<<endl;


        delete(fs);
        delete(aps);
        for(int i=0;i<=n;i++){
            delete(cout1[i]);
        }
        delete(cout1);
        delete(pred);
        delete(d);

        n=8;
        m=13;
        arete *g,*t,a;
        g = new arete[m];
        //1
        a.s = 1;
        a.t = 2;
        a.cout = 1;
        g[0] = a;
        //2
        a.s = 1;
        a.t = 3;
        a.cout = 2;
        g[1] = a;
        //3
        a.s = 1;
        a.t = 4;
        a.cout = 3;
        g[2] = a;
        //4
        a.s = 2;
        a.t = 3;
        a.cout = 1;
        g[3] = a;
        //5
        a.s = 2;
        a.t = 5;
        a.cout = 2;
        g[4] = a;
        //6
        a.s = 2;
        a.t = 6;
        a.cout = 3;
        g[5] = a;
        //7
        a.s = 2;
        a.t = 7;
        a.cout = 3;
        g[6] = a;
        //8
        a.s = 3;
        a.t = 4;
        a.cout = 1;
        g[7] = a;
        //9
        a.s = 3;
        a.t = 7;
        a.cout = 4;
        g[8] = a;
        //10
        a.s = 4;
        a.t = 6;
        a.cout = 2;
        g[9] = a;
        //11
        a.s = 4;
        a.t = 7;
        a.cout = 2;
        g[10] = a;
        //12
        a.s = 4;
        a.t = 8;
        a.cout = 2;
        g[11] = a;
        //13
        a.s = 5;
        a.t = 6;
        a.cout = 2;
        g[12] = a;

        algo.trierAretes(g,m);
        algo.kruskal(g,n,m,t);
        cout<<"****Test Kruskal****"<<endl;
        for(int i=0;i<(n-1);i++){
            cout<<"["<<t[i].s<<","<<t[i].t<<","<<t[i].cout<<"]"<<endl;
        }

        delete(g);
        delete(t);

        g = new arete[8];
        //1
        a.s = 1;
        a.t = 6;
        g[0] = a;
        //2
        a.s = 1;
        a.t = 7;
        g[1] = a;
        //3
        a.s = 1;
        a.t = 2;
        g[2] = a;
        //4
        a.s = 2;
        a.t = 3;
        g[3] = a;
        //5
        a.s = 2;
        a.t = 4;
        g[4] = a;
        //6
        a.s = 2;
        a.t = 5;
        g[5] = a;
        //7
        a.s = 5;
        a.t = 8;
        g[6] = a;
        //8
        a.s = 5;
        a.t = 9;
        g[7] = a;
        int *h;
        algo.prufer(g,9,h);
        cout<<"****Test Prufer****"<<endl;
        cout<<"h: ["<<h[0];
        for(int i=1;i<7;i++){
            cout<<","<<h[i];
        }
        cout<<"]"<<endl;
        delete(g);
        delete(h);

        int *poids,**matrix; //*aps,*fs,n,m
        n = 5;m = 7;
        matrix = new int*[n+1];
        matrix[0] = new int[2]; matrix[0][0] = n; matrix[0][1] = m;
        for(int i=1;i<=n;i++){
            matrix[i] = new int[n+1];
            for(int j=1;j<=n;j++) matrix[i][j] = INT_MAX;
        }
        matrix[1][2] = 1;
        matrix[1][5] = 3;
        matrix[2][5] = 1;
        matrix[3][1] = 0;
        matrix[3][4] = 2;
        matrix[5][3] = 1;
        matrix[5][4] = 6;
        algo.matrix2all(matrix,fs,aps,poids);
        cout<<"****Test matrix2all****"<<endl;
        cout<<"aps: ["<<aps[0];
        for(int i=1;i<=n;i++){
            cout<<","<<aps[i];
        }
        cout<<"]"<<endl;
        cout<<"fs: ["<<fs[0];
        for(int i=1;i<=(n+m);i++){
            cout<<","<<fs[i];
        }
        cout<<"]"<<endl;
        cout<<"poids: ["<<poids[0];
        for(int i=1;i<=(n+m);i++){
            cout<<","<<poids[i];
        }
        cout<<"]"<<endl;

        algo.all2matrix(fs,aps,poids,matrix);
        cout<<"****Test all2matrix****"<<endl;
        cout<<"Matrix:"<<endl;
        for(int i=1;i<=n;i++){
            cout<<"| ";
            for(int j=1;j<=n;j++){
                switch(matrix[i][j]){
                    case INT_MAX:
                        cout<<"m ";
                        break;
                    default:
                        cout<<matrix[i][j]<<" ";
                        break;
                }
            }
            cout<<"|"<<endl;
        }

        for(int i=0;i<=n;i++){
            delete(matrix[i]);
        }
        delete(matrix);
        //delete(fs);
        //delete(aps);
        //delete(poids);

        n=4;m=4;
        g = new arete[4];
        //1
        a.s = 1;
        a.t = 2;
        a.cout = 1;
        g[0] = a;
        //2
        a.s = 1;
        a.t = 3;
        a.cout = 2;
        g[1] = a;
        //3
        a.s = 1;
        a.t = 4;
        a.cout = 3;
        g[2] = a;
        //4
        a.s = 2;
        a.t = 3;
        a.cout = 1;
        g[3] = a;

        algo.aretes2matrix(g,matrix,n,m);
        cout<<"****Test aretes2matrix****"<<endl;
        cout<<"Matrix:"<<endl;
        for(int i=1;i<=n;i++){
            cout<<"| ";
            for(int j=1;j<=n;j++){
                switch(matrix[i][j]){
                    case INT_MAX:
                        cout<<"m ";
                        break;
                    default:
                        cout<<matrix[i][j]<<" ";
                        break;
                }
            }
            cout<<"|"<<endl;
        }

        algo.matrix2aretes(matrix,g,n,m);
        cout<<"****Test matrix2arete****"<<endl;
        for(int i=0;i<m;i++){
            cout<<"["<<g[i].s<<","<<g[i].t<<","<<g[i].cout<<"]"<<endl;
        }
        delete(g);
}

