#include "Algorithme.h"
#include <iostream>
#include <vector>
#include <climits>


using namespace std;
using namespace algo_ns;

void Algorithme::dijkstra(int* fs, int* aps,int **cout,int s,int* &pred,int* &d){
    int n = aps[0];int x,j,m,k;
    m = n-1;
    d = new int[n+1]; d[0] = n;
    pred = new int[n+1]; pred[0] = n;
    bool *b = new bool[n+1];
    b[0] = false;

    for(int i=1;i<=n;i++){
        d[i] = cout[s][i];
        pred[i] = s;
        b[i] = true;

    }
    d[s] = 0;
    b[s] = false;

    while(m>0){
        x = INT_MAX;
        for(int i=1;i<=n;i++){
            if(b[i]){
                if(d[i]<x){
                    x = d[i];
                    j = i;
                }
            }
        }
        if(x == INT_MAX)
            break;
        b[j] = false;
        m--;
        k = aps[j];
        while(fs[k]>0){
            if(b[fs[k]]){
                int v = d[j] + cout[j][fs[k]];
                if(v<d[fs[k]]){
                    d[fs[k]] = v;
                    pred[fs[k]] = j;
                }
            }
            k++;
        }
    }
    delete(b);
}

void Algorithme::joindre(int i,int j,int *prem,int *cc,int *pilch){
    if(i>j){
        int r=i;
        i=j;
        j=r;
    }
    int k = prem[j];
    int t;
    while(k!=0){
        cc[k] = i;
        t = k;
        k = pilch[k];
    }
    pilch[t] = prem[i];
    prem[i] = prem[j];
}

void Algorithme::trierAretes(arete *&g,int m){
    arete a;
    for(int i=0;i<(m-1);i++){
        for(int j=i;j<m;j++){
            if(g[i].cout>g[j].cout){
                a = g[i];
                g[i] = g[j];
                g[j] = a;
            }
        }
    }
}

void Algorithme::kruskal(arete *g,int n,int m,arete *&t){
    t = new arete[n];
    int *pilch = new int[n+1];
    int *prem = new int[n+1];
    int *cc = new int[n+1];

    int k=0,l=0;
    for(int i=1;i<=n;i++){
        prem[i] = i;
        pilch[i] = 0;
        cc[i] = i;
    }

    while(k<(n-1)){
        std::cout<<"ca marche bien"<<std::endl;
        std::cout<<k<<std::endl;
        int i = cc[g[l].s];
        int j = cc[g[l].t];
        if(i!=j){
            t[k++] = g[l];
            joindre(i,j,prem,cc,pilch);
        }
        l++;
    }

    delete(pilch);
    delete(prem);
    delete(cc);

}

void Algorithme::prufer(arete *g,int n,int *&t){
    int m = n-2;
    t = new int[m];
    int *s = new int[n+1];
    vector<int> aretes;
    for (int i = 0; i <= n; i++) s[i] = 0;
    for(int i = 0; i<(n-1);i++){
        s[g[i].s]++;
        s[g[i].t]++;
        aretes.push_back(i);
    }
    aretes.push_back(-1);
    int x;
    int k,l;
    l = 0;
    int size = aretes.size()-1;
    int feuille;
    while(size>1){
        k = 0;
        feuille = INT_MAX;
        for(int i=0;i<size;i++){
            if(s[g[aretes[i]].s] == 1){
                if(g[aretes[i]].s < feuille){
                    feuille = g[aretes[i]].s;
                    x = g[aretes[i]].t;
                    k = i;
                }
            }
            else{
                if(s[g[aretes[i]].t] == 1){
                    if(g[aretes[i]].t < feuille){
                        feuille = g[aretes[i]].t;
                        x = g[aretes[i]].s;
                        k = i;
                    }
                }
            }
        }
        t[l++] = x;
        s[g[aretes[k]].t]--;
        s[g[aretes[k]].s]--;
        for(int i=k;i<size;i++){
            aretes[i] = aretes[i+1];
        }
        aretes.pop_back();
        size--;
    }
    delete(s);
}
void Algorithme::matrix2all(int **&a,int *&fs,int *&aps,int *&poids){
    int n,m;
    n = a[0][0];
    m = a[0][1];
    aps = new int[n+1]; aps[0] = n; aps[1] = 1;
    fs = new int[n+m+1]; fs[0] = n+m;
    poids = new int[n+m+1]; poids[0] = n+m;
    int k = 1;
    for(int i=1;i<=n;i++){
        aps[i] = k;
        for(int j=1;j<=n;j++){
            if(a[i][j]<INT_MAX){
                fs[k] = j;
                poids[k] = a[i][j];
                k++;
            }
        }
        fs[k] = 0;
        poids[k] = -1;
        k++;
    }
    for(int i=0;i<=n;i++){
        delete(a[i]);
    }
    delete(a);
}

void Algorithme::all2matrix(int *&fs,int *&aps,int *&poids,int **&a){
    int n = aps[0];
    int m = fs[0] - n;
    a = new int*[n+1];
    a[0] = new int[2]; a[0][0] = n; a[0][1] = m;
    for(int i=1;i<=n;i++){
        a[i] = new int[n+1];
        for(int j=1;j<=n;j++) a[i][j] = INT_MAX;
    }

    for(int i=1;i<=n;i++){
        for(int l=aps[i];fs[l]>0;l++){
            a[i][fs[l]] = poids[l];
        }

    }
    delete(fs);
    delete(aps);
    delete(poids);
}

void Algorithme::matrix2aretes(int **&a,arete *&g,int &n,int &m){
    n = a[0][0];
    m = a[0][1]/2;
    g = new arete[m];
    arete ar;
    int k = 0;
    for(int i=1;i<=n;i++){
        for(int j=i+1;j<=n;j++){
            if(a[i][j]<INT_MAX){
                ar.s = i;
                ar.t = j;
                ar.cout = a[i][j];
                g[k++] = ar;
            }
        }
    }

    for(int i=0;i<=n;i++){
        delete(a[i]);
    }
    delete(a);

}

void Algorithme::aretes2matrix(arete *&g,int **&a,int n,int m){
    a = new int*[n+1];
    a[0] = new int[2]; a[0][0] = n; a[0][1] = m*2;
    for(int i=1;i<=n;i++){
        a[i] = new int[n+1];
        for(int j=1;j<=n;j++) a[i][j] = INT_MAX;
    }

    for(int i=0;i<m;i++){
        a[g[i].s][g[i].t] = g[i].cout;
        a[g[i].t][g[i].s] = g[i].cout;
    }
    delete(g);
}

