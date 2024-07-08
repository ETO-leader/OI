#include<bits/stdc++.h>
#define cir(i,a,b) for(auto i=a;i<b;++i)
using namespace std;
template<typename T>
class base{
private:
    template<typename Ty>
    Ty nmax(){
        return numeric_limits<Ty>::max();
    }
    unsigned len;bool sign;
    vector<T> px;
public:
    base():len(nmax<T>()>nmax<unsigned>()?64:32){
        sign=(T)(1ULL<<len)!=(1ULL<<len);
        px.resize(len-sign);}
    void insert(T x){
        for(auto i=len-sign-1;~i;--i){
            if((!(x&(1ULL<<i)))) continue;
            if(!px[i]){px[i]=x;break;}
            x^=px[i];
        }
    }
    T operator()(T x){
        T res=x;
        for(auto i=len-sign-1;~i;--i)
            res=max(res,res^px[i]);
        return res;
    }
};
using ull=unsigned long long;
struct edge{ull v,w;};
vector<vector<edge>> G;
vector<bool> vis;
vector<ull> vx;
void roading(int u,ull val,base<ull>&vs){
    vx[u]=val;vis[u]=true;
    for(auto&i:G[u]){
        if(!vis[i.v]) roading(i.v,val^i.w,vs);
        else if(val^i.w^vx[i.v]) vs.insert(val^i.w^vx[i.v]);
    }
}
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n,m;cin>>n>>m;G.resize(n+1);
    vis.resize(n+1);vx.resize(n+1);
    base<ull> b;
    cir(i,0,m){
        ull u,v,w;cin>>u>>v>>w;
        G[u].push_back({v,w});G[v].push_back({u,w});
    }
    roading(1,0,b);
    cout<<b(vx[n])<<'\n';
    return 0;
}