#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
using state=bitset<5007>;
vector<state> st;
vector<lint> D,p;
vector<bool> vis;
lint dfs(int k){
    if(vis[k]) return D[k];
    vis[k]=true;D[k]=p[k];
    cir(i,0,D.size()) if(st[k][i])
        D[k]=max(dfs(i)+p[k],D[k]);
    return D[k];
}
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n,m;cin>>n>>m;p.resize(m);
    st.resize(m);vis.resize(m);D.resize(m);
    for(auto&i:p) cin>>i;
    for(auto&i:st) i.set();
    cir(i,0,n){
        map<int,vector<int>> pwi;
        cir(i,0,m){
            int w;cin>>w;
            pwi[w].push_back(i);
        }
        state sti;
        for(auto&[a,b]:pwi){
            for(auto&i:b) st[i]&=sti;
            for(auto&i:b) sti.set(i,true);
        }
    }
    cir(i,0,m) dfs(i);
    cout<<*max_element(D.begin(),D.end())<<'\n';
    return 0;
}
