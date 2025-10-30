#include<bits/stdc++.h>
#define cir(i,a,b) for(auto i=a;i<b;++i)
using namespace std;
class dsu{
private:
    const int n;
    vector<int> f,w,g;
    int64_t ans;
public:
    auto findset(int u)->int{
        if(u==f[u]) return u;
        const auto res=findset(f[u]);
        (w[u]+=w[f[u]])%=n;
        return f[u]=res;
    }
    auto merge(int u,int v,int x){
        const auto ux=u,vx=v;
        u=findset(u);v=findset(v);
        if(u!=v){
            ans-=gcd(g[u],n)+gcd(g[v],n);
            f[u]=v;
            w[u]=(w[vx]-w[ux]+x+n)%n;
            g[v]=gcd(g[u],g[v]);
            ans+=gcd(n,g[v]);
        }else{
            ans-=gcd(n,g[u]);
            g[u]=gcd(g[u],(w[vx]-w[ux]+x+n)%n);
            ans+=gcd(n,g[u]);
        }
    }
    auto getans(){return ans;}
    dsu(int _n):n(_n),f(n),w(n),g(n),ans((int64_t)(n)*n){iota(f.begin(),f.end(),0);}
};
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int n,q;cin>>n>>q;
    dsu qwq(n);
    cir(i,0,q){
        int a,b,c,d;cin>>a>>b>>c>>d;
        qwq.merge((b-a+n)%n,(d-c+n)%n,(c-a+n)%n);
        cout<<qwq.getans()<<'\n';
    }
    return 0;
}
