#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
vector<vector<lint>> D;
const int MOD=1e9+7;
lint dfs(int f,int s){
    auto&d=D[f][s];
    if(~d) return d;
    if(f==1) return (d=1);
    return (d=(s?2*dfs(f-1,1)+dfs(f-1,0):
        dfs(f-1,1)+4*dfs(f-1,0)))%=MOD;
}
const int NN=1e6+7;
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int T,n;cin>>T;D.assign(NN,vector<lint>(2,-1));
    while(T--){
        cin>>n,cout<<(dfs(n,1)+dfs(n,0))%MOD<<'\n';
    }
    return 0;
}