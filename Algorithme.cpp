#include "Algorithme.h"
#include <iostream>
#include <vector>
#include <climits>

using namespace std;
using namespace algo_ns;

void Algorithme::test(){
//    int *fs,*aps,**cout1,s,*pred,*d,**m_dantzig;
//    int n = 7;
//    int m = 12;
//    fs = new int[n+m+1];fs[0]=n+m;
//    aps = new int[n+1];aps[0]=n;
//    cout1 = new int*[n+1];
//    cout1[0] = new int[2]; cout1[0][0] = n; cout1[0][1] = m;
//    for(int i=1;i<=n;i++){
//        cout1[i] = new int[n+1];
//    }
//    fs[1] = 2;
//    fs[2] = 5;
//    fs[3] = 0; //1
//    fs[4] = 5;
//    fs[5] = 6;
//    fs[6] = 0; //2
//    fs[7] = 1;
//    fs[8] = 4;
//    fs[9] = 0; //3
//    fs[10] = 7;
//    fs[11] = 0; //4
//    fs[12] = 3;
//    fs[13] = 4;
//    fs[14] = 7;
//    fs[15] = 0; //5
//    fs[16] = 5;
//    fs[17] = 0; //6
//    fs[18] = 6;
//    fs[19] = 0; //7

//    aps[1] = 1;
//    aps[2] = 4;
//    aps[3] = 7;
//    aps[4] = 10;
//    aps[5] = 12;
//    aps[6] = 16;
//    aps[7] = 18;

//    for(int i=1;i<=n;i++){
//        for(int j=1;j<=n;j++){
//            cout1[i][j] = INT_MAX;
//        }
//    }

//    cout1[1][2] = 1;
//    cout1[1][5] = 3;
//    cout1[2][5] = 1;
//    cout1[2][6] = 4;
//    cout1[3][1] = 0;
//    cout1[3][4] = 2;
//    cout1[4][7] = 4;
//    cout1[5][3] = 1;
//    cout1[5][4] = 6;
//    cout1[5][7] = 0;
//    cout1[6][5] = 1;
//    cout1[7][6] = 1;

//    s = 1;

//    Algorithme algo;

//    algo.dijkstra(fs,aps,cout1,s,pred,d);
//    cout<<"****Test Djikstra****"<<endl;
//    cout<<"pred : ["<<pred[0];
//    for(int i=1;i<=n;i++){
//        cout<<","<<pred[i];
//    }
//    cout<<"]"<<endl;

//    cout<<"d : ["<<d[0];
//    for(int i=1;i<=n;i++){
//        cout<<","<<d[i];
//    }
//    cout<<"]"<<endl;

//    int *fs1,*aps1;
//    algo.pred2fsaps(pred,fs1,aps1);
//    cout<<"aps : ["<<aps1[0];
//    for(int i=1;i<=n;i++){
//        cout<<","<<aps1[i];
//    }
//    cout<<"]"<<endl;
//    cout<<"fs : ["<<fs1[0];
//    for(int i=1;i<=fs1[0];i++){
//        cout<<","<<fs1[i];
//    }
//    cout<<"]"<<endl;
//    algo.del_fs_aps(fs1,aps1);
//    /*Test fs aps 2 fp app*/
//    int *fp,*app;
//    algo.det_fpapp(fs,aps,fp,app);
//    cout<<"****Test fs aps 2 fp app****"<<endl;
//    cout<<"app : ["<<app[0];
//    for(int i=1;i<=n;i++){
//        cout<<","<<app[i];
//    }
//    cout<<"]"<<endl;
//    cout<<"fp : ["<<fp[0];
//    for(int i=1;i<=(n+m);i++){
//        cout<<","<<fp[i];
//    }
//    cout<<"]"<<endl;


//    algo.del_fs_aps(fs,aps);
//    algo.del_fs_aps(fp,app);
//    algo.del_matrice(cout1);
//    delete [] pred;
//    delete [] d;
//*/
//    /*Test dantzig*/
//    n = 5;
//    m = 7;

//    cout1 = new int*[n+1];
//    cout1[0] = new int[2]; cout1[0][0] = n; cout1[0][1] = m;
//    for(int i=1;i<=n;i++){
//        cout1[i] = new int[n+1];
//    }

//    for(int i=1;i<=n;i++){
//        for(int j=1;j<=n;j++){
//            cout1[i][j] = INT_MAX;
//        }
//    }

//    cout1[1][1] = 0;
//    cout1[2][2] = 0;
//    cout1[3][3] = 0;
//    cout1[4][4] = 0;
//    cout1[5][5] = 0;
//    cout1[1][2] = -1;
//    cout1[1][3] = 4;
//    cout1[2][4] = 6;
//    cout1[2][5] = -2;
//    cout1[3][4] = 2;
//    cout1[4][1] = -5;
//    cout1[4][5] = 0;

//    bool cir = algo.dantzig(cout1,m_dantzig);
//    if(!cir) cout<<"circuit"<<endl;
//    cout<<"****Test Dantzig****"<<endl;
//    cout<<"Matrix origin:"<<endl;
//    for(int i=1;i<=n;i++){
//        cout<<"| ";
//        for(int j=1;j<=n;j++){
//            switch(cout1[i][j]){
//                case INT_MAX:
//                    cout<<"m ";
//                    break;
//                default:
//                    cout<<cout1[i][j]<<" ";
//                    break;
//            }
//        }
//        cout<<"|"<<endl;
//    }
//    cout<<"Matrix dantzig:"<<endl;
//    for(int i=1;i<=n;i++){
//        cout<<"| ";
//        for(int j=1;j<=n;j++){
//            switch(m_dantzig[i][j]){
//                case INT_MAX:
//                    cout<<"m ";
//                    break;
//                default:
//                    cout<<m_dantzig[i][j]<<" ";
//                    break;
//            }
//        }
//        cout<<"|"<<endl;
//    }
//    algo.del_matrice(cout1);
//    algo.del_matrice(m_dantzig);

//    /*Test kruskal*/
//    n=8;
//    m=13;
//    arete *g,*t,a;
//    g = new arete[m];
//    //1
//    a.s = 1;
//    a.t = 2;
//    a.cout = 1;
//    g[0] = a;
//    //2
//    a.s = 1;
//    a.t = 3;
//    a.cout = 2;
//    g[1] = a;
//    //3
//    a.s = 1;
//    a.t = 4;
//    a.cout = 3;
//    g[2] = a;
//    //4
//    a.s = 2;
//    a.t = 3;
//    a.cout = 1;
//    g[3] = a;
//    //5
//    a.s = 2;
//    a.t = 5;
//    a.cout = 2;
//    g[4] = a;
//    //6
//    a.s = 2;
//    a.t = 6;
//    a.cout = 3;
//    g[5] = a;
//    //7
//    a.s = 2;
//    a.t = 7;
//    a.cout = 3;
//    g[6] = a;
//    //8
//    a.s = 3;
//    a.t = 4;
//    a.cout = 1;
//    g[7] = a;
//    //9
//    a.s = 3;
//    a.t = 7;
//    a.cout = 4;
//    g[8] = a;
//    //10
//    a.s = 4;
//    a.t = 6;
//    a.cout = 2;
//    g[9] = a;
//    //11
//    a.s = 4;
//    a.t = 7;
//    a.cout = 2;
//    g[10] = a;
//    //12
//    a.s = 4;
//    a.t = 8;
//    a.cout = 2;
//    g[11] = a;
//    //13
//    a.s = 5;
//    a.t = 6;
//    a.cout = 2;
//    g[12] = a;

//    algo.trierAretes(g,m);
//    algo.kruskal(g,n,t);
//    cout<<"****Test Kruskal****"<<endl;
//    for(int i=0;i<(n-1);i++){
//        cout<<"["<<t[i].s<<","<<t[i].t<<","<<t[i].cout<<"]"<<endl;
//    }

//    delete [] g;
//    delete [] t;

//    /*Test prim*/
//    n=6;
//    m=10;

//    g = new arete[m];
//    //1
//    a.s = 1;
//    a.t = 2;
//    a.cout = 1;
//    g[0] = a;
//    //2
//    a.s = 1;
//    a.t = 3;
//    a.cout = 5;
//    g[1] = a;
//    //3
//    a.s = 1;
//    a.t = 4;
//    a.cout = 3;
//    g[2] = a;
//    //4
//    a.s = 1;
//    a.t = 5;
//    a.cout = 5;
//    g[3] = a;
//    //5
//    a.s = 1;
//    a.t = 6;
//    a.cout = 5;
//    g[4] = a;
//    //6
//    a.s = 2;
//    a.t = 3;
//    a.cout = 4;
//    g[5] = a;
//    //7
//    a.s = 2;
//    a.t = 6;
//    a.cout = 6;
//    g[6] = a;
//    //8
//    a.s = 3;
//    a.t = 4;
//    a.cout = 2;
//    g[7] = a;
//    //9
//    a.s = 4;
//    a.t = 5;
//    a.cout = 6;
//    g[8] = a;
//    //10
//    a.s = 5;
//    a.t = 6;
//    a.cout = 3;
//    g[9] = a;

//    s = 2;
//    algo.prim(g,n,m,s,t);

//    cout<<"****Test Prim****"<<endl;
//    for(int i=0;i<(n-1);i++){
//        cout<<"["<<t[i].s<<","<<t[i].t<<","<<t[i].cout<<"]"<<endl;
//    }

//    delete [] g;
//    delete [] t;
//    /*Test prufer*/
//    g = new arete[8];
//    //1
//    a.s = 1;
//    a.t = 6;
//    g[0] = a;
//    //2
//    a.s = 1;
//    a.t = 7;
//    g[1] = a;
//    //3
//    a.s = 1;
//    a.t = 2;
//    g[2] = a;
//    //4
//    a.s = 2;
//    a.t = 3;
//    g[3] = a;
//    //5
//    a.s = 2;
//    a.t = 4;
//    g[4] = a;
//    //6
//    a.s = 2;
//    a.t = 5;
//    g[5] = a;
//    //7
//    a.s = 5;
//    a.t = 8;
//    g[6] = a;
//    //8
//    a.s = 5;
//    a.t = 9;
//    g[7] = a;
//    int *h;
//    algo.prufer(g,9,h);
//    cout<<"****Test Prufer****"<<endl;
//    cout<<"h: ["<<h[0];
//    for(int i=1;i<7;i++){
//        cout<<","<<h[i];
//    }
//    cout<<"]"<<endl;
//    delete [] g;
//    delete [] h;

//    int *poids,**matrix; //*aps,*fs,n,m
//    n = 5;m = 7;
//    matrix = new int*[n+1];
//    matrix[0] = new int[2]; matrix[0][0] = n; matrix[0][1] = m;
//    for(int i=1;i<=n;i++){
//        matrix[i] = new int[n+1];
//        for(int j=1;j<=n;j++) matrix[i][j] = INT_MAX;
//    }
//    matrix[1][2] = 1;
//    matrix[1][5] = 3;
//    matrix[2][5] = 1;
//    matrix[3][1] = 0;
//    matrix[3][4] = 2;
//    matrix[5][3] = 1;
//    matrix[5][4] = 6;
//    algo.matrix2all(matrix,fs,aps,poids);
//    cout<<"****Test matrix2all****"<<endl;
//    cout<<"aps: ["<<aps[0];
//    for(int i=1;i<=n;i++){
//        cout<<","<<aps[i];
//    }
//    cout<<"]"<<endl;
//    cout<<"fs: ["<<fs[0];
//    for(int i=1;i<=(n+m);i++){
//        cout<<","<<fs[i];
//    }
//    cout<<"]"<<endl;
//    cout<<"poids: ["<<poids[0];
//    for(int i=1;i<=(n+m);i++){
//        cout<<","<<poids[i];
//    }
//    cout<<"]"<<endl;
//    algo.del_matrice(matrix);

//    algo.all2matrix(fs,aps,poids,matrix);
//    cout<<"****Test all2matrix****"<<endl;
//    cout<<"Matrix:"<<endl;
//    for(int i=1;i<=n;i++){
//        cout<<"| ";
//        for(int j=1;j<=n;j++){
//            switch(matrix[i][j]){
//                case INT_MAX:
//                    cout<<"m ";
//                    break;
//                default:
//                    cout<<matrix[i][j]<<" ";
//                    break;
//            }
//        }
//        cout<<"|"<<endl;
//    }

//    algo.del_matrice(matrix);
//    algo.del_fs_aps_poids(fs,aps,poids);

//    n=4;m=4;
//    g = new arete[4];
//    //1
//    a.s = 1;
//    a.t = 2;
//    a.cout = 1;
//    g[0] = a;
//    //2
//    a.s = 1;
//    a.t = 3;
//    a.cout = 2;
//    g[1] = a;
//    //3
//    a.s = 1;
//    a.t = 4;
//    a.cout = 3;
//    g[2] = a;
//    //4
//    a.s = 2;
//    a.t = 3;
//    a.cout = 1;
//    g[3] = a;

//    algo.aretes2matrix(g,matrix,n,m);
//    cout<<"****Test aretes2matrix****"<<endl;
//    cout<<"Matrix:"<<endl;
//    for(int i=1;i<=n;i++){
//        cout<<"| ";
//        for(int j=1;j<=n;j++){
//            switch(matrix[i][j]){
//                case INT_MAX:
//                    cout<<"m ";
//                    break;
//                default:
//                    cout<<matrix[i][j]<<" ";
//                    break;
//            }
//        }
//        cout<<"|"<<endl;
//    }
//    algo.del_aretes(g);

//    algo.matrix2aretes(matrix,g,n,m);
//    cout<<"****Test matrix2arete****"<<endl;
//    for(int i=0;i<m;i++){
//        cout<<"["<<g[i].s<<","<<g[i].t<<","<<g[i].cout<<"]"<<endl;
//    }

//    algo.del_matrice(matrix);
//    delete [] g;

//    /*Test ddi*/
//    int *ddi;
//    n = 7;
//    m = 12;
//    fs = new int[n+m+1];fs[0]=n+m;
//    aps = new int[n+1];aps[0]=n;

//    fs[1] = 2;
//    fs[2] = 5;
//    fs[3] = 0; //1
//    fs[4] = 5;
//    fs[5] = 6;
//    fs[6] = 0; //2
//    fs[7] = 1;
//    fs[8] = 4;
//    fs[9] = 0; //3
//    fs[10] = 7;
//    fs[11] = 0; //4
//    fs[12] = 3;
//    fs[13] = 4;
//    fs[14] = 7;
//    fs[15] = 0; //5
//    fs[16] = 5;
//    fs[17] = 0; //6
//    fs[18] = 6;
//    fs[19] = 0; //7

//    aps[1] = 1;
//    aps[2] = 4;
//    aps[3] = 7;
//    aps[4] = 10;
//    aps[5] = 12;
//    aps[6] = 16;
//    aps[7] = 18;

//    algo.det_ddi(fs,aps,ddi);
//    cout<<"****Test det_ddi****"<<endl;
//    cout<<"ddi : ["<<ddi[0];
//    for(int i=1;i<=n;i++){
//        cout<<","<<ddi[i];
//    }
//    cout<<"]"<<endl;
//    algo.del_fs_aps(fs,aps);
//    delete [] ddi;

//    /*Test rang*/
//    n = 9;
//    m = 15;
//    fs = new int[n+m+1];fs[0]=n+m;
//    aps = new int[n+1];aps[0]=n;

//    fs[1] = 2;
//    fs[2] = 3;
//    fs[3] = 0; //1
//    fs[4] = 4;
//    fs[5] = 0; //2
//    fs[6] = 4;
//    fs[7] = 5;
//    fs[8] = 0; //3
//    fs[9] = 0; //4
//    fs[10] = 4;
//    fs[11] = 6;
//    fs[12] = 0; //5
//    fs[13] = 4;
//    fs[14] = 7;
//    fs[15] = 9;
//    fs[16] = 0; //6
//    fs[17] = 4;
//    fs[18] = 9;
//    fs[19] = 0; //7
//    fs[20] = 2;
//    fs[21] = 4;
//    fs[22] = 0; //8
//    fs[23] = 4;
//    fs[24] = 0; //9


//    aps[1] = 1;
//    aps[2] = 4;
//    aps[3] = 6;
//    aps[4] = 9;
//    aps[5] = 10;
//    aps[6] = 13;
//    aps[7] = 17;
//    aps[8] = 20;
//    aps[9] = 23;

//    int *rang;
//    algo.det_rang(fs,aps,rang);
//    cout<<"****Test det_rang****"<<endl;
//    cout<<"rang : ["<<rang[0];
//    for(int i=1;i<=n;i++){
//        cout<<","<<rang[i];
//    }
//    cout<<"]"<<endl;

//    algo.del_fs_aps(fs,aps);
//    delete [] rang;

//    /*Test distances*/
//    n = 7;
//    m = 10;
//    fs = new int[n+m+1];fs[0]=n+m;
//    aps = new int[n+1];aps[0]=n;

//    fs[1] = 2;
//    fs[2] = 3;
//    fs[3] = 5;
//    fs[4] = 0; //1
//    fs[5] = 3;
//    fs[6] = 0; //2
//    fs[7] = 4;
//    fs[8] = 0; //3
//    fs[9] = 5;
//    fs[10] = 7;
//    fs[11] = 0; //4
//    fs[12] = 3;
//    fs[13] = 0; //5
//    fs[14] = 4;
//    fs[15] = 0; //6
//    fs[16] = 6;
//    fs[17] = 0; //7

//    aps[1] = 1;
//    aps[2] = 5;
//    aps[3] = 7;
//    aps[4] = 9;
//    aps[5] = 12;
//    aps[6] = 14;
//    aps[7] = 16;

//    int *marque;
//    s=1;
//    algo.det_dist(fs,aps,s,marque);
//    cout<<"****Test det_dist****"<<endl;
//    cout<<"marque : ["<<marque[0];
//    for(int i=1;i<=n;i++){
//        cout<<","<<marque[i];
//    }
//    cout<<"]"<<endl;

//    algo.del_fs_aps(fs,aps);
//    delete [] marque;

//    /*Test all2lists*/
//    n = 7;
//    m = 12;
//    fs = new int[n+m+1];fs[0]=n+m;
//    aps = new int[n+1];aps[0]=n;
//    poids = new int[n+m+1];poids[0]=n+m;

//    fs[1] = 2;
//    fs[2] = 5;
//    fs[3] = 0; //1
//    fs[4] = 5;
//    fs[5] = 6;
//    fs[6] = 0; //2
//    fs[7] = 1;
//    fs[8] = 4;
//    fs[9] = 0; //3
//    fs[10] = 7;
//    fs[11] = 0; //4
//    fs[12] = 3;
//    fs[13] = 4;
//    fs[14] = 7;
//    fs[15] = 0; //5
//    fs[16] = 5;
//    fs[17] = 0; //6
//    fs[18] = 6;
//    fs[19] = 0; //7

//    poids[1] = 1;
//    poids[2] = 3;
//    poids[3] = INT_MAX; //1
//    poids[4] = 1;
//    poids[5] = 4;
//    poids[6] = INT_MAX; //2
//    poids[7] = 0;
//    poids[8] = 2;
//    poids[9] = INT_MAX; //3
//    poids[10] = 4;
//    poids[11] = INT_MAX; //4
//    poids[12] = 1;
//    poids[13] = 6;
//    poids[14] = 0;
//    poids[15] = INT_MAX; //5
//    poids[16] = 1;
//    poids[17] = INT_MAX; //6
//    poids[18] = 1;
//    poids[19] = INT_MAX; //7

//    aps[1] = 1;
//    aps[2] = 4;
//    aps[3] = 7;
//    aps[4] = 10;
//    aps[5] = 12;
//    aps[6] = 16;
//    aps[7] = 18;



//    principale* pri;

//    algo.all2lists(fs,aps,poids,pri);
//    cout<<"****Test all2lists****"<<endl;
//    algo.affiche_lists(pri);
//    algo.del_fs_aps_poids(fs,aps,poids);

//    /*Test lists2all*/
//    algo.lists2all(pri,fs,aps,poids);
//    n = aps[0];
//    m = fs[0] - n;
//    cout<<"****Test lists2all****"<<endl;
//    cout<<"aps : ["<<aps[0];
//    for(int i=1;i<=n;i++){
//        cout<<","<<aps[i];
//    }
//    cout<<"]"<<endl;
//    cout<<"fs : ["<<fs[0];
//    for(int i=1;i<=(n+m);i++){
//        cout<<","<<fs[i];
//    }
//    cout<<"]"<<endl;
//        cout<<"poids : ["<<poids[0];
//    for(int i=1;i<=(n+m);i++){
//        cout<<","<<poids[i];
//    }
//    cout<<"]"<<endl;
//    algo.del_fs_aps_poids(fs,aps,poids);
//    algo.del_lists(pri);

//    /*Test bellman*/
//    n = 6;
//    m = 9;
//    s = 1;
//    fs = new int[n+m+1]; fs[0] = n+m;
//    poids = new int[n+m+1]; poids[0] = n+m;
//    aps = new int[n+1];aps[0] = n;

//    fs[1] = 2;
//    fs[2] = 3;
//    fs[3] = 0; //1
//    fs[4] = 3;
//    fs[5] = 6;
//    fs[6] = 0; //2
//    fs[7] = 5;
//    fs[8] = 6;
//    fs[9] = 0; //3
//    fs[10] = 3;
//    fs[11] = 5;
//    fs[12] = 0; //4
//    fs[13] = 0; //5
//    fs[14] = 5;
//    fs[15] = 0; //6

//    poids[1] = 2;
//    poids[2] = 1;
//    poids[3] = INT_MAX; //1
//    poids[4] = -2;
//    poids[5] = 2;
//    poids[6] = INT_MAX; //2
//    poids[7] = 1;
//    poids[8] = -2;
//    poids[9] = INT_MAX; //3
//    poids[10] = 5;
//    poids[11] = 0;
//    poids[12] = INT_MAX; //4
//    poids[13] = INT_MAX; //5
//    poids[14] = -1;
//    poids[15] = INT_MAX; //6

//    aps[1] = 1;
//    aps[2] = 4;
//    aps[3] = 7;
//    aps[4] = 10;
//    aps[5] = 13;
//    aps[6] = 14;

//    cout<<"****Test bellman****"<<endl;
//    algo.det_fpapp(fs,aps,fp,app);
//    cout<<"app : ["<<app[0];
//    for(int i=1;i<=n;i++){
//        cout<<","<<app[i];
//    }
//    cout<<"]"<<endl;
//    cout<<"fp : ["<<fp[0];
//    for(int i=1;i<=(n+m);i++){
//        cout<<","<<fp[i];
//    }
//    cout<<"]"<<endl;
//    algo.del_fs_aps(fp,app);

//    algo.bellman(fs,aps,poids,s,pred,d);

//    cout<<"pred : ["<<pred[0];
//    for(int i=1;i<=n;i++){
//        cout<<","<<pred[i];
//    }
//    cout<<"]"<<endl;
//    cout<<"d : ["<<d[0];
//    for(int i=1;i<=n;i++){
//        cout<<","<<d[i];
//    }
//    cout<<"]"<<endl;

//    delete [] d;
//    delete [] pred;
//    algo.del_fs_aps_poids(fs,aps,poids);

//    n = 5;
//    m = 7;
//    //n = 7;
//    //m = 12;
//    cout1 = new int*[n+1];
//    cout1[0] = new int[2]; cout1[0][0] = n; cout1[0][1] = m;
//    for(int i=1;i<=n;i++){
//        cout1[i] = new int[n+1];
//    }

//    for(int i=1;i<=n;i++){
//        for(int j=1;j<=n;j++){
//            cout1[i][j] = INT_MAX;
//        }
//    }

//    /*Test estSymetrique*/
//    cout1[1][1] = 0;
//    cout1[2][2] = 0;
//    cout1[3][3] = 0;
//    cout1[4][4] = 0;
//    cout1[5][5] = 0;
//    cout1[1][2] = -1;
//    cout1[2][1] = -1;
//    cout1[2][4] = 6;
//    cout1[4][2] = 6;
//    cout1[3][4] = 2;
//    cout1[4][3] = 2;
//    cout1[4][4] = 8;

//    cout<<"****Test estSymetrique****"<<endl;
//    if(algo.estSymetrique(cout1)) cout<<"C'est symetrique"<<endl;
//    cout1[5][5] = 6;
//    if(algo.estSymetrique(cout1)) cout<<"C'est symetrique apres changer [5][5]"<<endl;
//    cout1[3][5] = 10;
//    if(!algo.estSymetrique(cout1)) cout<<"C'est asymetrique apres changer [3][5]"<<endl;

//    algo.del_matrice(cout1);




//}

//void Algorithme::dijkstra(int* fs, int* aps,int *poids,int s,int* &pred,int* &d){
//    int **cout;
//    all2matrix(fs,aps,poids,cout);
//    int n = aps[0];int x,j,m,k;
//    m = n-1;
//    d = new int[n+1]; d[0] = n;
//    pred = new int[n+1]; pred[0] = n;
//    bool *b = new bool[n+1];
//    b[0] = false;

//    for(int i=1;i<=n;i++){
//        d[i] = cout[s][i];
//        pred[i] = s;
//        b[i] = true;

//    }
//    pred[s] = 0;
//    d[s] = 0;
//    b[s] = false;

//    while(m>0){
//        x = INT_MAX;
//        for(int i=1;i<=n;i++){
//            if(b[i]){
//                if(d[i]<x){
//                    x = d[i];
//                    j = i;
//                }
//            }
//        }
//        if(x == INT_MAX)
//            break;
//        b[j] = false;
//        m--;
//        k = aps[j];
//        while(fs[k]>0){
//            if(b[fs[k]]){
//                int v = d[j] + cout[j][fs[k]];
//                if(v<d[fs[k]]){
//                    d[fs[k]] = v;
//                    pred[fs[k]] = j;
//                }
//            }
//            k++;
//        }
//    }
//    del_matrice(cout);
//    delete [] b;
}

void Algorithme::det_fpapp(int* fs, int* aps,int *&fp,int *&app){
    int n = aps[0];
    int nm = fs[0];
    app = new int[n+1]; app[0]=n;
    fp = new int[nm+1]; fp[0]=nm;
    int *np = new int[n+1];
    for(int i=1;i<=n;i++) np[i]=0;
    for(int i=1;i<=nm;i++){
        if(fs[i]!=0) np[fs[i]]++;
    }
    app[1]=1;
    for(int i=1;i<n;i++) app[i+1] = app[i]+np[i]+1;
    int k=1,t;
    for(int i=1;i<=n;i++){
        while((t=fs[k])!=0){
            fp[app[t]]=i;
            app[t]++;
            k++;
        }
        k++;
    }
    fp[app[n]]=0;
    for(int i=n-1;i>=1;i--){
        fp[app[i]]=0;
        app[i+1] = app[i]+1;
    }
    app[1]=1;
    delete [] np;
}

void Algorithme::bellman(int* fs, int* aps,int* poids,int s,int* &pred,int* &d){
    int **a,*fp,*app;
    int n = aps[0];
    all2matrix(fs,aps,poids,a);
    det_fpapp(fs,aps,fp,app);
    d = new int[n+1]; d[0] = n; d[s] = 0;
    pred = new int[n+1]; pred[0] = n; pred[s] = 0;
    bool *S = new bool[n+1];
    for(int i=0;i<=n;i++) S[i] = false;
    S[0] = true;
    S[s] = true;
    vector<int> X;
    for(int i=1;i<s;i++) X.push_back(i);
    for(int i=s+1;i<=n;i++) X.push_back(i);
    X.push_back(-1);
    int min,nb,min_t,k,l,t,valeur;
    nb = n-1;
    bool existe = true;
    while(nb>0&&existe){
        k = 0;
        existe = false;
        while(!existe&&X[k]!=-1){
            min = INT_MAX;
            min_t = 0;
            l = app[X[k]];
            existe = true;
            while((t=fp[l])!=0){
                if(!S[t]){
                    existe = false;
                    break;
                }
                if(d[t]<INT_MAX&&(valeur=d[t]+a[t][X[k]])<min){
                    min = valeur;
                    min_t = t;
                }
                l++;
            }
            if(existe){
                d[X[k]] = min;
                pred[X[k]] = min_t;
                S[X[k]] = true;
                for(unsigned int j=k;j<(X.size()-1);j++){
                    X[j] = X[j+1];
                }
                X.pop_back();
                nb--;
            }
            k++;
        }
    }

    delete [] S;
    delete [] fp;
    delete [] app;
    del_matrice(a);
}

bool Algorithme::dantzig(int **a,int **&m){
    int n = a[0][0];
    m = new int*[n+1];

    m[0] = new int[2]; m[0][0] = a[0][0]; m[0][1] = a[0][1];
    for(int i=1;i<=n;i++) m[i] = new int[n+1];
    for(int i=1;i<=n;i++)
        for(int j=1;j<=n;j++)
            m[i][j] = a[i][j];
    int x;
    for(int k=1;k<n;k++){
        for(int i=1;i<=k;i++){
            for(int j=1;j<=k;j++){
                if((x=m[i][j]+m[j][k+1])<m[i][k+1]&&m[i][j]<(INT_MAX/2)&&m[j][k+1]<(INT_MAX/2)){
                    m[i][k+1] = x;
                }
                if((x=m[k+1][j]+m[j][i])<m[k+1][i]&&m[k+1][j]<(INT_MAX/2)&&m[j][i]<(INT_MAX/2)){
                    m[k+1][i]=x;
                }
            }
            if((x=m[k+1][i]+m[i][k+1])<0&&m[k+1][i]<(INT_MAX/2)&&m[i][k+1]<(INT_MAX/2)){
                return false;
            }
        }
        for(int i=1;i<=k;i++){
            for(int j=1;j<=k;j++)
                if((x=m[i][k+1]+m[k+1][j])<m[i][j]&&m[i][k+1]<(INT_MAX/2)&&m[k+1][j]<(INT_MAX/2)){
                    m[i][j] = x;
                }
        }
    }
    return true;
}

bool Algorithme::estSymetrique(int **a){
    int n = a[0][0];
    for(int i=1;i<=n;i++)
        for(int j=i+1;j<=n;j++)
            if(a[i][j]!=a[j][i])
                return false;
    return true;
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

void Algorithme::kruskal(arete *g,int n,arete *&t){
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
        int i = cc[g[l].s];
        int j = cc[g[l].t];
        if(i!=j){
            t[k++] = g[l];
            joindre(i,j,prem,cc,pilch);
        }
        l++;
    }

    delete [] pilch;
    delete [] prem;
    delete [] cc;

}

void Algorithme::prim(arete *g,int n,int m,int s,arete *&t){
    bool *X = new bool[n+1];
    vector<int> aretes;
    t = new arete[n-1];
    for(int i=0;i<m;i++) aretes.push_back(i);
    aretes.push_back(-1);
    for(int i=0;i<=n;i++) X[i] = false;
    X[s] = true;
    int min_k,l=0;
    long min;

    //arete a;

    while(l<(n-1)){
        min = INT_MAX;
        unsigned int k=0;
        while(k<aretes.size()-1){
            if((!X[g[aretes[k]].s]&&X[g[aretes[k]].t])||(X[g[aretes[k]].s]&&!X[g[aretes[k]].t])){
                if(g[aretes[k]].cout<min){
                    min = g[aretes[k]].cout;
                    min_k = k;
                }
            }
            k++;
        }
        t[l++] = g[aretes[min_k]];
        if(X[g[aretes[min_k]].s]){
            X[g[aretes[min_k]].t] = true;
        }
        else{
            X[g[aretes[min_k]].s] = true;
        }
        for(unsigned int i=min_k;i<(aretes.size()-1);i++){
            aretes[i] = aretes[i+1];
        }
        aretes.pop_back();
    }
    delete [] X;

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
    delete [] s;
}
void Algorithme::matrix2all(int **a,int *&fs,int *&aps,int *&poids){
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
            if(a[i][j]<INT_MAX&&i!=j){
                fs[k] = j;
                poids[k] = a[i][j];
                k++;
            }
        }
        fs[k] = 0;
        poids[k] = INT_MAX;
        k++;
    }
}

void Algorithme::all2matrix(int *fs,int *aps,int *poids,int **&a){
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
}

void Algorithme::matrix2aretes(int **a,arete *&g,int &n,int &m){
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
}

void Algorithme::aretes2matrix(arete *g,int **&a,int n,int m){
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
}

void Algorithme::pred2fsaps(int* pred,int *&fs,int *&aps){
    int n = pred[0];
    int *fp,*app;
    fp = new int[n+n]; fp[0] = n+n-1;
    app = new int[n+1]; app[0] = n;
    int k=1;
    for(int i=1;i<=n;i++){
        app[i] = k;
        if(pred[i]!=0)
            fp[k++] = pred[i];
        fp[k++] = 0;
    }
    det_fpapp(fp,app,fs,aps);
    del_fs_aps(fp,app);
}

principale* Algorithme::adresse(principale* pri,int sommet){
    principale* tmp = pri;
    while(tmp != NULL){
        if(tmp->num == sommet) return tmp;
        tmp = tmp->suiv;
    }
    return NULL;
}

void Algorithme::all2lists(int *fs,int *aps,int *poids,principale *&pri){
    int n = aps[0];
    pri = new principale;
    principale *tmp = pri;
    for(int i=1;i<n;i++){
        tmp->num = i;
        tmp->suiv = new principale;
        tmp->succ = new secondaire;
        tmp = tmp->suiv;
    }
    tmp->num = n;
    tmp->suiv = NULL;
    tmp->succ = new secondaire;

    int l,t,i;
    tmp = pri;
    secondaire *tmpsucc,*succlast;
    while(tmp!=NULL){
        i = tmp->num;
        tmpsucc = tmp->succ;
        l = aps[i];
        while((t=fs[l])!=0){
            tmpsucc->som = adresse(pri,t);
            tmpsucc->suiv = new secondaire;
            tmpsucc->cout = poids[l];
            l++;
            succlast = tmpsucc;
            tmpsucc = tmpsucc->suiv;
        }
        delete tmpsucc;
        succlast->suiv = NULL;
        tmp = tmp->suiv;
    }
}

void Algorithme::lists2all(principale *pri,int *&fs,int *&aps,int *&poids){
    int n=0,m=0,k;
    principale *tmp;
    secondaire *tmpsucc;
    tmp = pri;
    while(tmp != NULL){
        n++;
        k = 0;
        tmpsucc = tmp->succ;
        while(tmpsucc != NULL){
            m++;
            tmpsucc = tmpsucc->suiv;
        }
        tmp = tmp->suiv;
    }

    fs = new int[n+m+1]; fs[0] = n+m;
    poids = new int[n+m+1]; poids[0] = n+m;
    aps = new int[n+1]; aps[0] = n;
    k = 1;
    tmp = pri;
    while(tmp != NULL){
        tmpsucc = tmp->succ;
        aps[tmp->num] = k;
        while(tmpsucc != NULL){
            fs[k] = tmpsucc->som->num;
            poids[k++] = tmpsucc->cout;
            tmpsucc = tmpsucc->suiv;
        }
        fs[k] = 0;
        poids[k++] = INT_MAX;
        tmp = tmp->suiv;
    }
}

void Algorithme::affiche_lists(principale *pri){
    principale *temp;
    secondaire *tempsucc;
    temp = pri;
    while(temp!=NULL){
        tempsucc = temp->succ;
        while(tempsucc!=NULL){
            cout<<temp->num<<"->"<<tempsucc->som->num<<endl;
            tempsucc = tempsucc->suiv;
        }
        temp = temp->suiv;
    }
}

void Algorithme::affiche_fs_aps_poids(int *fs,int *aps,int *poids){
    int n = aps[0];
    int nm = fs[0];
    cout<<"aps : ["<<aps[0];
    for(int i=1;i<=n;i++){
        cout<<","<<aps[i];
    }
    cout<<"]"<<endl;
    cout<<"fs : ["<<fs[0];
    for(int i=1;i<=nm;i++){
        cout<<","<<fs[i];
    }
    cout<<"]"<<endl;
    cout<<"poids : [";
    if(poids[0]<INT_MAX)
        cout<<poids[0];
    else
        cout<<"m";
    for(int i=1;i<=nm;i++){
        if(poids[i]<INT_MAX)
            cout<<","<<poids[i];
        else
            cout<<",m";
    }
    cout<<"]"<<endl;
}

void Algorithme::affiche_matrice(int **a){
    cout<<"Matrice d'adjacent :"<<endl;
    int n = a[0][0];
    for(int i=1;i<=n;i++){
        cout<<"| ";
        for(int j=1;j<=n;j++){
            switch(a[i][j]){
                case INT_MAX:
                    cout<<"m ";
                    break;
                default:
                    cout<<a[i][j]<<" ";
                    break;
            }
        }
        cout<<"|"<<endl;
    }
}

void Algorithme::affiche_aretes(arete *g,int n,int m){
    cout<<"Sommets : "<<n<<endl;
    cout<<"Aretes : "<<m<<endl;
    for(int i=0;i<m;i++){
        cout<<g[i].s<<" - "<<g[i].t<<"   cout : "<<g[i].cout<<endl;
    }
}

void Algorithme::del_lists(principale *&pri){
    principale *pri1,*pri2;
    secondaire *sec1,*sec2;
    pri1 = pri;
    while(pri1 != NULL){
        pri2 = pri1->suiv;
        sec1 = pri1->succ;
        while(sec1 != NULL){
            sec2 = sec1->suiv;
            delete sec1 ;
            sec1 = sec2;
        }
        delete pri1;
        pri1 = pri2;
    }
}

void Algorithme::det_ddi(int *fs,int *aps,int *&ddi){
    int n = aps[0];
    ddi = new int[n+1];
    for(int i=1;i<=n;i++) ddi[i]=0;
    ddi[0] = n;
    int l,t;
    for(int i=1;i<=n;i++){
        l = aps[i];
        while((t=fs[l])!=0){
            ddi[t]++;
            l++;
        }
    }
}

int Algorithme::det_rang(int *fs,int *aps,int *&rang){
    int n = aps[0];
    int *ddi,*pilch,/**prem,*/k=-1,s,t;
    det_ddi(fs,aps,ddi);
    rang = new int[n+1];
    rang[0] = n;
    pilch = new int[n+1];
    //prem = new int[n];
    pilch[0] = 0;
    for(int i=1;i<=n;i++){
        rang[i] = -1;
        if(ddi[i]==0){
            pilch[i] = pilch[0];
            pilch[0] = i;
        }
    }

    s = pilch[0];
    //prem[0] = s;
    while(pilch[0]>0){
        k++;
        pilch[0] = 0;
        while(s>0){
            rang[s] = k;
            for(int l=aps[s];(t=fs[l])>0;l++){
                ddi[t]--;
                if(ddi[t]==0){
                    pilch[t] = pilch[0];
                    pilch[0] = t;
                }
            }
            s = pilch[s];
        }
        s = pilch[0];
        //prem[k+1] = s;

    }

    delete [] ddi;
    delete [] pilch;
    //delete(prem);

    return k;
}

void Algorithme::det_dist(int *fs,int *aps,int s,int *&marque){
    int n = aps[0];
    marque = new int[n+1];
    marque[0] = n;
    for(int i=1;i<=n;i++) marque[i] = -1;
    int *fa = new int[n+1];
    int t=1,q=2,k=2,d=0;
    fa[1] = s;
    marque[s] = 0;
    while(t<q){
        d++;
        for(int j=t;j<q;j++){
            int l = aps[fa[j]];
            while(fs[l]!=0){
                if(marque[fs[l]] == -1){
                    marque[fs[l]] = d;
                    fa[k++] = fs[l];
                }
                l++;
            }
        }
        t = q;
        q = k;
    }

    delete [] fa;

}

void Algorithme::del_fs_aps(int* fs,int* aps){
    delete [] fs;
    delete [] aps;
}

void Algorithme::del_fs_aps_poids(int* fs,int* aps,int *poids){
    del_fs_aps(fs,aps);
    delete [] poids;
}

void Algorithme::del_matrice(int **a){
    int n = a[0][0];
    for(int i=0;i<=n;i++){
        delete [] a[i];
    }
    delete [] a;
}

void Algorithme::del_aretes(arete *g){
    delete [] g;
}
