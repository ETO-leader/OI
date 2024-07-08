#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
vector<vector<int>> G,UP;
int HT;vector<int> li,D,H;
void dfs(int u,int f=1){
    UP[u][0]=f;H[u]=H[f]+1;
    cir(i,1,HT) UP[u][i]=UP[UP[u][i-1]][i-1];
    for(auto&i:G[u]) if(i!=f) dfs(i,u);
}
int getfath(int u,int k){
    cir(i,0,HT) if(k&(1<<i)) u=UP[u][i];
    return u;
}
vector<pair<int,int>> st;
void dp(int u,int f=1){
    if(u!=1){
        D[u]=D[(lower_bound(st.begin(),st.end(),
            make_pair(H[getfath(u,li[u])],-1))->second)]+1;
    }
    vector<pair<int,int>> tp;
    while((!st.empty())&&D[st.back().second]>=D[u])
        tp.push_back(st.back()),st.pop_back();
    st.push_back({H[u],u});
    for(auto&i:G[u]) if(i!=f) dp(i,u);
    st.pop_back();
    while(!tp.empty()) st.push_back(tp.back()),tp.pop_back();
}
const int _inf=1e9+7;
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n;cin>>n;G.resize(n+1);H.resize(n+1);
    HT=log2(n)+2;UP.assign(n+1,vector<int>(HT));
    li.resize(n+1);D.resize(n+1);
    cir(i,2,n+1){
        int f;cin>>f>>li[i];
        G[i].push_back(f);G[f].push_back(i);
    }
    dfs(1);dp(1);
    cir(i,1,n+1) cout<<D[i]<<'\n';
    return 0;
}