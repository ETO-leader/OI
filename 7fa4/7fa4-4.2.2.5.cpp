#include<bits/stdc++.h>
#pragma GCC optimize("Ofast")
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
vector<lint> pr;
void initpr(int n){
    vector<bool> isp(n,true);
    cir(i,2,n){
        if(!isp[i]) continue;
        for(int j=i*2;j<n;j+=i) isp[j]=false;
        pr.push_back(i);
    } 
}
vector<lint> unperp;
void calcunp(lint w,lint adk,lint mx){
    lint cnx=mx/w;
    for(lint x=w;x<unperp.size();x+=w)
        unperp[x]+=cnx*adk;
}
void dfs(lint mx,lint mxk,lint l=1,
    bool tx=0,int pos=0,bool chtag=false){
    if(chtag) calcunp(l,tx?1:-1,mxk);
    if(l*pr[pos]>mx||pos>=pr.size()) return;
    dfs(mx,mxk,l*pr[pos],tx^1,pos+1,true);
    dfs(mx,mxk,l,tx,pos+1,false);
}
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    lint n,m;cin>>n>>m;initpr(n+1);
    unperp.resize(n+1);dfs(n,m);
    cir(i,1,n+1) cout<<m-unperp[i]<<'\n';
    return 0;
}
