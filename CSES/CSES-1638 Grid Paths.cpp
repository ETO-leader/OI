#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
const int MOD=1e9+7;
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n,st=0;cin>>n;
    vector<vector<int>> D(2,vector<int>(n)); 
    vector<string> mp(n);
    for(auto&i:mp) cin>>i;
    D[st][0]=(mp[0][0]=='.');
    cir(i,0,n){
        cir(j,0,n){
            if((!i)&&(!j)) continue;
            if(mp[i][j]=='*') D[st][j]=0;
            else D[st][j]=((j?D[st][j-1]:0)+D[st^1][j])%MOD;
        }
        st^=1;
    }
    cout<<D[st^1][n-1]<<'\n';
    return 0;
}