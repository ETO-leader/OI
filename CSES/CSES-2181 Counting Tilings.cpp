#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
const int MOD=1e9+7;
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n,m;cin>>n>>m;const int _sz=1<<n;
    vector<vector<int>> D(2,vector<int>(_sz));
    int st=0;D[st][0]=1;
    cir(i,0,m) cir(j,0,n){
        st^=1;fill(D[st].begin(),D[st].end(),0);
        cir(s,0,_sz){
            (D[st][s^(1<<j)]+=D[st^1][s])%=MOD;
            if(j!=n-1&&(!((s>>j)&3)))
                (D[st][s^(1<<(j+1))]+=D[st^1][s])%=MOD;
        }
    }
    cout<<D[st][0]<<'\n';
    return 0;
}