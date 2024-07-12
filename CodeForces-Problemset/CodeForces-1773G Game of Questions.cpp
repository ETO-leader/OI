#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lf=long double;
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int n,m;cin>>n>>m;
    vector<vector<pair<int,int>>> g(1<<m);
    cir(s,0,(1<<m)){
        const auto len=1<<popcount((unsigned)(s));
        g[s].reserve(len);
        for(auto x=s;x;x=(x-1)&s) g[s].push_back({x,0});
        g[s].push_back({0,0});
        reverse(g[s].begin(),g[s].end());
    }
    cir(i,0,n){
        string s;cin>>s;
        auto x=0;
        reverse(s.begin(),s.end());
        for(auto&i:s) (x<<=1)+=(i-'0');
        ++g[(1<<m)-1][x].second;
    }
    vector<int> c(1<<m);
    for(auto s=(1<<m)-2;~s;--s){
        auto nxt=0;
        cir(i,0,m) if(!(s&(1<<i))) nxt=i;
        for(auto&[a,b]:g[s]) c[a]=0;
        for(auto&[a,b]:g[s|(1<<nxt)]) c[s&a]+=b;
        for(auto&[a,b]:g[s]) b+=c[a];
    }
    vector<lf> f(1<<m);
    cir(s,0,(1<<m)) if(s&1) [&](){
        const auto ck=n-g[s].front().second-g[s].back().second;
        if(!ck) return f[s]=1,void();
        for(auto&[a,b]:g[s]) if(a&&a!=s){
            f[s]+=f[a]*b/ck;
        }
    }();
    cout<<fixed<<setprecision(15)<<f[(1<<m)-1]<<'\n';
    return 0;
}
