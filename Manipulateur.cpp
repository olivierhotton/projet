#include "Manipulateur.h"
using namespace gpx_ns;
using namespace geojson_ns;
using namespace algo_ns;
using namespace manip_ns;
using namespace std;

Manipulateur::Manipulateur(Graphe* g):monGraphe(g){}
//Manipulateur::Manipulateur():monGraphe(nullptr){}

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
 * @brief lit un fichier GPX et met a jour le vecteur d'arete
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

/* renvoit un vecteur de positions trié sans doublon
 *
 * */
std::vector<Position> Manipulateur::positionAsc(const GeoJson &gj){


    std::vector<Position> tmp;
    std::vector<Position> pos;
    int nb;


    tmp = gj.member()->positions();


    //on trie les points ordre croissant
    sort(tmp.begin(),tmp.end());


//    //on supprime les doublons


    for(int i=1;i<= (nb=tmp.size()-1);i++)
    {
        if(tmp[i-1] != tmp[i]) // inutile de garder les doublons
        {
            pos.push_back(tmp[i-1]);
        }
    }
    if(tmp[nb-1] != tmp[nb]) // dernier element
    {
        pos.push_back(tmp[nb]);
    }


    return pos;

}

/*
 * trier lieux
 * */

/* renvoit un vecteur de positions trié sans doublon
 *
 * */
void Manipulateur::trierLieux(){

    std::cout << "gr ->" << monGraphe->noeuds().size() << " noeuds avant le tri" << std::endl;
    std::vector<Lieu> tmp;

    std::vector<Noeud*> pos;


    int nb;



    for (unsigned int i=0; i< monGraphe->noeuds().size();i++){
        //tmp.push_back(monGraphe->getNoeud(i));
       tmp.push_back(Lieu(monGraphe->getNoeud(i)->get_id(),monGraphe->getNoeud(i)->get_lattitude(),monGraphe->getNoeud(i)->get_longitude(),monGraphe->getNoeud(i)->get_altitude(),""));

    }
    //vider le tableau de noeuds du graphe
    for (unsigned int i=0; i< monGraphe->noeuds().size();i++){
        delete monGraphe->getNoeud(i);

    }
    monGraphe->noeuds().clear();

    //on trie les lieux ordre croissant

    sort(tmp.begin(),tmp.end());
    for (auto f : tmp)  std::cout << f<< std::endl;

    //on supprime les doublons
    std::cout << "n = " << tmp.size()-1 << std::endl;
nb=tmp.size();

if(nb> 0){
monGraphe->addNoeud(new Lieu(0,tmp[0].get_lattitude(),tmp[0].get_longitude(),tmp[0].get_altitude(),tmp[0].get_nom()));

    for(int i=1;i< nb-1;i++)
    {
        if(tmp[i+1] != tmp[i]) // inutile de garder les doublons
        {
             std::cout << "tmp["<<i-1<<"] != tmp["<<i<<"] -> gr" << std::endl;
            monGraphe->addNoeud(new Lieu(0,tmp[i+1].get_lattitude(),tmp[i+1].get_longitude(),tmp[i+1].get_altitude(),tmp[i+1].get_nom()));
   //  std::cout << "gr->noeuds : " << monGraphe->noeuds().size() << std::endl;
        }
        else {
            std::cout << "tmp["<<i-1<<"] == tmp["<<i<<"] " << std::endl;
        }
    }
//    if(tmp[nb-1] != tmp[nb]) // dernier element
//    {
//        monGraphe->addNoeud(new Lieu(0,tmp[nb].get_lattitude(),tmp[nb].get_longitude(),tmp[nb].get_altitude(),tmp[nb].get_nom()));
////        monGraphe->addNoeud(new Lieu());

//    }
    std::vector<Noeud*> v =  monGraphe->noeuds();
   // for (auto f : v)  std::cout << *f<< std::endl;

//renumeroterLieux();
}
}


void Manipulateur::renumeroterLieux(){
    int n = monGraphe->noeuds().size();
for(int i=0;i< n;i++)
    monGraphe->getNoeud(i)->set_id(i+1);
}


int Manipulateur::indicePosition(const Position& pos, const std::vector<Position>& vpos)
{


   /*   déclaration des variables locales à la fonction */
     bool trouve;  //vaut faux tant que la valeur "val" n'aura pas été trouvée
     int id;  //indice de début
     int ifin;  //indice de fin
     int im;  //indice de "milieu"

     /* initialisation de ces variables avant la boucle de recherche */
     trouve = false;  //la valeur n'a pas encore été trouvée
     id = 0;  //intervalle de recherche compris entre 0...
     ifin = vpos.size();  //...et nbVal

     /* boucle de recherche */
     while(!trouve && ((ifin - id) > 1)){

       im = (id + ifin)/2;  //on détermine l'indice de milieu

       trouve = (vpos[im] == pos);  //on regarde si la valeur recherchée est à cet indice

       if( pos < vpos[im]) ifin = im;  //si la valeur qui est à la case "im" est supérieure à la valeur recherchée, l'indice de fin "ifin" << devient >> l'indice de milieu, ainsi l'intervalle de recherche est restreint lors du prochain tour de boucle
       else id = im;  //sinon l'indice de début << devient >> l'indice de milieu et l'intervalle est de la même façon restreint
     }

     /* test conditionnant la valeur que la fonction va renvoyer */
     if(vpos[id] == pos) return(id);  //si on a trouvé la bonne valeur, on retourne l'indice
     else return(-1);  //sinon on retourne -1

   }


/*
 * Changer pour return Geojson
 * */

void Manipulateur::toGeoJSON(const Gpx& g){

   // if (monGraphe != nullptr) std::cout << "coucou" <<std::endl;


    std::vector<Trk> tr;
    std::vector<TrkSeg> trs;
    std::vector<TrkPt> trp;

   // Position p;
    LineString l= LineString();
    MultiLineString mls = MultiLineString();
         FeatureCollection fc = FeatureCollection();
        Feature f = Feature();
    tr = g.tracks();


    //pour chaque track
    for (auto i: tr){
        //récupérer le nom de la track

        //récupérer les segments


        trs = i.segments();
        //récupérer un segment
        for (auto j: trs){
            //récupérer les points du segment
  //  std::cout << "Segment\n";
            trp = j.points();



            //récupérer un point du segment     g.getTrack(0).getSegment(0).getPoint(0)

            for (unsigned int k=0;k< trp.size();k++){
                l.addPosition(Position(trp[k].lattitude(),trp[k].longitude(),trp[k].altitude()));
                //creer un noeud et l'ajouter dans un vecteur de noeuds

//                monGraphe->addNoeud(new Lieu(k+1,trp[k].lattitude(),trp[k].longitude(),trp[k].altitude(),""));
                monGraphe->addNoeud(new Lieu(k+1,trp[k].lattitude(),trp[k].longitude(),trp[k].altitude(),""));

                //creer une arete et l'ajouter dans le vecteur d'arete
                if(k>0)
                {
                    monGraphe->addArete(new Arete(k+1,monGraphe->getNoeud(k-1),monGraphe->getNoeud(k)));
                }

            }
            //std::cout << l;
            mls.addLineString(l);

        }

        f.setMember(&mls);
       // std::cout << f;
      fc.addFeature(&f);
    }

      //GeoJson gj = GeoJson(&fc);
     // std::cout << gj;
    std::cout << monGraphe->noeuds().size() <<" noeuds\n";
    std::cout << monGraphe->aretes().size() <<" aretes \n";

    //trier les lieux par ordre croissant, supprimer les doublons et renumeroter
    trierLieux();

    //std::cout << "Apres le tri \n";
//    std::cout << monGraphe->noeuds().size() <<" noeuds\n";
//    std::cout << monGraphe->aretes().size() <<" aretes \n";
 /*
    //initialiser la matrice adj
    initMadj();
    //recuperer chaque arete du graphe
    for (auto t: monGraphe->aretes()){

    //mettre a jour la matrice adj
        updateMadj(t->getNoeud1()->get_id(),t->getNoeud2()->get_id());
    }






    createFile("C:/Users/oliv/Documents/L3_INFO/Projet_GA/test_conversion.geojson",gj);
    int nb = monGraphe->noeuds().size();
    for(int i=0;i<nb;i++){
        for(int j=0;j<nb;j++){
            if (M_adj[i][j] == 1)
                std::cout << "[1] ";
            else
                std::cout << "[0] ";

        }
        std::cout << std::endl;
    }
*/
}



/*
 * Creer lieux et renvoit un vecteur de pointeurs
 * */


void Manipulateur::creerLieux(const std::vector<Position> &vp){

    std::vector<Noeud*> vn;
    for(unsigned int i=0;i<vp.size(); i++)
    {
        std::string name = ""; // A CHANGER
//        Lieu l = new Lieu(i,vl[i].lattitude(),vl[i].longitude(),vl[i].elevation(),name);
       // std::cout <<l << std::endl;

        vn.push_back(new Lieu(i+1,vp[i].lattitude(),vp[i].longitude(),vp[i].elevation(),name));
    }

  monGraphe->setNoeuds(vn);
}





//id = numeros de sommets
void Manipulateur::updateMadj(const int id1, const int id2){ M_adj[id1][id2] = 1; }

void Manipulateur::initMadj(){
//recuperer le nombre de noeuds contenus dans le graphe
int n = monGraphe->noeuds().size();
//allocation mémoire de la matrice adj
*M_adj = new int[n+1] ;

for( int i = 0 ; i < n+1 ; i++ )
{
M_adj[i] = new int[n+1];

//initialisation
for( int j = 1 ; j < n+1 ; j++ )
{
M_adj[i+1][j] = INT_MAX;
}
}
}

void Manipulateur::testGraphe()
{
   /* Lieu l1 =  Lieu(1,50.45,7.33,280.0);
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

*/

       /* Graphe G1(tab_Aretes);
        cout << "affichage du graphe :" <<  endl ;
        cout << G1  <<  endl ;

        Lieu L1(1,3.4,2.2,1.2,"Lieu 1")  ;

        cout << "affichage du Lieu :" <<  endl ;
        cout << L1 <<  endl ;

        Portion* P1 = new Portion(1,&n1,&n2,2,3,7);

        cout << "affichage de la portion  :" <<  endl ;
        cout << *P1 ;
*/
    Graphe gr = Graphe();
}
void Manipulateur::testGPX(){

Gpx g=lireGPX("C:/Users/oliv/Documents/L3_INFO/Projet_GA/test.gpx");


}

// on suppose gj.member() != nullptr
/*
std::vector<Arete> &Manipulateur::aretes(const GJObject &gjo){
    std::vector<Arete> tmp;
    std::string name ;
  //  std::cout << type;


    //recuperer le vecteur de positions pour chaque element
      if ( (name =  gjo.name()).find("Collection") != std::string::npos) // c'est une collection
    {
          for (auto t : gjo.member()-> )
          {
              tmp.push_back();
          }

    std::cout << std::endl <<"c'est une collection !"<<std::endl;
    }
    else //ce n'est pas une collection
        std::cout<< std::endl<< "ce n'est pas une collection !"<<std::endl;

}*/




void Manipulateur::testGeoJSON(){

    Gpx g = Manipulateur::lireGPX("C:/Users/oliv/Downloads/gpx/test.gpx");
Manipulateur m;
  m.toGeoJSON(g);

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


