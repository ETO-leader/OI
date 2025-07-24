#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
static constexpr auto MOD=998244353;
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int T;cin>>T;
    while(T--) []{
        int n,m;cin>>n>>m;
        vector banup(n,vector<int>(n));
        vector uppos(n,vector(n,n));
        cir(i,0,m){
            int p,w;cin>>p>>w;--p;--w;
            auto x=p,v=w;
            while(x<n&&v<n) banup[x][v]=true,++x,++v;
            x=p,v=w;
            while(x>-1&&v>-1) uppos[x][v]=min(uppos[x][v],p),--x,--v;
        }
        vector<lint> f(n+1),sg(n+1),pre(n);
        vector g(n+1,vector<lint>(n)),tag(n+1,vector<lint>(n));
        f[0]=1;
        cir(i,1,n+1) cir(w,0,i) if(!banup[i-1][w]){
            pre[w]+=tag[i][w];
            (g[i][w]+=f[i-w-1]+sg[i-w-1])%=MOD;
            (sg[i]+=f[i-w-1]+sg[i-w-1])%=MOD;
            if(w+1<n) for(auto p=i-w-2;~p;--p) if(uppos[p][w+1]>i-w-2) (f[i]+=(f[p]+sg[p]+MOD-g[p][w]))%=MOD;
            clog<<i<<": "<<f[i]<<' '<<sg[i]<<'\n';
        }
        cout<<(f[n]+sg[n])%MOD<<'\n';
    }();
    return 0;
}
