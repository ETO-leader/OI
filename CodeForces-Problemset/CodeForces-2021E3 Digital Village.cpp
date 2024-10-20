#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
class dsu{
private:
    vector<int> f;
public:
    auto findset(int u)->int{
        return f[u]==u?u:(f[u]=findset(f[u]));
    }
    auto setfath(int u,int nf){
        f[findset(u)]=findset(nf);
    }
    dsu(int _n):f(_n){ranges::iota(f,0);}
};
class tree{
private:
    vector<int> ls,rs,fx;
    vector<lint> sum,val,rk,dep;
    vector<pair<lint,lint>> f;
    auto dfs(int u,lint w,const int n){
        const auto wx=sum[u]*(val[u]-(fx[u]>-1?val[fx[u]]:0));
        dep[u]=(w+=wx);
        if(u<n) return f[u]={wx,u},rk[u]=wx,void();
        for(auto v:{ls[u],rs[u]}) dfs(v,w,n);
        f[u]=min(f[ls[u]],f[rs[u]]);
        f[u].first+=wx;
        rk[f[u].second]=dep[f[u].second]-(fx[u]>-1?dep[fx[u]]:0);
    }
    auto krt(vector<tuple<lint,int,int>> es,const int n){
        ranges::sort(es);
        dsu ds(n*2-1);
        for(auto x:{&ls,&rs,&fx}) x->resize(n*2-1);
        for(auto x:{&val,&dep}) x->resize(n*2-1);
        ranges::fill(fx,-1);
        f.resize(n*2-1);rk.resize(n);
        auto cnt=n-1;
        for(auto[w,u,v]:es){
            u=ds.findset(u);v=ds.findset(v);
            if(u==v) continue;
            ++cnt;
            ds.setfath(u,cnt);ds.setfath(v,cnt);
            ls[cnt]=u;rs[cnt]=v;
            sum[cnt]=sum[ls[cnt]]+sum[rs[cnt]];
            fx[u]=fx[v]=cnt;
            val[cnt]=w;
        }
    }
public:
    auto solve(vector<tuple<lint,int,int>> es,vector<int> imp,const int n){
        sum.resize(n*2-1);
        for(auto&i:imp) sum[i]=1;
        krt(es,n);
        dfs(n*2-2,0,n);
        ranges::sort(rk);
        ranges::rotate(rk,prev(rk.end()));
        vector<lint> ans;
        cir(i,0,n) ans.push_back((rk[i]+=(i?rk[i-1]:0)));
        return ans;
    }
};
int main(){
    int T;cin>>T;
    while(T--) [&](){
        int n,m,c;cin>>n>>m>>c;
        vector<int> imp(c);
        for(auto&i:imp) cin>>i,--i;
        vector<tuple<lint,int,int>> es(m);
        for(auto&[w,u,v]:es) cin>>u>>v>>w,--u,--v;
        const auto ans=tree().solve(es,imp,n);
        for(auto&i:ans) print("{} ",i);
        println("");
    }();
}
