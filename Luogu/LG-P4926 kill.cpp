#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using db=long double;
struct edge{int v;db w;};
vector<vector<edge>> G;
const db _inf=1e18+7;
bool spfa(int k){
    queue<int> q;q.push(k);
    vector<db> D(G.size(),_inf),inq(G.size());
    vector<db> ins(G.size());
    D[k]=0;inq[k]=true;ins[k]++;
    while(!q.empty()){
        int u=q.front();q.pop();
        inq[u]=false;
        for(auto&[v,w]:G[u]){
            if(w+D[u]<D[v]){
                D[v]=D[u]+w;
                if(!inq[v]) q.push(v);
                inq[v]=true;
                if((++ins[v])>=G.size())
                    return false;
            }
        }
    }
    return true;
}
struct edge_t{int tp,u,v;db w;};
vector<edge_t> es;
struct egs{int p;db w;};
vector<egs> known;
void build(db t){
    for(auto&i:G) i.clear();
    for(auto&i:known){
        G[0].push_back({i.p,-log2(i.w)});
        G[i.p].push_back({0,log2(i.w)});
    }
    for(auto&i:es){
        auto lgx=(i.tp==1?
            -log2(i.w-t):log2(i.w+t));
        G[i.v].push_back({i.u,lgx});
    }
    int nx=G.size()-1;
    cir(i,0,nx) G[nx].push_back({i,0});
}
istream&operator>>(istream&is,edge_t&e){
    return is>>e.tp>>e.u>>e.v>>e.w;
}
istream&operator>>(istream&is,egs&e){
    return is>>e.p>>e.w;
}
const db mxt=1e9+7;
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n,m,c;cin>>n>>m>>c;G.resize(n+2);
    es.resize(m);known.resize(c);
    for(auto&i:es) cin>>i;
    for(auto&i:known) cin>>i;
    build(0);
    if(spfa(n+1)){
        cout<<"-1\n";exit(0);}
    db l=0,r=mxt;
    build(4);
    cir(i,0,100){
        db mid=(l+r)/2;
        build(mid);
        spfa(n+1)?r=mid:l=mid;
    }
    cout<<fixed<<setprecision(13)
        <<(l+r)/2<<'\n';
    return 0;
}
