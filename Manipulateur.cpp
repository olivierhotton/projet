#include "Manipulateur.h"
#include <vector>
using namespace gpx_ns;
using namespace geojson_ns;
using namespace algo_ns;
using namespace manip_ns;
using namespace std;

Manipulateur::Manipulateur(Graphe* g, GeoJson* gj):monGraphe(g),monGeoJson(gj){}
//Manipulateur::Manipulateur():monGraphe(nullptr){}

/*
 * @function rÃ©cupÃ©rer champ gpx
 * */
std::string Manipulateur::recupererChampGPX(std::string& ligne,const std::string& tag){
    unsigned int pos;
    std::string champ;

    if( (pos = ligne.find(tag )) != std::string::npos ){
        champ = tag;

        //nettoyage de la balise pour rÃ©cupÃ©rer le champ
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
 * @param str chaÃ®ne de caractÃ¨res reprÃ©sentant le chemin d'accÃ¨s au fichier GPX
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
                seg.ajouterPoint(p);

            }
            //fin trkseg
            if ( ligne.find("</trkseg>") != std::string::npos)
            {
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




void Manipulateur::renumeroterLieux(){
    int n = monGraphe->noeuds().size();
    for(int i=0;i< n;i++)
        monGraphe->getNoeud(i)->set_id(i+1);
}


int Manipulateur::indicePosition(int g, int d, Noeud *n)
{

    if (g == d)
        if(
                n->get_lattitude() == monGraphe->getNoeud(g)->get_lattitude() &&
                n->get_longitude() == monGraphe->getNoeud(g)->get_longitude()
                )
        {
            return g;
        }
        else {
            return -1;
        }
    else
    {
        int m = (g+d)/2;
        if (n->get_lattitude() < monGraphe->getNoeud(m)->get_lattitude())

            return indicePosition(g,m,n);
        else
            if(n->get_lattitude() == monGraphe->getNoeud(m)->get_lattitude())
            {  if(n->get_longitude() < monGraphe->getNoeud(m)->get_longitude())
                    return indicePosition(g,m,n);
                else
                    return indicePosition(m+1,d,n);
            }
            else
                return indicePosition(m+1,d,n);
    }
}



void Manipulateur::updateGeoJSON(){

        std::cout << "-------------------------------------  : "<<endl;
        std::cout << "taille de graphe->noeuds : "<<monGraphe->noeuds().size()<<std::endl;
        std::cout << "taille de aretes  : "<< monGraphe->aretes().size()<< std::endl;


    MultiLineString mls = MultiLineString();
    FeatureCollection fc = FeatureCollection();
    Feature f = Feature();
    Position p;

    int i,j;
    //debut recuperer les aretes


    /* ajouter chaque arete */
    for(auto u : monGraphe->aretes()) //pour chaque arete
    {

        LineString l= LineString();

        i=u->getNoeud1()->get_id();
         j=u->getNoeud2()->get_id();

        //ne pas tracer les doubles orientations i->j et j->i
        if(i <= j)
        {

            p=Position(u->getNoeud1()->get_lattitude(),u->getNoeud1()->get_longitude(),u->getNoeud1()->get_altitude());
            l.addPosition(p);
            //std::cout <<i<< " vers ";
            p=Position(u->getNoeud2()->get_lattitude(),u->getNoeud2()->get_longitude(),u->getNoeud2()->get_altitude());
            l.addPosition(p);
           // std::cout << j << std::endl;

            mls.addLineString(l);
        }


    }
    std::cout << std::endl;
//    afficheAdj();
    /* ajouter tous les points sur un meme segment */
    //for(auto u : monGraphe->noeuds()) //pour chaque arete
    //{

    //LineString l= LineString();

    ////ne pas tracer les doubles orientations i->j et j->i
    ////if((i=u->get_id()) < (j=u->get_id()))
    //{

    // p=Position(u->get_lattitude(),u->get_longitude(),u->get_altitude());
    //l.addPosition(p);/*
    //std::cout <<i<< " vers ";
    // p=Position(u->get_lattitude(),u->get_longitude(),u->get_altitude());
    //l.addPosition(p);
    //std::cout << j << std::endl;*/

    // mls.addLineString(l);
    //}
    //}

    f.setMember(&mls);
    fc.addFeature(&f);

    std::cout <<  monGraphe->aretes().size()<< std::endl;

    if (monGeoJson != nullptr) delete monGeoJson;
    monGeoJson = new GeoJson(&fc);
    // std::cout << *monGeoJson ;

    createFile("C:/gpx/test_conversion.geojson",*monGeoJson);


}


void Manipulateur::afficheAdj()const{
    int nb = M_adj[0][0];
    // std::cout << M_adj[0][0] <<"\n";

    for(int i=0;i<=nb;i++){
        if (i<2)
            std::cout << "[" << M_adj[0][i]<<"] ";
        else
        {
            std::cout << "[0] ";
        }


    }

    std::cout << std::endl;

    for(int i=1;i<=nb;i++){
        for(int j=0;j<=nb;j++){
            if (M_adj[i][j] == 1)
                std::cout << "[1] ";
            else
            {
                std::cout << "[0] ";
            }
        }

        std::cout << std::endl;
    }
}

/*
 * Trier vecteur de noeud*
 *
 * */

void Manipulateur::trier(std::vector<Noeud *> &tmp){
    Noeud* aux;
    for(unsigned int i=0;i<(tmp.size()-1);i++){
        for(unsigned int j=i;j<tmp.size();j++){
            if(tmp[i]->get_lattitude()>tmp[j]->get_lattitude()){
                aux = tmp[i];
                tmp[i] = tmp[j];
                tmp[j] = aux;
            }
            else{
                if(tmp[i]->get_lattitude()==tmp[j]->get_lattitude()){
                    if(tmp[i]->get_longitude()>tmp[j]->get_longitude()){
                        aux = tmp[i];
                        tmp[i] = tmp[j];
                        tmp[j] = aux;
                    }
                }
            }
        }
    }
}

/*
 * Creer graphe a partir d'un objet gpx
 *
 * */

void Manipulateur::creerGraphe(const Gpx& g){

    //    std::cout << "-------------------------------------  : "<<endl;
    //    std::cout << "taille de graphe->noeuds : "<<monGraphe->noeuds().size()<<std::endl;
    //    std::cout << "taille de aretes  : "<< monGraphe->aretes().size()<< std::endl;

    std::vector<Noeud*> lieux, tmp,tmp2;
    //ok fait lors de la lecture du gpx
    //debut recuperer les sommets et les ajouter dans le vecteur de noeuds temporaire non trié avec doublons
    for (auto t : g.tracks())
    {
        for(auto u : t.segments())
        {
            for(auto x : u.points())
            {
                tmp.push_back(new Lieu(0,x.lattitude(),x.longitude(),x.altitude()));
            }
        }
    }


    //    for(unsigned int i=0;i<tmp.size();i++){
    //        cout<<"["<<tmp[i]->get_lattitude()<<","<<tmp[i]->get_longitude()<<","<<tmp[i]->get_altitude()<<"]"<<endl;
    //    }

    //trier les noeuds par ordre croissant

    trier(tmp);
    //    cout<<"Apres avoir trie"<<endl;

    //suppression des doublons
    lieux.push_back(tmp[0]);
    int k=0;
    // cout<<"["<<tmp[0]->get_lattitude()<<","<<tmp[0]->get_longitude()<<","<<tmp[0]->get_altitude()<<"]"<<endl;
    for(unsigned int i=1;i<tmp.size();i++){
        //   cout<<"["<<tmp[i]->get_lattitude()<<","<<tmp[i]->get_longitude()<<","<<tmp[i]->get_altitude()<<"]"<<endl;
        if(tmp[i]->get_lattitude()!=lieux[k]->get_lattitude()&&tmp[i]->get_longitude()!=lieux[k]->get_longitude()){
            lieux.push_back(tmp[i]);
            k++;
        }

    }
    //    cout<<"Apres avoir enleve doublons"<<endl;
    //    for(unsigned int i=0;i<lieux.size();i++){
    //        cout<<"["<<lieux[i]->get_lattitude()<<","<<lieux[i]->get_longitude()<<","<<lieux[i]->get_altitude()<<"]"<<endl;
    //    }

    //copier le vecteur lieux dans le vecteur de noeuds du graphe
    monGraphe->setNoeuds(lieux);


    //on renumerote les lieux du vecteur lieux

    renumeroterLieux();

    //fin renumeroter
    //fin recuperer les sommets




    //initialiser la matrice adj
    initMadj();

    //debut recuperer les aretes
    for (auto t : g.tracks())
    {

        for(auto u : t.segments())
        {
            //le vecteur tmp2 correspond a un segment
            for(auto x : u.points())
                tmp2.push_back(new Lieu(0,x.lattitude(),x.longitude(),x.altitude()));
            // cout << Lieu(0,x.lattitude(),x.longitude(),x.altitude()) <<"\n";
            //parcourir tmp2
            //recherche dichotomique pour trouver indice des 2 sommets de chaque arete dans le vector lieux
            int d=tmp2.size()-1;
            Noeud* n1;
            Noeud* n2;

            if (d>0){
                for (int k=1;k<= d;k++){
                    n1=tmp2[k-1];
                    n2=tmp2[k];

                    int i=indicePosition(0,monGraphe->noeuds().size()-1,n1);

                    int j=indicePosition(0,monGraphe->noeuds().size()-1,n2);

                    if(i==j)cout <<"i==j" <<i << ","<<j<<std::endl;

                    //Avec 2 indices : A[i][j] = 1;
                    updateMadj(i+1,j+1); //decalage
                    updateMadj(j+1,i+1); //non orienté stockage des deux arcs orientés
                }
            }



            //vider tmp2
            while(!tmp2.empty()){
                delete tmp2.back();
                tmp2.pop_back();
            }
            tmp2.clear();
        }
    }
    //libérer la mémoire => vider les vecteurs tmp et lieux sans supprimer les objets pointés
    while(!tmp.empty()){
        tmp.pop_back();
    }
    tmp.clear();
    while(!lieux.empty()){
        lieux.pop_back();
    }
    lieux.clear();


    //creer aretes
    int nb = monGraphe->noeuds().size();
    for(int i=1;i<=nb;i++){
        for(int j=1;j<=nb;j++){
            if (M_adj[i][j] == 1 && i!=j)

                monGraphe->addArete(new Arete(monGraphe->aretes().size()+1,monGraphe->getNoeud(i-1),monGraphe->getNoeud(j-1)));

        }
    }




    //    std::cout << "-------------------------------------  : "<<endl;
    //    std::cout << "taille de graphe->noeuds : "<<monGraphe->noeuds().size()<<std::endl;
    //    std::cout << "taille de aretes  : "<< monGraphe->aretes().size()<< std::endl;
    //    std::cout << "taille de lieux   : "<< lieux.size()<< std::endl;
    //    std::cout << "taille de tmp   : "<< tmp.size()<< std::endl;
    //    std::cout << "taille de tmp2   : "<< tmp2.size()<< std::endl;
    //    std::cout << "-------------------------------------  : "<<endl;

    //    k=0;
    //    for (auto t : monGraphe->noeuds())
    //    std::cout << k++ <<*t<<std::endl;

    //    for (auto t : monGraphe->aretes())
    //    std::cout <<*t<<std::endl;
    //        std::cout << t->getNoeud1()->get_id() << " : " << t->getNoeud2()->get_id() <<std::endl;
    //   std::cout << t->getNoeud1() << " : " << t->getNoeud2()<<std::endl;
   // afficheAdj();

}


/*
 * Ajouter lieu dans le vecteur de lieu
 * */


void Manipulateur::ajouterLieu(int i, double lattitude, double longitude, double altitude, const std::string& nom){

    //ajouter un nouveau lieu dans le vecteur de pointeurs
    monGraphe->noeuds().push_back(new Lieu(i,lattitude,longitude,altitude,nom));


}


void Manipulateur::updateMadj(const int i, const int j){ M_adj[i][j] = 1; M_adj[0][1]++; }

void Manipulateur::initMadj(){
    //recuperer le nombre de noeuds contenus dans le graphe
    int n = monGraphe->noeuds().size();
    //allocation mÃ©moire de la matrice adj
    M_adj = new int*[n+1] ;

    for( int i = 0 ; i < n+1 ; i++ )
    {
        M_adj[i] = new int[n+1];

        //initialisation
        for( int j = 1 ; j < n+1 ; j++ )
        {
            M_adj[i][j] = (i == j)?1:0;
        }
    }
    M_adj[0][0]=n;
    M_adj[0][1]=0;
}

void Manipulateur::updateArete(){

    while( ! monGraphe->aretes().empty())
    {
        delete monGraphe->aretes().back();
        monGraphe->aretes().pop_back();
    }
    monGraphe->aretes().clear();

    int n =M_adj[0][0];

    for(int i=1;i<=n;i++){
        for(int j=1;i<=n;i++){

            if(M_adj[i][j]==1)
            {
                monGraphe->addArete(new Arete(monGraphe->aretes().size()+1,monGraphe->getNoeud(i),monGraphe->getNoeud(j)));
            }
        }
    }

}

void Manipulateur::testGraphe()
{
    //    Graphe gr = Graphe();
}
void Manipulateur::testGPX(){	

}




void Manipulateur::testGeoJSON(){

    Gpx g = Manipulateur::lireGPX("c:/gpx/test.gpx");
    Manipulateur m;
    m.creerGraphe(g);
    m.updateGeoJSON();
}


void Manipulateur::testAlgo(){
    /*
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


    vector<arete> va;
    int index = 5;
    algo.supprime_sommet(fs,aps,index,va);
    cout<<"****Test suppression d'un sommet****"<<endl;
    for(int i=0;i<va.size();i++){
        cout<<va[i].s<<" -> "<<va[i].t<<endl;
    }
    cout<<endl;

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

    int *poids,**matrix; // *aps, *fs,n,m
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
    delete(g);*/
}

void Manipulateur::supprime_sommet(int *fs,int *aps,int index,vector<algo_ns::arete> &g){
    int n = aps[0];
    int l,t;
    arete elem;
    for(int i=1;i<index;i++){
        l = aps[i];
        while((t=fs[l])!=0){
            if(t!=index){
                elem.s = i;
                elem.t = t;
                g.push_back(elem);
            }
            l++;
        }
    }
    for(int i=index+1;i<=n;i++){
        l = aps[i];
        while((t=fs[l])!=0){
            if(t!=index){
                elem.s = i;
                elem.t = t;
                g.push_back(elem);
            }
            l++;
        }
    }

}

/*
 * Controle
 * */
int Manipulateur::det_structure(){
    if(aps)
        //les fs,aps,poids sont utilisé
        return 1;
    if(M_adj)
        //la matrice d'ajacence est utilisée
        return 2;
    if(g)
        //la liste des aretes est utilisée
        return 3;
    //la liste principale et la liste secondaire sont utilisées
    return 4;
}

void Manipulateur::choisir_structure(int i){
    Algorithme algo;
    int courant = det_structure();
    if(courant == 3){
        int **a,*fs_tmp,*aps_tmp,*poids_tmp;
        algo.aretes2matrix(g,a,n,m);
        switch(i){
        case 1:
            algo.matrix2all(a,fs,aps,poids);
            algo.del_matrice(a);
            delete [] g;
            break;
        case 2:
            M_adj = a;
            delete [] g;
            break;
        case 4:
            algo.matrix2all(a,fs_tmp,aps_tmp,poids_tmp);
            algo.del_matrice(a);
            algo.all2lists(fs_tmp,aps_tmp,poids_tmp,pri);
            algo.del_fs_aps_poids(fs_tmp,aps_tmp,poids_tmp);
            delete [] g;
            break;
        default:
            cout<<"ERREUR : Structure indéterminée"<<endl;
            break;
        }
    }
    else{
        if(courant == 1){
            if(i == 4){
                algo.all2lists(fs,aps,poids,pri);
                algo.del_fs_aps_poids(fs,aps,poids);
            }
            else{
                int **a;
                algo.all2matrix(fs,aps,poids,a);
                switch(i){
                case 2:
                    M_adj = a;
                    algo.del_fs_aps_poids(fs,aps,poids);
                    break;
                case 3:
                    if(algo.estSymetrique(a)){
                        algo.matrix2aretes(a,g,n,m);
                        algo.del_fs_aps_poids(fs,aps,poids);
                    }
                    else{
                        cout<<"ERREUR : Impossible de passer de la structure du graphe orienté vers celle du non orienté"<<endl;
                    }
                    algo.del_matrice(a);
                    break;
                default:
                    cout<<"ERREUR : Structure indéterminée"<<endl;
                    break;
                }
            }
        }
        else{
            if(courant == 2){
                if(i == 4){
                    int *fs_tmp,*aps_tmp,*poids_tmp;
                    algo.matrix2all(M_adj,fs_tmp,aps_tmp,poids_tmp);
                    algo.del_matrice(M_adj);
                    algo.all2lists(fs_tmp,aps_tmp,poids_tmp,pri);
                    algo.del_fs_aps_poids(fs_tmp,aps_tmp,poids_tmp);
                }
                else{
                    switch(i){
                    case 1:
                        algo.matrix2all(M_adj,fs,aps,poids);
                        algo.del_matrice(M_adj);
                        break;
                    case 3:
                        if(algo.estSymetrique(M_adj)){
                            algo.matrix2aretes(M_adj,g,n,m);
                            algo.del_matrice(M_adj);
                        }
                        else{
                            cout<<"ERREUR : Impossible de passer de la structure du graphe orienté vers celle du non orienté"<<endl;
                        }
                        break;
                    default:
                        cout<<"ERREUR : Structure indéterminée"<<endl;
                    }
                }
            }
            else{
                if(courant == 4){
                    int **a,*fs_tmp,*aps_tmp;
                    algo.lists2all(pri,fs_tmp,aps_tmp,poids);
                    switch(i){
                    case 1:
                        fs = fs_tmp;
                        aps = aps_tmp;
                        algo.del_lists(pri);
                        break;
                    case 2:
                        algo.all2matrix(fs_tmp,aps_tmp,poids,M_adj);
                        algo.del_fs_aps_poids(fs_tmp,aps_tmp,poids);
                        algo.del_lists(pri);
                        break;
                    case 3:
                        algo.all2matrix(fs_tmp,aps_tmp,poids,a);
                        algo.del_fs_aps_poids(fs_tmp,aps_tmp,poids);
                        if(algo.estSymetrique(a)){
                            algo.matrix2aretes(a,g,n,m);
                            algo.del_lists(pri);
                        }
                        else{
                            cout<<"ERREUR : Impossible de passer de la structure du graphe orienté vers celle du non orienté"<<endl;
                        }
                        algo.del_matrice(a);
                        break;
                    default:
                        cout<<"ERREUR : Structure indéterminée"<<endl;
                        break;
                    }
                }
                else{
                    cout<<"ERREUR!"<<endl;
                }
            }
        }
    }
}

void Manipulateur::afficher_structure(){
    int courant = det_structure();
    Algorithme algo;
    switch(courant){
    case 1:
        algo.affiche_fs_aps_poids(fs,aps,poids);
        break;
    case 2:
        algo.affiche_matrice(M_adj);
        break;
    case 3:
        algo.affiche_aretes(g,n,m);
        break;
    case 4:
        algo.affiche_lists(pri);
        break;
    default:
        cout<<"ERREUR!"<<endl;
        break;
    }
}
