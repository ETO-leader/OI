#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
ifstream inf("three.in");
ofstream ouf("three.out");
int main(){
    ios::sync_with_stdio(false),inf.tie(nullptr);
    int n,m,d;inf>>n>>m>>d;
    vector<vector<int>> gr(n);
    cir(i,0,m){
        int u,v;inf>>u>>v;--u;--v;
        gr[u].emplace_back(v);
        gr[v].emplace_back(u);
    }
    for(auto&x:gr){
        sort(x.begin(),x.end(),[&](auto u,auto v){
            return gr[u].size()==gr[v].size()?u>v:gr[u].size()>gr[v].size();
        });
    }
    auto ngr=gr;
    vector<int> ord(n);
    iota(ord.begin(),ord.end(),0);
    sort(ord.begin(),ord.end(),[&](auto u,auto v){
        return gr[u].size()>gr[v].size();
    });
    auto ans=0ll;
    vector<int> vis(n);
    for(auto&u:ord){
        for(auto&v:gr[u]) vis[v]=true;
        for(auto&v:gr[u]){
            if(gr[v].size()<gr[u].size()||(gr[v].size()==gr[u].size()&&v<u)) break;
            if(abs(v-u)>d) continue;
            for(auto w:gr[v]){
                if(gr[w].size()<gr[v].size()||(gr[w].size()==gr[v].size()&&v<u)) break;
                if(max({u,v,w})-min({u,v,w})>d) continue;
                ans-=vis[w]*2;
            }
        }
        for(auto&v:gr[u]) vis[v]=false;
    }
    for(auto u=-1;auto&x:gr){
        ++u;
        sort(x.begin(),x.end());
        auto r=-1;
        cir(l,0,(int)(x.size())){
            if(r<l-1) ++r;
            if(abs(u-x[l])>d) continue;
            while(r+1<(int)(x.size())&&abs(u-x[r+1])<d+1&&abs(x[l]-x[r+1])<d+1) ++r;
            ans+=r-l;
        }
    }
    ouf<<ans<<'\n';
    return 0;
}
