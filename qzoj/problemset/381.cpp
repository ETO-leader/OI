#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
static constexpr auto MOD=1234567;
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int n,m,k;cin>>n>>m>>k;
    vector<vector<int>> ban(n,vector<int>(m));
    cir(i,0,k){
        int x,y;cin>>x>>y;--x;--y;
        ban[x][y]=true;
    }
    vector<int64_t> f(1<<n);
    f[0]=1;
    cir(i,0,m){
        for(auto s=(1<<n)-1;~s;--s) cir(p,0,n) if((!(s&(1<<p)))&&(!ban[p][i])) (f[s|(1<<p)]+=f[s])%=MOD;
    }
    cout<<f[(1<<n)-1]<<'\n';
    return 0;
}
