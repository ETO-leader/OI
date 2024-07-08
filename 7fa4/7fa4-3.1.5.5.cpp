#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
vector<int> D,Tp,V;
const int _inf=1e9+7;
struct edge_t{
    int u,v,w,p;
    bool operator<(const edge_t&e) const{
        return w==e.w?(u==e.u?(v==e.v?p>e.p:v>e.v):u>e.u):w>e.w;
    }
};
set<edge_t> Ews;vector<set<edge_t>> R;
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n,m;cin>>n>>m;D.resize(n+1,_inf);
    R.resize(n+1);Tp.resize(n+1);V.resize(n+1);
    cir(i,0,m){
        int u,v,w,p;cin>>u>>v>>w>>p;Ews.insert({v,u,w,p});
        R[v].insert({v,u,w,p});
        Tp[u]++;
    }
    queue<int> q;
    cir(i,1,n+1) if(!Tp[i]) q.push(i);
    while(!Ews.empty()){
        while(q.empty()){
            if(Ews.empty()) break;
            auto b=*Ews.begin();
            if(!(--Tp[b.v])) q.push(b.v);
            D[b.v]=min(D[b.v],b.w);R[b.u].erase({b.u,b.v,b.w,b.p});
            Ews.erase(b);
        }
        if(q.empty()) break;
        auto f=q.front();q.pop();
        for(auto&i:R[f]){
            D[i.v]=min(D[i.v],(D[f]==_inf?_inf:max(D[f]-i.p,i.w)));
            if(!(--Tp[i.v])) q.push(i.v);
            Ews.erase({i.u,i.v,i.w,i.p});
        }
        R[f].clear();
    }
    cir(i,1,n+1) cout<<(D[i]==_inf?-1:D[i])<<' ';
    cout<<'\n';
    return 0;
}