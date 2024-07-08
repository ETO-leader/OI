#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
const int MOD=1e9+7;
int N,M;vector<int> v;
vector<vector<int>> D;
int dfs(int n,int k){
    int&d=D[n][k];
    if(d!=-1) return d;
    if(n==N-1) return d=((!v[n])||(k==v[n]));
    d=0;
    if(v[n]&&v[n]!=k) return d;
    cir(i,max(1,k-1),min(M,k+1)+1) (d+=dfs(n+1,i))%=MOD;
    return d;
}
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    cin>>N>>M;v.resize(N);
    D.assign(N,vector<int>(M+1,-1));
    for(auto&i:v) cin>>i;
    int ans=0;
    cir(i,1,M+1) (ans+=dfs(0,i))%=MOD;
    cout<<ans<<endl;
    return 0;
}