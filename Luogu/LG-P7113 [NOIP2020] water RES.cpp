#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
typedef __int128 __int;
ostream&operator<<(ostream&os,__int x){
    if(x>9) os<<(x/10);
    return (os<<(int)(x%10));
}
struct frac{
    __int p,q;
    frac(__int _p=0,__int _q=1):p(_p),q(_q){
        auto g=__gcd(p,q);p/=g;q/=g;
    }
    frac operator+(frac f){return frac(p*f.q+f.p*q,q*f.q);}
    frac operator/(__int x){return frac(p,q*x);}
};
ostream&operator<<(ostream&os,frac f){
    return (os<<f.p<<' '<<f.q);
}
vector<vector<int>> G;
vector<frac> frc;
void add(int u,frac f){
    if(G[u].empty()) return;
    auto fi=f/G[u].size();
    for(auto&i:G[u]){
        frc[i]=frc[i]+fi;
        add(i,fi);
    }
}
int main(){
	ios::sync_with_stdio(false),cin.tie(0);
	int n,m;cin>>n>>m;G.resize(n+1);
    frc.resize(n+1);
    cir(i,1,n+1){
        int k,f;cin>>k;
        while(k--) cin>>f,G[i].push_back(f);
    }
    cir(i,1,m+1) frc[i]=frc[i]+frac(1,1),add(i,frac(1,1));
    cir(i,1,n+1) if(G[i].empty()) cout<<frc[i]<<endl;
	return 0;
}