#include<bits/stdc++.h>
#include<bits/extc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace __gnu_pbds;
using namespace std;
template<typename T,class comp=less<T>>
using heap=__gnu_pbds::priority_queue<
    T,comp,pairing_heap_tag>;
using lint=long long;
namespace run{
    vector<vector<int>> G;
    vector<lint> L,W;
    vector<heap<lint>> hpns;
    lint ans=0;
    lint dfs(int u,lint p){
        int resx=W[u];hpns[u].push(W[u]);
        for(auto&i:G[u]){
            resx+=dfs(i,p);
            hpns[u].join(hpns[i]);
            while(resx>p) 
                resx-=hpns[u].top(),hpns[u].pop();
        }
        ans=max<lint>(ans,hpns[u].size()*L[u]);
        return resx;
    }
}
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n,m;cin>>n>>m;run::G.resize(n+1);
    run::hpns.resize(n+1);run::L.resize(n+1);
    run::W.resize(n+1);
    cir(i,1,n+1){
        int f;cin>>f>>run::W[i]>>run::L[i];
        run::G[f].push_back(i);
    }
    run::dfs(0,m);
    cout<<run::ans<<'\n';
    return 0;
}
