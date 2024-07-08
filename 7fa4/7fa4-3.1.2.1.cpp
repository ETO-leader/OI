#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
vector<priority_queue<int,vector<int>,greater<int>>> G;
vector<int> ansx,inx,oux;
void dfs(int u){
    while(!G[u].empty()){
        auto f=G[u].top();G[u].pop();
        dfs(f);
    }
    ansx.push_back(u);
}
void inpg(int m){
    cir(i,0,m){
        int u,v;cin>>u>>v;G[u].push(v);
        inx[v]++;oux[u]++;
    }
}
void impossible(){cout<<"No Solution\n";exit(0);}
int chk(int n){
    int l1=0,r1=0,u=0;
    cir(i,1,n+1){
        if(abs(inx[i]-oux[i])>1) impossible();
        l1+=(inx[i]>oux[i]);r1+=(inx[i]<oux[i]);
        if(l1>1||r1>1) impossible();
        if(inx[i]<oux[i]) u=i;
    }
    return u+(!u);
}
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n,m;cin>>n>>m;G.resize(n+1);
    inx.resize(n+1);oux.resize(n+1);
    inpg(m);auto u=chk(n);
    dfs(u);reverse(ansx.begin(),ansx.end());
    for(auto&i:ansx) cout<<i<<' ';cout<<'\n';
    return 0;
}
