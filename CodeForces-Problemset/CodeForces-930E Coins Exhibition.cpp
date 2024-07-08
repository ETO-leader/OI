#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
static constexpr int MOD=1e9+7;
constexpr auto qpow(lint a,lint b){
    auto res=1ll;
    while(b){
        if(b&1) (res*=a)%=MOD;
        (a*=a)%=MOD;b>>=1;
    }
    return res;
}
constexpr auto inv(lint x){
    return qpow(x,MOD-2);
}
struct seg{int l,r;};
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int k,n,m;cin>>k>>n>>m;
    vector<seg> sga(n),sgb(m);
    map<int,int> loc;
    for(auto&[l,r]:sga){
        cin>>l>>r;loc.insert({l-1,0});
        loc.insert({l,0});loc.insert({r,0});
    }
    for(auto&[l,r]:sgb){
        cin>>l>>r;loc.insert({l-1,0});
        loc.insert({l,0});loc.insert({r,0});
    }
    loc.insert({0,0});loc.insert({k,0});
    for(auto c=0;auto&[a,b]:loc) b=c++;
    vector<vector<int>> f(2,vector<int>(loc.size()));
    vector<int> msga(loc.size()),msgb(loc.size());
    for(const auto&[l,r]:sga)
        msga[loc[r]]=max(msga[loc[r]],loc[l]);
    for(const auto&[l,r]:sgb)
        msgb[loc[r]]=max(msgb[loc[r]],loc[l]);
    vector<int> locp(loc.size());
    for(const auto&[a,b]:loc) locp[b]=a;
    auto sf=1,st=1,pf=-1,pt=-1;
    f[0][0]=f[1][0]=1;
    cir(i,0,(int)(loc.size())-1){
        (f[1][i]+=sf)%=MOD;(f[0][i]+=st)%=MOD;
        const auto ad=((qpow(2,locp[i+1]-locp[i]-1)+
            MOD-1)%MOD)*(sf+st)%MOD;
        (f[0][i+1]+=ad)%=MOD;(f[1][i+1]+=ad)%=MOD;
        sf=st=(sf+st+ad)%MOD;
        while(pf+1<msga[i+1]) (sf+=MOD-f[0][++pf])%=MOD;
        while(pt+1<msgb[i+1]) (st+=MOD-f[1][++pt])%=MOD;
    }
    cout<<(sf+st)*inv(2)%MOD<<'\n';
    return 0;
}
