#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
namespace standardio{
    using lint=long long;
    const int BUFF=(1<<30)-1;
    int n,m,k,t,Abuff=0;
    void read_args(int&_n,int&_m,int&_k,int&_t){
        cin>>_n>>_m>>_k>>_t;
        n=_n;m=_m;k=_k;t=_t;
    }
    void read_line(int&p,int&u,int&v,lint&w){
        int ku,kv;cin>>p>>u>>v>>w>>ku>>kv;
        u=(u+(ku&Abuff)-1)%n+1;
        v=(v+(kv&Abuff)-1)%n+1;
    }
    void write_ans(int ans){
        cout<<ans<<'\n';
        Abuff=((Abuff<<1)|ans)&BUFF;
    }
}
template<typename T>
class valdset{
public:
    vector<int> F;vector<T> V,Al_gcd;
    pair<int,T> _findset(int x){
        if(x==F[x]) return {x,V[x]};
        auto f=_findset(F[x]);
        V[x]+=f.second;F[x]=f.first;
        return {f.first,V[x]};
    }
    T modifine(T x,T p){return p?((x%p+p)%p):x;}
public:
    int findset(int x){return _findset(x).first;}
    T node_dis(int x,int y){findset(x);findset(y);return V[x]-V[y];}
    void merge(int x,int y,T v){
        findset(x);findset(y);
        assert(findset(x)!=findset(y));
        if(Al_gcd[findset(x)]&&Al_gcd[findset(y)])
            Al_gcd[findset(y)]=
                __gcd(Al_gcd[findset(x)],Al_gcd[findset(y)]);
        else if(Al_gcd[findset(x)]) Al_gcd[findset(y)]=Al_gcd[findset(x)];
        int fx=findset(x);
        V[findset(x)]=v+V[y]-V[x];F[fx]=findset(y);
    }
    void calc(int x,int y,T Ev){
        findset(x);findset(y);
        assert(findset(x)==findset(y));
        T&al_gcd=Al_gcd[findset(x)];
        if(!(node_dis(y,x)+Ev)) return;
        if(!al_gcd) al_gcd=abs(node_dis(y,x)+Ev);
        al_gcd=__gcd(al_gcd,abs(node_dis(y,x)+Ev));
    }
    bool can_move(int u,int v,T w){
        findset(u);findset(v);
        if(findset(u)!=findset(v)) return false;
        T&al_gcd=Al_gcd[findset(u)];
        T nd=node_dis(u,v);
        return modifine(w,al_gcd)==modifine(nd,al_gcd);
    }
    valdset(int _n):V(_n),F(_n),Al_gcd(_n){
        iota(F.begin(),F.end(),0);
    }
};
using lint=standardio::lint;
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n,m,k,t;
    standardio::read_args(n,m,k,t);
    valdset<lint> vds(n+1);
    cir(i,0,m){
        int op,u,v;lint w;
        standardio::read_line(op,u,v,w);
        if(op){
            standardio::write_ans(vds.can_move(u,v,w));
        }else{
            if(vds.findset(u)==vds.findset(v))
                vds.calc(u,v,w);
            else vds.merge(v,u,-w);
        }
    }
    return 0;
}