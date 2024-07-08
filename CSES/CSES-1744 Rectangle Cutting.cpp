#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
vector<vector<int>> D;
const int _inf=1e9+7;
int dp(int x,int y){
    int&d=D[x][y];
    if(d!=_inf) return d;
    if(x==y) return d=0;
    cir(i,1,x) d=min(d,dp(x-i,y)+dp(i,y)+1);
    cir(i,1,y) d=min(d,dp(x,y-i)+dp(x,i)+1);
    return d;
}
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n,m;cin>>n>>m;
    D.assign(n+1,vector<int>(m+1,_inf));
    cout<<dp(n,m)<<'\n';
    return 0;
}