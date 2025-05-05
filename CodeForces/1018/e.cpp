#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
static constexpr auto _infl=(lint)(1e18l);
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int T;cin>>T;
    while(T--) [&]{
        int n;cin>>n;
        string s;cin>>s;
        vector<int> p;
        cir(i,0,n) if(s[i]=='B') p.emplace_back(i);
        const auto k=(int)(p.size());
        if(!k) return cout<<0<<'\n',void();
        vector f(k,vector<lint>(2,_infl));
        vector<int> dis(k);
        cir(i,0,k) dis[i]=p[i]-i;
        f[0][0]=(dis[0]+1)/2;
        f[0][1]=dis[0];
        vector<int> nxt(n);
        auto w=n-1;
        for(auto i=n-1;~i;--i){
            if(s[i]=='P') w=i-1;
            nxt[i]=w;
        }
        cir(i,0,k-1){
            f[i+1][0]=min(f[i+1][0],f[i][0]+(dis[i+1]+1)/2);
            f[i+1][0]=min(f[i+1][0],f[i][1]+(dis[i+1]-dis[i]+1)/2);
            f[i+1][1]=min(f[i+1][1],f[i][0]+dis[i+1]);
        }
        cir(i,0,k) clog<<f[i][0]<<' '<<f[i][1]<<'\n';
        cout<<f[k-1][0]<<'\n';
    }();
    return 0;
}
