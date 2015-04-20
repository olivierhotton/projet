#include "Manipulateur.h"
#include <vector>
#include <math.h>
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
        if (n->get_lattitude() <= monGraphe->getNoeud(m)->get_lattitude())

            return indicePosition(g,m,n);
        else
            //            if(n->get_lattitude() == monGraphe->getNoeud(m)->get_lattitude())
            //            {  if(n->get_longitude() < monGraphe->getNoeud(m)->get_longitude())
            //                    return indicePosition(g,m,n);
            //                else
            //                    return indicePosition(m+1,d,n);
            //            }
            //            else
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
            else
                M_adj[i][j] = INT_MAX;

        }
    }

    Algorithme algo;
    algo.matrix2all(M_adj,fs,aps,poids);
    algo.del_matrice(M_adj);




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
    structure=1;
    afficher_structure();

}


/*
 * Ajouter lieu dans le vecteur de lieu
 * */


void Manipulateur::ajouterLieu(int i, double lattitude, double longitude, double altitude, const std::string& nom){

    //ajouter un nouveau lieu dans le vecteur de pointeurs
    monGraphe->noeuds().push_back(new Lieu(i,lattitude,longitude,altitude,nom));


}

void Manipulateur::saisirArete(){

    int pred,succ;
    std::cout<<"---------------------------------------------------"<<std::endl;
    std::cout<<"Ajout d\'une arete \n";
    std::cout<<"---------------------------------------------------"<<std::endl;


    //changer de structure pour pred et successeurs = choix 1
    if (det_structure() != 1) choisir_structure(1);

    //choisir le predecesseur
    std::cout<<std::endl << "Saisir le predecesseur";
    std::cout << "[ 1" <<" - "<< monGraphe->noeuds().size() << "] : " << std::endl;
    std::cin >> pred;


    //choisir le sucesseur
    std::cout<<std::endl << "Saisir le sucesseur";
    std::cout << "[ 1" <<" - "<< monGraphe->noeuds().size() << "] : "<<std::endl;
    std::cin >> succ;

    //push arete - les noeuds sont deja tries
    int l = aps[pred];
    while(fs[l]!=0){
        if(fs[l]==succ)
            monGraphe->addArete(new Arete(monGraphe->aretes().size()+1,monGraphe->getNoeud(pred-1),monGraphe->getNoeud(succ-1)));
        break;
    }

    //mettre a jour fs aps
    Algorithme algo;
    algo.all2matrix(fs,aps,poids,M_adj);
    updateMadj(pred,succ);
    algo.del_fs_aps_poids(fs,aps,poids);
    algo.matrix2all(M_adj,fs,aps,poids);
    algo.del_matrice(M_adj);
}

void Manipulateur::saisirLieu(){

    double lattitude,longitude,altitude;
    int num=monGraphe->noeuds().size()+1;
    std::string nom;
    std::cout<<"---------------------------------------------------"<<std::endl;
    std::cout<<"Ajout d\'un sommet\n";
    std::cout<<"---------------------------------------------------"<<std::endl;

    std::cout<<std::endl << "Saisir la lattitude : "<<std::endl;
    std::cin >> lattitude;

    std::cout<<std::endl << "Saisir la longitude : "<<std::endl;
    std::cin >> lattitude;

    std::cout<<std::endl << "Saisir l\'altitude : "<<std::endl;
    std::cin >> altitude;


    std::cout<<std::endl << "Saisir le nom : "<<std::endl;
    std::cin >> nom;

    //ajouter le sommet dans le vecteur de noeuds
    monGraphe->addNoeud(new Lieu(num,lattitude,longitude,altitude,nom));
    //incrementer le nombre de sommets de la structure
    //    int* fs_tmp= fs;int* aps_tmp=aps;int* poids_tmp=poids;
    int m=fs[0];
    int n=aps[0];
    int* fs_tmp = new int[m+1];
    int* aps_tmp = new int[n+1];
    int* poids_tmp = new int[m+1];

    for(int i=1;i<=m;i++) fs_tmp[i]=fs[i];
    for(int i=1;i<=n;i++) aps_tmp[i]=aps[i];
    for(int i=1;i<=m;i++) poids_tmp[i]=poids[i];


    n++;

    m++;
    Algorithme algo;
    algo.del_fs_aps_poids(fs,aps,poids);
    fs=new int[m+1];
    aps=new int[n+1];
    poids=new int[m+1];
    fs[0]=m;
    aps[0]=n;
    for(int i=1;i<m;i++)
    {
        std::cout << fs_tmp[i] << " : " << poids_tmp[i]<<std::endl;
        fs[i]=fs_tmp[i];
        poids[i]=poids_tmp[i];
    }
    fs[m]=0;
    poids[0]=m;
    poids[m]=INT_MAX;
    for(int j=1;j<n;j++){aps[j]=aps_tmp[j];}
    aps[n]=m;
    algo.del_fs_aps_poids(fs_tmp,aps_tmp,poids_tmp);

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

void Manipulateur::initPoids(){
    int l,t,poid;
    int n = aps[0];
    for(int i=1;i<=n;i++){
        l = aps[i];
        while((t=fs[l])!=0){
            cout <<std::endl << monGraphe->getNoeud(i-1)->get_altitude();
            poid = (monGraphe->getNoeud(i-1)->get_altitude()- monGraphe->getNoeud(t-1)->get_altitude());
            poids[l] = poid;
            l++;
        }
    }
}

void Manipulateur::initPoids2(){
    int l,t,poid;
    long c;
    int n = aps[0];
    for(int i=1;i<=n;i++){
        l = aps[i];
        while((t=fs[l])!=0){
            c = (monGraphe->getNoeud(i-1)->get_lattitude()- monGraphe->getNoeud(t-1)->get_lattitude())*10000*(monGraphe->getNoeud(i-1)->get_lattitude()- monGraphe->getNoeud(t-1)->get_lattitude())*10000;
            c += (monGraphe->getNoeud(i-1)->get_longitude()- monGraphe->getNoeud(t-1)->get_longitude())*10000*(monGraphe->getNoeud(i-1)->get_longitude()- monGraphe->getNoeud(t-1)->get_longitude())*10000;
            poid = sqrt(c);
            poids[l] = poid;
            l++;
        }
    }
}

void Manipulateur::testGraphe()
{
    //    Graphe gr = Graphe();
}
void Manipulateur::testGPX(){	

}






void Manipulateur::testAlgo(){
    Gpx gpx =lireGPX("C:\gpx\test.gpx");
    creerGraphe(gpx);
    updateGeoJSON();
    // saisirLieu();
    //  saisirArete();

    //afficher_structure();
    Algorithme algo;
    //choisir_structure(2);
    afficher_structure();
    initPoids();
    //initPoids2();
    //    int* t;
    //    algo.prufer(g,n,t);
    //    afficher_structure();
    //    for (int i=0;i<n-1;i++)
    //    {
    //        std::cout << t[i] << ",";
    //    }

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
    //    if(aps)
    //        //les fs,aps,poids sont utilisé
    //        return 1;
    //    if(M_adj)
    //        //la matrice d'ajacence est utilisée
    //        return 2;
    //    if(g)
    //        //la liste des aretes est utilisée
    //        return 3;
    //    //la liste principale et la liste secondaire sont utilisées
    //    return 4;
    return structure;
}

void Manipulateur::choisir_structure(int i){
    Algorithme algo;
    int courant = det_structure();
    if(courant == 3){
        int **a,*fs_tmp,*aps_tmp,*poids_tmp;
        algo.aretes2matrix(g,a,n,m);
        switch(i){
        case 1:
            structure=1;
            algo.matrix2all(a,fs,aps,poids);
            algo.del_matrice(a);
            delete [] g;
            break;
        case 2:
            structure=2;
            M_adj = a;
            delete [] g;
            break;
        case 4:
            structure=4;
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
                structure=4;
                algo.all2lists(fs,aps,poids,pri);
                algo.del_fs_aps_poids(fs,aps,poids);
            }
            else{
                int **a;
                algo.all2matrix(fs,aps,poids,a);
                switch(i){
                case 2:
                    structure=2;
                    M_adj = a;
                    //                    for(int i=0;i<=a[0][0];i++){
                    //                        for(int j=0;j<=a[0][0];j++){


                    //                        }

                    //                    }
                    //algo.all2matrix(fs,aps,poids,M_adj);
                    // cout << "ok "<<M_adj[0][0]<<std::endl;

                    algo.del_fs_aps_poids(fs,aps,poids);
                    break;
                case 3:
                    structure=3;
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
                    structure=4;
                    int *fs_tmp,*aps_tmp,*poids_tmp;
                    algo.matrix2all(M_adj,fs_tmp,aps_tmp,poids_tmp);
                    algo.del_matrice(M_adj);
                    algo.all2lists(fs_tmp,aps_tmp,poids_tmp,pri);
                    algo.del_fs_aps_poids(fs_tmp,aps_tmp,poids_tmp);
                }
                else{
                    switch(i){
                    case 1:
                        structure=1;
                        algo.matrix2all(M_adj,fs,aps,poids);
                        algo.del_matrice(M_adj);
                        break;
                    case 3:
                        if(algo.estSymetrique(M_adj)){
                            structure=3;
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
                        structure=1;
                        fs = fs_tmp;
                        aps = aps_tmp;
                        algo.del_lists(pri);
                        break;
                    case 2:
                        structure=2;
                        algo.all2matrix(fs_tmp,aps_tmp,poids,M_adj);
                        algo.del_fs_aps_poids(fs_tmp,aps_tmp,poids);
                        algo.del_lists(pri);
                        break;
                    case 3:

                        algo.all2matrix(fs_tmp,aps_tmp,poids,a);
                        algo.del_fs_aps_poids(fs_tmp,aps_tmp,poids);
                        if(algo.estSymetrique(a)){
                            structure=3;
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
    //cout << "\n courant:" <<courant << std::endl;
    switch(courant){
    case 1:
        algo.affiche_fs_aps_poids(fs,aps,poids);
        break;
    case 2:
        //        cout << M_adj[0][0];
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

void Manipulateur::run(){

    std::string fichier;

    cout<<"Entrer un chemin complet vers le fichier GPX contenant le graphe \n[taper D pour accepter la valeur par defaut: C:/gpx/test.gpx]: "<<endl;
    cin>>fichier;
    if(fichier == "D")
    {
        fichier="C:/gpx/test.gpx";
    }
    cout << std::endl;
    Gpx gpx =lireGPX(fichier);
    creerGraphe(gpx);
    updateGeoJSON();



    //afficher_structure();
    Algorithme algo;
    //choisir_structure(2);
    afficher_structure();
    //cout << "\nok";
    //    initPoids();
    // cout << "\nok";
    //initPoids2();
    int choix=1,choix2;
    while(choix!=0){
        cout<<"Votre choix : "<<endl<<"[0] Terminer"<<endl<<"[1] Afficher la structure du graphe";
        cout<<endl<<"[2] Changer la structure du graphe"<<endl;
        cout<<"[3] Ajouter un sommet"<<endl<<"[4] Ajouter un arc"<<endl;
        cout<<"[5] Initialiser les poids"<<endl;
        cout<<"[6] Algorithme"<<endl;
        cin>>choix;
        if(choix!=6){
            switch(choix){
            case 0:
                return;
            case 1:
                afficher_structure();
                break;
            case 2:
                cout<<"Structure : [1] fs aps poids  [2] Matrice d'adjacent  [3] Liste d'aretes  [4] Liste principale et liste secondaire"<<endl;
                cout<<"Votre choix : ";
                cin>>choix2;
                choisir_structure(choix2);
                break;
            case 3:
                saisirLieu();
                break;
            case 4:
                saisirArete();
                break;
            case 5:
                cout<<"Structure : [1] Pente  [2] Distance"<<endl;
                cout<<"Votre choix : ";
                cin>>choix2;
                choisir_structure(1);
                if(choix2 == 1)
                    initPoids();
                else
                    if(choix2 == 2)
                        initPoids2();
                    else
                        cout<<"1 ou 2"<<endl;
                break;
            default:
                cout<<"Entre 1 et 6"<<endl;
                break;
            }
        }
        else{
            cout<<"Votre choix : "<<endl<<"[0] Dijkstra"<<endl<<"[1] Belleman";
            cout<<endl<<"[2] Dantzig"<<endl;
            cout<<"[3] Kruskal"<<endl<<"[4] Prim"<<endl;
            cout<<"[5] Prufer"<<endl;
            cout<<"[6] Rang"<<endl;
            cout<<"[7] Distances"<<endl;
            cout<<"Votre choix : ";
            cin>>choix2;
            if(choix2<0||choix2>7){
                cout<<"Entre 0 et 7"<<endl;
            }
            else{
                if(choix2 == 0){
                    if(det_structure()!=1) choisir_structure(1);
                    int *pred,*d,s;
                    cout<<"Sommet initial : ";
                    cin>>s;
                    algo.dijkstra(fs,aps,poids,s,pred,d);
                    int n = pred[0];
                    cout<<"Pred : ["<<pred[0];
                    for(int i=1;i<=n;i++){
                        cout<<","<<pred[i];
                    }
                    cout<<"]"<<endl;
                    cout<<"d : ["<<d[0];
                    for(int i=1;i<=n;i++){
                        cout<<","<<d[i];
                    }
                    cout<<"]"<<endl;
                    algo.del_fs_aps(pred,d);
                }
                else{
                    if(choix2 == 1){
                        if(det_structure()!=1)choisir_structure(1);
                        int *pred,*d,s;
                        cout<<"Sommet initial : ";
                        cin>>s;
                        algo.bellman(fs,aps,poids,s,pred,d);
                        int n = pred[0];
                        cout<<"Pred : ["<<pred[0];
                        for(int i=1;i<=n;i++){
                            cout<<","<<pred[i];
                        }
                        cout<<"]"<<endl;
                        cout<<"d : ["<<d[0];
                        for(int i=1;i<=n;i++){
                            cout<<","<<d[i];
                        }
                        cout<<"]"<<endl;
                        algo.del_fs_aps(pred,d);
                    }
                    else{
                        if(choix2 == 2){
                            if(det_structure()!=2)choisir_structure(2);
                            int **matrice_res;
                            algo.dantzig(M_adj,matrice_res);
                            cout<<"Matrice des couts"<<endl;
                            algo.affiche_matrice(M_adj);
                            cout<<"Matrice des couts des plus cours chemins"<<endl;
                            algo.affiche_matrice(matrice_res);
                            algo.del_matrice(matrice_res);
                        }
                        else{
                            if(choix2 == 3){
                                if(det_structure()!=3)choisir_structure(3);
                                if(!g){
                                    cout<<"Impossible! Kruskal ne marche pas avec un graphe oriente"<<endl;
                                }
                                else{
                                    arete *t;
                                    algo.kruskal(g,n,t);
                                    cout<<"Les aretes : "<<endl;
                                    algo.affiche_aretes(g,n,m);
                                    cout<<"L'ARM : "<<endl;
                                    algo.affiche_aretes(t,n,n-1);
                                    algo.del_aretes(t);
                                }

                            }
                            else{
                                if(choix2 == 4){
                                    if(det_structure()!=3)choisir_structure(3);
                                    if(!g){
                                        cout<<"Impossible! Prim ne marche pas avec un graphe oriente"<<endl;
                                    }
                                    else{
                                        arete *t;
                                        int s;
                                        cout<<"Sommet initial : ";
                                        cin>>s;
                                        algo.prim(g,n,m,s,t);
                                        cout<<"Les aretes : "<<endl;
                                        algo.affiche_aretes(g,n,m);
                                        cout<<"L'ARM : "<<endl;
                                        algo.affiche_aretes(t,n,n-1);
                                        algo.del_aretes(t);
                                    }
                                }
                                else{
                                    if(choix2 == 5){
                                        if(det_structure()!=3)choisir_structure(3);
                                        if(!g){
                                            cout<<"Impossible! Prufer ne marche pas avec un graphe oriente"<<endl;
                                        }
                                        else{
                                            int *t;
                                            algo.prufer(g,n,t);
                                            cout<<"Les aretes : "<<endl;
                                            algo.affiche_aretes(g,n,m);
                                            cout<<"Le codage ["<<t[0];
                                            for(int i=1;i<(n-2);i++){
                                                cout<<","<<t[i];
                                            }
                                            cout<<"]"<<endl;
                                            delete [] t;
                                        }
                                    }
                                    else{
                                        if(choix2 == 6){
                                            if(det_structure()!=1) choisir_structure(1);
                                            int *rang;
                                            int n = aps[0];
                                            algo.det_rang(fs,aps,rang);
                                            cout<<"Rang ["<<rang[0];
                                            for(int i=1;i<=n;i++){
                                                cout<<","<<rang[i];
                                            }
                                            cout<<"]"<<endl;
                                            delete [] rang;
                                        }
                                        else{
                                            if(det_structure()!=1) choisir_structure(1);
                                            int s,*marque;
                                            cout<<"Sommet initial : ";
                                            cin>>s;
                                            algo.det_dist(fs,aps,s,marque);
                                            cout<<"Distance ["<<marque[0];
                                            for(int i=1;i<=n;i++){
                                                cout<<","<<marque[i];
                                            }
                                            cout<<"]"<<endl;
                                            delete [] marque;

                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}
