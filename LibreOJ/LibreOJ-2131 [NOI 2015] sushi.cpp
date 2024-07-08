#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
constexpr auto alst={2,3,5,7,11,13,17,19};
constexpr auto isprime(int x){
    for(auto i=2;i*i<x+1;++i){
        if(!(x%i)) return false;
    }
    return true;
}
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n,p;cin>>n>>p;
    const auto chsn=(int)(alst.size());
    vector f(1<<chsn,vector<int>(1<<chsn));
    f[0][0]=1;
    vector<int> mp(23);
    for(auto c=0;auto&i:alst) mp[i]=c++;
    vector<int> al;
    cir(i,23,n+1) if(isprime(i)) al.push_back(i);
    map<int,vector<int>> mxp;
    cir(i,2,n+1){
        auto c=-1;
        for(auto&x:al) if(!(i%x)) c=x;
        if(c>-1) mxp[c].push_back(i/c);
        else mxp[-i].push_back(i);
    }
    auto updar=[&](bool chsb,vector<int>&ar,vector<vector<int>> fx){
        for(auto&x:ar){
            auto g=fx;
            auto chs=0;
            for(auto c=0;auto&i:alst){
                if(!(x%i)) chs|=(1<<c);
                ++c;
            }
            cir(s,0,(1<<chsn)) cir(sx,0,(1<<chsn)){
                if(s&sx) continue;
                if((!chsb)&&(!(sx&chs))) (fx[s|chs][sx]+=g[s][sx])%=p;
                if(chsb&&(!(s&chs))) (fx[s][sx|chs]+=g[s][sx])%=p;
            }
        }
        return fx;
    };
    for(auto&[w,ar]:mxp){
        const auto fx=updar(false,ar,f);
        const auto gx=updar(true,ar,f);
        cir(s,0,(1<<chsn)) cir(sx,0,(1<<chsn)) if(!(s&sx)){
            f[s][sx]=(((fx[s][sx]+gx[s][sx]-f[s][sx])%p)+p)%p;
        }
    }
    auto ans=0;
    for(auto&x:f) for(auto&w:x) (ans+=w)%=p;
    cout<<ans<<'\n';
    return 0;
}