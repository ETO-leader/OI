#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using VI=vector<int>;
using func=function<int(int)>;
vector<VI> G,gapid;
vector<vector<VI>> dist;
const int _inf=1e9+7;
const int alp_siz=26;
int init(){
    int cnx=-1;
    gapid.assign(alp_siz,VI(alp_siz));
    dist.assign(alp_siz,
        vector<VI>(alp_siz));
    cir(i,0,alp_siz) cir(j,0,alp_siz)
        gapid[i][j]=(++cnx);
    return cnx;
}
void build_g(string&s,func id,func vid){
    const int n=s.size();
    G.resize(vid(n-1)+1);
    cir(i,0,n-1){
        G[id(i)].push_back(vid(i));
        G[vid(i)].push_back(id(i));
        G[id(i+1)].push_back(vid(i));
        G[vid(i)].push_back(id(i+1));
        const int gid=gapid[
            s[i]-'a'][s[i+1]-'a'];
        G[gid].push_back(id(i));
        G[id(i)].push_back(gid);
    }
}
auto bfs(int ux){
    const int n=G.size();
    VI D(n,_inf),vis(n);queue<int> q;
    q.push(ux);vis[ux]=true;D[ux]=0;
    while(!q.empty()){
        auto u=q.front();q.pop();
        for(auto&i:G[u]) if(!vis[i]){
            vis[i]=true;D[i]=D[u]+1;
            q.push(i);
        }
    }
    return D;
}
void init_sp(string&s,func id,func vid){
    build_g(s,id,vid);
    cir(i,0,alp_siz) cir(j,0,alp_siz)
        dist[i][j]=bfs(gapid[i][j]);
}
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    string s;cin>>s;
    const int n=s.size();
    const auto cnx=init()+1;
    auto id=[&](int x){return cnx+x;};
    auto vid=[&](int x){return cnx+n+x;};
    init_sp(s,id,vid);
    int q;cin>>q;
    while(q--){
        int u,v;cin>>u>>v;
        --u,--v;
        if(u>v) swap(u,v);
        int ans=(v-u)*2;
        cir(i,0,26) cir(j,0,26){
            ans=min(ans,dist[i][j][id(u)]
                +dist[i][j][id(v)]);
        }
        cout<<(ans/2)<<'\n';
    }
    return 0;
}
