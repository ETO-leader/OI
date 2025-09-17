#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N=1000000;
const int INF=2.1e9;
int vb[60],vk[60],sz,K,M,d[1000050],F[22][1000008],Maxlen[1000050],T,Q,L[1050],V[10200];
bool canvis[55];
struct D {
	int X,C;
} p[55];
int calc[55][22];
inline double slope(int p1,int p2) {
	return (vb[p2]-vb[p1])*1./(vk[p1]-vk[p2]);
}
inline void insert(int K,int B) {
	while(sz&&vk[sz]==K)if(vb[sz]>B)sz--;
		else return;
	vb[sz+1]=B;
	vk[sz+1]=K;
	while(sz>1&&slope(sz,sz-1)>slope(sz,sz+1))swap(vk[sz],vk[sz+1]),swap(vb[sz],vb[sz+1]),sz--;
	sz++;
}
inline ll solve(int x,int y) {
	if(y%x!=0)return -M;
	memset(canvis,0,sizeof(canvis));
	int c=y/x;
	ll sum=0;
	sz=0;
	for(int i=1; i<=T; ++i)
		if(y%p[i].X==0&&p[i].X%x==0) {
			canvis[i]=1;
			int c1=y/p[i].X,c2=p[i].X/x,Min=1e9;
			for(int len1=0; len1<=Maxlen[c1]; ++len1)
				for(int len2=0; len2<=Maxlen[c2]&&len1+len2<=20; ++len2)
					calc[i][len1+len2]=min(calc[i][len1+len2],F[len1][c1]+F[len2][c2]-(len1+len2)*p[i].C);
			for(int j=1; j<=20; ++j)
				calc[i][j]=min(calc[i][j],calc[i][j-1]);
			Min=calc[i][20];
			insert(p[i].C,Min);
		}
	for(int i=1,k=0,v,ans=0; i<=M; ++i) {
		v=L[i];
		if(v<=20) {
			ans=F[v][c];
			for(int j=1; j<=T; ++j)
				if(canvis[j])
					ans=min(ans,calc[j][v]+v*p[j].C);
			if(ans>1e9)ans=-1;
		}
		else {
			if(!sz)ans=-1;
			else {
				while(k<sz&&slope(k,k+1)<=L[i])++k;
				ans=vk[k]*L[i]+vb[k];
			}
		}
		sum+=ans;
	}
	for(int i=1; i<=T; ++i)
		if(canvis[i])
			memset(calc[i],63,sizeof(calc[i]));
	return sum;
}
bitset<1000010> B1,B2;
void init() {
	memset(F,63,sizeof(F));
	Maxlen[0]=0;
	F[0][1]=0;
	memset(calc,63,sizeof(calc));
	for(int i=1; i<=N; ++i) {
		for(int j=i; j<=N; j+=i)
			d[j]++;
		d[i]=V[d[i]];
	}
	int tot=0,ccc=0;
	for(int i=2; i<=N; ++i)F[1][i]=d[i],Maxlen[i]=1;
	B1.set();
	for(int c=1; c<20; ++c) {
		int *D1=F[c],*D2=F[c+1];
		for(int i=B1._Find_next(0); i<=N; i=B1._Find_next(i)) {
			for(int j=(i<<1),c=2,C=D1[i]; j<=N; j+=i,++c)
				D2[j]=min(D2[j],C+d[c]),B2[j]=1,tot++;
			Maxlen[i]=c;
		}
		B1=B2;
		B2.reset();
	}
}
inline bool cmp(D x,D y) {
	return x.C>y.C;
}
int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin>>K;
	for(int i=1; i<=K; ++i)
		cin>>V[i];
	init();
	cin>>M;
	for(int i=1; i<=M; ++i)
		cin>>L[i];
	sort(L+1,L+M+1);
	cin>>T;
	for(int i=1; i<=T; ++i)
		cin>>p[i].X>>p[i].C;
	sort(p+1,p+T+1,cmp);
	cin>>Q;
	while(Q--) {
		int x,y;
		cin>>x>>y;
		cout<<solve(y,x)<<'\n';
	}
}