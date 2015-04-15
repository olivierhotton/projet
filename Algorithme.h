#ifndef ALGORITHME_H
#define ALGORITHME_H

namespace algo_ns{


typedef struct {
    int s,t;
    long cout;
} arete;

class Algorithme {
    public:
        void dijkstra(int* fs, int* aps,int **cout,int s,int* &pred,int* &d);
        void kruskal(arete *g,int n,int m,arete *&t);
        void trierAretes(arete *&g,int m);
        void prufer(arete *g,int n,int *&t);
        void matrix2all(int **&a,int *&fs,int *&aps,int *&poids);
        void all2matrix(int *&fs,int *&aps,int *&poids,int **&a);
        void matrix2aretes(int **&a,arete *&g,int &n,int &m);
        void aretes2matrix(arete *&g,int **&a,int n,int m);

    private:
        void joindre(int i,int j,int *prem, int *cc,int *pilch);
};
}
#endif // ALGORITHME_H
