#include "Algorithme.h"

#include <iostream>
using namespace std;
using namespace algo_ns;
/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int main(int argc, char** argv) {
	int *fs,*aps,**cout1,s,*pred,*d,**m_dantzig;
	int n = 7;
	int m = 12;
	fs = new int[n+m+1];fs[0]=n+m;
	aps = new int[n+1];aps[0]=n;
	cout1 = new int*[n+1];
	cout1[0] = new int[2]; cout1[0][0] = n; cout1[0][1] = m;
	for(int i=1;i<=n;i++){
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
	cout<<"pred : ["<<pred[0];
	for(int i=1;i<=n;i++){
		cout<<","<<pred[i];
	}
	cout<<"]"<<endl;
			
	cout<<"d : ["<<d[0];
	for(int i=1;i<=n;i++){
		cout<<","<<d[i];
	}
	cout<<"]"<<endl;
	
	int *fs1,*aps1;
	algo.pred2fsaps(pred,fs1,aps1);
	cout<<"aps : ["<<aps1[0];
	for(int i=1;i<=n;i++){
		cout<<","<<aps1[i];
	}
	cout<<"]"<<endl;
	cout<<"fs : ["<<fs1[0];
	for(int i=1;i<=fs1[0];i++){
		cout<<","<<fs1[i];
	}
	cout<<"]"<<endl;
	algo.del_fs_aps(fs1,aps1);	
	/*Test fs aps 2 fp app*/
	int *fp,*app;
	algo.det_fpapp(fs,aps,fp,app);
	cout<<"****Test fs aps 2 fp app****"<<endl;
	cout<<"app : ["<<app[0];
	for(int i=1;i<=n;i++){
		cout<<","<<app[i];
	}
	cout<<"]"<<endl;
	cout<<"fp : ["<<fp[0];
	for(int i=1;i<=(n+m);i++){
		cout<<","<<fp[i];
	}
	cout<<"]"<<endl;
	
	
	algo.del_fs_aps(fs,aps);
	algo.del_fs_aps(fp,app);
	algo.del_matrice(cout1);
	delete [] pred;
	delete [] d;
	
	/*Test dantzig*/
	n = 5;
	m = 7;

	cout1 = new int*[n+1];
	cout1[0] = new int[2]; cout1[0][0] = n; cout1[0][1] = m;
	for(int i=1;i<=n;i++){
		cout1[i] = new int[n+1];
	}
	
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			cout1[i][j] = INT_MAX;
		}
	}
	
	cout1[1][1] = 0;
	cout1[2][2] = 0;
	cout1[3][3] = 0;
	cout1[4][4] = 0;
	cout1[5][5] = 0;
	cout1[1][2] = -1;
	cout1[1][3] = 4;
	cout1[2][4] = 6;
	cout1[2][5] = -2;
	cout1[3][4] = 2;
	cout1[4][1] = -5;
	cout1[4][5] = 0;
	
	bool cir = algo.dantzig(cout1,m_dantzig);
	if(!cir) cout<<"circuit"<<endl;
	cout<<"****Test Dantzig****"<<endl;
	cout<<"Matrix origin:"<<endl;
	for(int i=1;i<=n;i++){
		cout<<"| ";
		for(int j=1;j<=n;j++){
			switch(cout1[i][j]){
				case INT_MAX:
					cout<<"m ";
					break;
				default:
					cout<<cout1[i][j]<<" ";
					break;	
			}
		}
		cout<<"|"<<endl;
	}
	cout<<"Matrix dantzig:"<<endl;
	for(int i=1;i<=n;i++){
		cout<<"| ";
		for(int j=1;j<=n;j++){
			switch(m_dantzig[i][j]){
				case INT_MAX:
					cout<<"m ";
					break;
				default:
					cout<<m_dantzig[i][j]<<" ";
					break;	
			}
		}
		cout<<"|"<<endl;
	}
	algo.del_matrice(cout1);
	algo.del_matrice(m_dantzig);
	
	/*Test kruskal*/
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
	
	delete [] g;
	delete [] t;
	
	/*Test prim*/
	n=6;
	m=10;
	
	g = new arete[m];
	//1
	a.s = 1;
	a.t = 2;
	a.cout = 1;
	g[0] = a;
	//2
	a.s = 1;
	a.t = 3;
	a.cout = 5;
	g[1] = a;
	//3
	a.s = 1;
	a.t = 4;
	a.cout = 3;
	g[2] = a;
	//4
	a.s = 1;
	a.t = 5;
	a.cout = 5;
	g[3] = a;
	//5
	a.s = 1;
	a.t = 6;
	a.cout = 5;
	g[4] = a;
	//6
	a.s = 2;
	a.t = 3;
	a.cout = 4;
	g[5] = a;
	//7
	a.s = 2;
	a.t = 6;
	a.cout = 6;
	g[6] = a;
	//8
	a.s = 3;
	a.t = 4;
	a.cout = 2;
	g[7] = a;
	//9
	a.s = 4;
	a.t = 5;
	a.cout = 6;
	g[8] = a;
	//10
	a.s = 5;
	a.t = 6;
	a.cout = 3;
	g[9] = a;
	
	s = 2;
	algo.prim(g,n,m,s,t);
	
	cout<<"****Test Prim****"<<endl;
	for(int i=0;i<(n-1);i++){
		cout<<"["<<t[i].s<<","<<t[i].t<<","<<t[i].cout<<"]"<<endl;
	}
	
	delete [] g;
	delete [] t;
	/*Test prufer*/
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
	delete [] g;
	delete [] h;
	
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
	algo.del_matrice(matrix);
	
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
				
	algo.del_matrice(matrix);
	algo.del_fs_aps_poids(fs,aps,poids);
	
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
	algo.del_aretes(g);
	
	algo.matrix2aretes(matrix,g,n,m);
	cout<<"****Test matrix2arete****"<<endl;
	for(int i=0;i<m;i++){
		cout<<"["<<g[i].s<<","<<g[i].t<<","<<g[i].cout<<"]"<<endl;
	}
	
	algo.del_matrice(matrix);
	delete [] g;
	
	/*Test ddi*/
	int *ddi;
	n = 7;
	m = 12;
	fs = new int[n+m+1];fs[0]=n+m;
	aps = new int[n+1];aps[0]=n;

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
	
	algo.det_ddi(fs,aps,ddi);
	cout<<"****Test det_ddi****"<<endl;
	cout<<"ddi : ["<<ddi[0];
	for(int i=1;i<=n;i++){
		cout<<","<<ddi[i];
	}
	cout<<"]"<<endl;
	algo.del_fs_aps(fs,aps);
	delete [] ddi;
	
	/*Test rang*/
	n = 9;
	m = 15;
	fs = new int[n+m+1];fs[0]=n+m;
	aps = new int[n+1];aps[0]=n;

	fs[1] = 2;
	fs[2] = 3;
	fs[3] = 0; //1
	fs[4] = 4;
	fs[5] = 0; //2
	fs[6] = 4; 
	fs[7] = 5;
	fs[8] = 0; //3
	fs[9] = 0; //4
	fs[10] = 4;
	fs[11] = 6; 
	fs[12] = 0; //5
	fs[13] = 4;
	fs[14] = 7;
	fs[15] = 9; 
	fs[16] = 0; //6
	fs[17] = 4; 
	fs[18] = 9;
	fs[19] = 0; //7
	fs[20] = 2; 
	fs[21] = 4; 
	fs[22] = 0; //8
	fs[23] = 4;
	fs[24] = 0; //9
	
	
	aps[1] = 1;
	aps[2] = 4;
	aps[3] = 6;
	aps[4] = 9;
	aps[5] = 10;
	aps[6] = 13;
	aps[7] = 17;
	aps[8] = 20;
	aps[9] = 23;
	
	int *rang;
	algo.det_rang(fs,aps,rang);
	cout<<"****Test det_rang****"<<endl;
	cout<<"rang : ["<<rang[0];
	for(int i=1;i<=n;i++){
		cout<<","<<rang[i];
	}
	cout<<"]"<<endl;	
	
	algo.del_fs_aps(fs,aps);
	delete [] rang;
	
	/*Test distances*/
	n = 7;
	m = 10;
	fs = new int[n+m+1];fs[0]=n+m;
	aps = new int[n+1];aps[0]=n;

	fs[1] = 2;
	fs[2] = 3;
	fs[3] = 5; 
	fs[4] = 0; //1
	fs[5] = 3; 
	fs[6] = 0; //2 
	fs[7] = 4;
	fs[8] = 0; //3
	fs[9] = 5; 
	fs[10] = 7;
	fs[11] = 0; //4 
	fs[12] = 3; 
	fs[13] = 0; //5
	fs[14] = 4;
	fs[15] = 0; //6 
	fs[16] = 6; 
	fs[17] = 0; //7 
			
	aps[1] = 1;
	aps[2] = 5;
	aps[3] = 7;
	aps[4] = 9;
	aps[5] = 12;
	aps[6] = 14;
	aps[7] = 16;
	
	int *marque;
	s=1;
	algo.det_dist(fs,aps,s,marque);
	cout<<"****Test det_dist****"<<endl;
	cout<<"marque : ["<<marque[0];
	for(int i=1;i<=n;i++){
		cout<<","<<marque[i];
	}
	cout<<"]"<<endl;
	
	algo.del_fs_aps(fs,aps);
	delete [] marque;
	
	/*Test all2lists*/
	n = 7;
	m = 12;
	fs = new int[n+m+1];fs[0]=n+m;
	aps = new int[n+1];aps[0]=n;
	poids = new int[n+m+1];poids[0]=n+m;
	
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
	
	poids[1] = 1;
	poids[2] = 3;
	poids[3] = INT_MAX; //1
	poids[4] = 1;
	poids[5] = 4;
	poids[6] = INT_MAX; //2
	poids[7] = 0;
	poids[8] = 2;
	poids[9] = INT_MAX; //3
	poids[10] = 4;
	poids[11] = INT_MAX; //4
	poids[12] = 1;
	poids[13] = 6;
	poids[14] = 0;
	poids[15] = INT_MAX; //5
	poids[16] = 1;
	poids[17] = INT_MAX; //6
	poids[18] = 1;
	poids[19] = INT_MAX; //7
	
	aps[1] = 1;
	aps[2] = 4;
	aps[3] = 7;
	aps[4] = 10;
	aps[5] = 12;
	aps[6] = 16;
	aps[7] = 18;
	
	
	
	principale* pri;
	
	algo.all2lists(fs,aps,poids,pri);
	cout<<"****Test all2lists****"<<endl;
	algo.affiche_lists(pri);
	algo.del_fs_aps_poids(fs,aps,poids);
	
	/*Test lists2all*/
	algo.lists2all(pri,fs,aps,poids);
	n = aps[0];
	m = fs[0] - n;
	cout<<"****Test lists2all****"<<endl;
	cout<<"aps : ["<<aps[0];
	for(int i=1;i<=n;i++){
		cout<<","<<aps[i];
	}
	cout<<"]"<<endl;
	cout<<"fs : ["<<fs[0];
	for(int i=1;i<=(n+m);i++){
		cout<<","<<fs[i];
	}
	cout<<"]"<<endl;
		cout<<"poids : ["<<poids[0];
	for(int i=1;i<=(n+m);i++){
		cout<<","<<poids[i];
	}
	cout<<"]"<<endl;
	algo.del_fs_aps_poids(fs,aps,poids);
	algo.del_lists(pri);
	
	/*Test bellman*/
	n = 6;
	m = 9;
	s = 1;
	fs = new int[n+m+1]; fs[0] = n+m;
	poids = new int[n+m+1]; poids[0] = n+m;
	aps = new int[n+1];aps[0] = n;
	
	fs[1] = 2;
	fs[2] = 3;
	fs[3] = 0; //1
	fs[4] = 3;
	fs[5] = 6;
	fs[6] = 0; //2
	fs[7] = 5;
	fs[8] = 6;
	fs[9] = 0; //3
	fs[10] = 3; 
	fs[11] = 5;
	fs[12] = 0; //4
	fs[13] = 0; //5
	fs[14] = 5;
	fs[15] = 0; //6 
	
	poids[1] = 2;
	poids[2] = 1;
	poids[3] = INT_MAX; //1
	poids[4] = -2;
	poids[5] = 2;
	poids[6] = INT_MAX; //2
	poids[7] = 1;
	poids[8] = -2;
	poids[9] = INT_MAX; //3
	poids[10] = 5;
	poids[11] = 0;
	poids[12] = INT_MAX; //4
	poids[13] = INT_MAX; //5
	poids[14] = -1;
	poids[15] = INT_MAX; //6
	
	aps[1] = 1;
	aps[2] = 4;
	aps[3] = 7;
	aps[4] = 10;
	aps[5] = 13;
	aps[6] = 14;
	
	cout<<"****Test bellman****"<<endl;
	algo.det_fpapp(fs,aps,fp,app);
	cout<<"app : ["<<app[0];
	for(int i=1;i<=n;i++){
		cout<<","<<app[i];
	}
	cout<<"]"<<endl;
	cout<<"fp : ["<<fp[0];
	for(int i=1;i<=(n+m);i++){
		cout<<","<<fp[i];
	}
	cout<<"]"<<endl;
	algo.del_fs_aps(fp,app);
	
	algo.bellman(fs,aps,poids,s,pred,d);
	
	cout<<"pred : ["<<pred[0];
	for(int i=1;i<=n;i++){
		cout<<","<<pred[i];
	}
	cout<<"]"<<endl;
	cout<<"d : ["<<d[0];
	for(int i=1;i<=n;i++){
		cout<<","<<d[i];
	}
	cout<<"]"<<endl;
	
	delete [] d;
	delete [] pred;
	algo.del_fs_aps_poids(fs,aps,poids);
	
	n = 5;
	m = 7;
	//n = 7;
	//m = 12;
	cout1 = new int*[n+1];
	cout1[0] = new int[2]; cout1[0][0] = n; cout1[0][1] = m;
	for(int i=1;i<=n;i++){
		cout1[i] = new int[n+1];
	}
	
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			cout1[i][j] = INT_MAX;
		}
	}
	
	/*Test estSymetrique*/
	cout1[1][1] = 0;
	cout1[2][2] = 0;
	cout1[3][3] = 0;
	cout1[4][4] = 0;
	cout1[5][5] = 0;
	cout1[1][2] = -1;
	cout1[2][1] = -1;
	cout1[2][4] = 6;
	cout1[4][2] = 6;
	cout1[3][4] = 2;
	cout1[4][3] = 2;
	cout1[4][4] = 8;
	
	cout<<"****Test estSymetrique****"<<endl;
	if(algo.estSymetrique(cout1)) cout<<"C'est symetrique"<<endl;
	cout1[5][5] = 6;
	if(algo.estSymetrique(cout1)) cout<<"C'est symetrique apres changer [5][5]"<<endl;
	cout1[3][5] = 10;
	if(!algo.estSymetrique(cout1)) cout<<"C'est asymetrique apres changer [3][5]"<<endl;
	
	algo.del_matrice(cout1);
	
	/*Test saisir*/
	algo.saisir(fp,app,poids);
	cout<<"****Test Saisir****"<<endl;
	cout<<"app : ["<<app[0];
	for(int i=1;i<=app[0];i++){
		cout<<","<<app[i];
	}
	cout<<"]"<<endl;
	cout<<"fp : ["<<fp[0];
	for(int i=1;i<=fp[0];i++){
		cout<<","<<fp[i];
	}
	cout<<"]"<<endl;
	cout<<"poids : ["<<poids[0];
	for(int i=1;i<=poids[0];i++){
		cout<<","<<poids[i];
	}
	cout<<"]"<<endl;
	
	algo.del_fs_aps_poids(fp,app,poids);	
			
	return 0;
}
