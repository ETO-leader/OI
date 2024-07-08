#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
using VI=vector<lint>;
int lowbit(int x){return x&-x;}
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n,m;cin>>n>>m;const int _sz=1<<n;
    vector<VI> G(n),D(n,VI(_sz));
    VI _lg(_sz);
    cir(i,0,m){
        int u,v;cin>>u>>v;--u,--v;
        G[u].push_back(v),G[v].push_back(u);
    }
    cir(i,0,n) D[i][1<<i]=1,_lg[1<<i]=i;
    lint ans=0;
    cir(s,1,_sz) cir(i,0,n) if((1<<i)&s){
        for(auto&u:G[i]){
            if(u==_lg[lowbit(s)]) ans+=D[i][s];
            else if(!(s&(1<<u))&&u>_lg[lowbit(s)])
                D[u][s+(1<<u)]+=D[i][s];
        }
    }
    cout<<(ans-m)/2<<'\n';
    return 0;
}