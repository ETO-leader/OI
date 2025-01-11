#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
ifstream fcin("epilogue.in");
ofstream fcout("epilogue.out");
class fileio{
public:
    ~fileio(){
        fcin.close();fcout.close();
    }
} use_fileio;
int main(){
    ios::sync_with_stdio(false),fcin.tie(nullptr);
    int wx,n,m,x;fcin>>wx>>n>>m>>x;
    cir(i,0,n){
        int x,y;fcin>>x>>y;
    }
    vector<vector<pair<int,int>>> to(n);
    cir(i,0,m){
        int u,v,w;fcin>>u>>v>>w;--u;--v;
        to[u].emplace_back(v,w);
        to[v].emplace_back(u,w);
        clog<<u<<' '<<v<<' '<<w<<'\n';
    }
    auto ans=make_pair(0,10000000);
    cir(u,0,n){
        auto cnti=0;
        for(auto&[v,w]:to[u]) if(w<x){
            auto nw=w;
            auto pos=31;
            while(nw<x){
                while(nw&(1<<pos)) --pos;
                clog<<w<<' '<<nw<<": "<<x<<'\n';
                nw|=(1<<pos);++cnti;
            }
        }
        ans=min(ans,make_pair(u,cnti));
    }
    // const auto u=ans.first;
    // fcout<<to[u].size()<<'\n';
    // for(auto&[v,w]:to[u]){
    //     auto nw=w;
    //     auto pos=31;
    //     while(nw<x){
    //         while(nw&(1<<pos)) --pos;
    //         nw|=(1<<pos);
    //     }
    //     fcout<<u<<' '<<v<<' '<<nw<<'\n';
    // }
    return 0;
}
