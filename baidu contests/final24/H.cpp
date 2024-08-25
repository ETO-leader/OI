#pragma GCC optimize("Ofast")
#pragma GCC optimize("inline")
#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using lint=long long;
using namespace std;
class tree{
private:
    vector<vector<tuple<int,lint,int>>> gr;
    vector<int> fr,vis,ban,fid;
    int eidc;
    auto dfs(int u,lint fw=0,int f=-1)->pair<lint,int>{
        fr[u]=f;vis[u]=true;
        auto res=pair(0ll,u);
        for(auto&[i,w,id]:gr[u]) if((!ban[id])&&i!=f) res=max(res,dfs(i,w,u)),fid[i]=id;
        res.first+=fw;
        return res;
    }
public:
    auto insert(int u,int v,lint w){
        gr[u].emplace_back(v,w,eidc);
        gr[v].emplace_back(u,w,eidc);
        ++eidc;
    }
    auto check(){
        fill(vis.begin(),vis.end(),false);
        auto mx=-1ll;auto ans=pair(0,0);
        cir(i,0,(int)(gr.size())) if(!vis[i]){
            const auto[dis,u]=dfs(i);
            const auto[adix,v]=dfs(u);
            if(adix>mx){
                mx=adix;ans=pair(u,v);
            }
        }
        return pair(mx,ans);
    }
    auto route(int u,int v){
        vector<int> eid;
        while(v!=u){
            eid.push_back(fid[v]);
            v=fr[v];
        }
        return eid;
    }
    auto banedge(int id){ban[id]=true;}
    tree(int _n):gr(_n),fr(_n),vis(_n),ban(_n),fid(_n),eidc(0){}
};
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n,k;cin>>n>>k;tree gr(n);
    auto ans=0ll;
    cir(i,0,n-1){
        int u,v;lint w;cin>>u>>v>>w;--u;--v;
        gr.insert(u,v,w);ans+=w*2;
    }
    vector<lint> cks(k);
    for(auto&i:cks) cin>>i;
    sort(cks.begin(),cks.end(),greater<lint>());
    cir(i,0,k){
        auto[mx,es]=gr.check();
        if(mx<cks.back()+1) break;
        ans+=cks.back()-mx;
        cks.pop_back();
        const auto bid=gr.route(es.first,es.second);
        for(auto&e:bid) gr.banedge(e);
    }
    cout<<ans<<'\n';
    return 0;
}
