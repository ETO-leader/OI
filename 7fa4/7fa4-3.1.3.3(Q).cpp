#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
string st;
inline bool asa(char c){return c>='a'&&c<='z';}
inline bool asA(char c){return c>='A'&&c<='Z';}
unordered_map<char,vector<int>> ds;
void newd(int w){ds[st[w]].push_back(w);}
int nxtd(int w){
    auto&dw=ds[st[w]];
    return dw[0]==w?dw[1]:dw[0];
}
struct edge{int v,w;};
vector<vector<edge>> G,unjumpG;
void ad(int u,edge e){G[u].push_back(e);}
void build(int u,int v){
    bool adu=false,adv=false;
    if(asA(st[v])) ad(u,{nxtd(v),2}),ad(nxtd(v),{u,2});
    if(asA(st[u])) ad(v,{nxtd(u),2}),ad(nxtd(u),{v,2});
    ad(u,{v,1});
    ad(v,{u,1});
}
struct HeapNode{
    int v,w;
    inline bool operator<(const HeapNode&hp) const{
        return w>hp.w;
    }
};
const int _inf=1e9+7;
vector<int> dijkstra(int n,int u=1){
    priority_queue<HeapNode> pq;
    vector<int> D(n,_inf),vis(n);
    pq.push({u,0});D[u]=0;
    while(!pq.empty()){
        auto f=pq.top();pq.pop();
        if(vis[f.v]) continue;
        vis[f.v]=true;
        for(auto&i:G[f.v]){
            int iw=i.w,iv=i.v;
            if(asa(st[i.v])) ++iw,iv=nxtd(i.v);
            if(st[iv]=='#') ++iw;
            if((!vis[iv])&&D[iv]>f.w+iw){
                D[iv]=f.w+iw;
                pq.push({iv,f.w+iw});
            }
        }
    }
    return D;
}
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n,m;cin>>n>>m>>st;
    G.resize(n+1);st=' '+st;
    cir(i,1,n+1) if(isalpha(st[i])) newd(i);
    cir(i,0,m){
        int u,v;cin>>u>>v;
        build(u,v);
    }
    auto D=dijkstra(n+1);
    cir(i,1,n+1) cout<<(D[i]==_inf?-1:D[i])<<' ';
    cout<<'\n';
    return 0;
}