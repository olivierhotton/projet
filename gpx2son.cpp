
//#include "ManipFichier.h"

///**
// * @fn split
// * @brief split
// * @param s chaîne de caractères à diviser en sous-chaînes
// * @param c caractère séparateur de champ
// * @param v vecteur de chaines de caractères contenant les différents champs
// */

//void split(const std::string& s, char c,std::vector<std::string>& v)
//{
//    std::string::size_type i = 0;
//    std::string::size_type j = s.find(c);

//    while (j != std::string::npos) {
//        v.push_back(s.substr(i, j-i));
//        i = ++j;
//        j = s.find(c, j);

//        if (j ==std::string::npos)
//            v.push_back(s.substr(i, s.length()));
//    }
//}


///**
// * @fn lireFichier
// * @brief lit un fichier ligne par ligne
// * @param str chaîne de caractères représentant le chemin d'accès au fichier
// * @return vecteur d'étudiants contenant chaque entrée du fichier et également l'entête du fichier dont le champ Badge sera converti en entier
// */

//std::vector<etudiant> lireFichier(const std::string& str){

//    std::vector<etudiant> vect;
//    std::ifstream fs;
//    if(! fs.is_open() )
//    {
//        std::string ligne;
//        fs.open(str.c_str());
//        char c='\t';
//        while(getline(fs, ligne))
//        {
//            std::vector<std::string> tmp;
//            split(ligne,c,tmp);
//            vect.push_back(etudiant(tmp[0],tmp[1],tmp[2],tmp[3]));
//        }

//        fs.close();

//    }
//    return vect;
//}

///**
// * @fn ecrireFichier
// * @brief ecrit le contenu d'un vecteur d'étudiants dans un fichier apres en avoir trié les éléments
// * la première entrée du vecteur ne sera pas écrite (entêtes) et lors de la création du fichier
// * les entêtes seront écrites en début de fichier
// * @param v vecteur d'étudiants à écrire dans le fichier
// * @param str chaîne de caractères représentant le chemin d'accès au fichier
// */


//void ecrireFichier( std::vector<etudiant> &v, const std::string& str){

//    std::ofstream fs;
//    if(! fs.is_open() )
//    {
//        std::string ligne;
//        fs.open(str.c_str());
//        //on trie les noms d'étudiants. Inutile de trier la ligne d'entete
//        sort(v.begin()+1,v.end());

//        std::string entete="Nom\tPrenom\tClasse\tBadge";
//        fs << entete << std::endl;
//        //inutile de reecrire la ligne d'entete conteu dans le vecteur et dont le champ Badge a ete converti en int

//        for(unsigned int i=1;i<v.size()-1;i++)
//        {
//            if(v[i] != v[i+1]) // inutile de garder les doublons
//            {
//                fs << v[i] << std::endl;
//            }
//        }

//        fs << v[v.size() -1] << std::endl;
//    }
//    fs.close();
//}


///**
// * @fn miseAJourFichier
// * @brief ajoute un étudiant à une liste d'etudiants si il contient les informations obligatoires
// * @param str  chaîne de caractères représentant le chemin d'accès au fichier à mettre à jour
// * @param entree un étudiant à ajouter au fichier
// */

//void miseAJourFichier(std::string& file, const etudiant& entree){

//    std::vector<etudiant> tmp = lireFichier(file);

//    if (entree.good()) //enregistrement non vide=> tous les champs obligatoires nom, prenom, classe, sont renseignes
//    {
//        tmp.push_back(entree);
//    }
//    else
//    {
//        return;
//    }
//    ecrireFichier( tmp, file)  ;

//}



