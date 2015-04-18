#include "Algorithme.h"
#include <iostream>
#include <vector>
#include <climits>

using namespace std;
using namespace algo_ns;

void Algorithme::chemin_critiques(int *fp,int *app,int *poids,int *&fpc, int *&appc,int *&lc){
	int n = app[0];
	int kc=1,k,j,lg;
	appc = new int[n+1]; appc[0] = n;
	lc = new int[n+1]; lc[0] = n;
	fpc = new int[fp[0]+1]; fpc[0] = fp[0];
	
	fpc[1] = 0;
	for(int i=1;i<=n;i++) lc[i] = -1;
	lc[1] = 0;
	for(int i=2;i<=n;i++){
		k = app[i]; appc[i] = kc+1;
		while(j=fp[k]!=0){
			lg = lc[j] + poids[k];
			if(lg>=lc[i]){
				if(lg>lc[i]){
					lc[i] = lg;
					kc = appc[i];
					fpc[kc] = j;
				}
				else{
					kc++;
					fpc[kc] = k;
				}
			}
			k++;
		}
		kc++;
		fpc[kc] = 0;		
	}
	fpc[0] = kc;
}

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
	pred[s] = 0; 
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
	delete [] b;
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
				for(int j=k;j<(X.size()-1);j++){
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
	int k,min_k,l=0;
	long min;
	arete a;
	while(l<(n-1)){
		min = INT_MAX;
		k=0;		
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
		for(int i=min_k;i<(aretes.size()-1);i++){
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
		a[i][i] = 0;
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
		a[i][i] = 0;
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

void Algorithme::saisir(int *&fs,int *&aps,int *&poids){
	int n,**a;
	cout<<"Nombre de sommets : ";
	while((cin>>n)==NULL){
		cin.clear();
		cin.ignore();
		cout<<endl;
		cout<<"Saisir un entier : ";
	}
	if(n<1) return;
	a = new int*[n+1];
	a[0] = new int[2];
	for(int i=1;i<=n;i++) a[i] = new int[n+1];
	a[0][0] = n;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++)
			a[i][j] = INT_MAX;
		a[i][i] = 0;	
		
	}
	int s,t,poid;
	char c;
	bool correct_input = true;
	int k = 0;
	while(correct_input){
		cout<<"Saisir un arc avec 2 sommets "<<endl;
		cout<<"Sommet depart : ";
		cin>>s;
		cout<<"Somme destination : ";
		cin>>t;
		cout<<"Cout : ";
		cin>>poid;
		cout<<endl;
		if(!s||!t||s==t||s<1||t<1||s>n||t>n){
			cout<<"ERREUR!"<<endl;
			cin.clear();
			cin.ignore();
			correct_input = false;	
		}		
		if(correct_input){
			a[s][t] = poid;	
			k++;
	    }
	    cout<<"Continuer?(y/n) ";
	    cin>>c;
	    if(c=='y') correct_input = true;
	    else correct_input = false;	    
	}
	a[0][1] = k;
	cout<<endl;
	matrix2all(a,fs,aps,poids);
	
	del_matrice(a);
}
