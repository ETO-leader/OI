#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using VI=vector<int>;
const int _inf=1e9+7;
template<typename T>
ostream&operator<<(ostream&os,vector<T> v){
    for(auto&i:v) os<<i<<' ';
    return os;
}
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n,m;cin>>n>>m;VI lt(n),sx(n);
    vector<VI> cst(n,VI(n));
    const int fullset=(1<<n)-1,_sz=(1<<n);
    cir(i,0,m){
        int u,v,w;cin>>u>>v>>w;--u,--v;
        lt[v]|=(1<<u);cst[v][u]+=w;
        sx[u]|=(1<<v);
    }
    VI D(_sz,_inf),F(_sz);
    VI fx(_sz),wx(_sz);
    cir(s,0,_sz){
        cir(i,0,n) if(s&(1<<i)){
            fx[s]|=sx[i];
            cir(j,0,n) if(lt[i]&(1<<j)&&(!(s&(1<<j))))
                wx[s]+=cst[i][j];
        }
    }
    cir(s,0,_sz) if(!fx[s]) D[s]=0;
    cir(s,0,_sz){
        const int cs=fullset^s;
        for(int sx=cs;sx;sx=((sx-1)&cs)){
            if((fx[sx]|s)!=s) continue;
            if(D[s]+wx[s]>=D[sx|s]) continue;
            D[sx|s]=D[s]+wx[s];F[sx|s]=s;
        }
    }
    cout<<[&](){
        VI res(n);
        function<void(int,int)> f=[&](int p,int s){
            auto sx=s^F[s];
            cir(i,0,n) if(sx&(1<<i))
                res[i]=114514-p;    
            if(F[s]) f(p+1,F[s]);
        };
        f(0,_sz-1);
        return res;
    }()<<'\n';
    return 0;
}
