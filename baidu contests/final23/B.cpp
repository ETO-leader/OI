#pragma GCC optimize("Ofast")
#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
using VI=vector<int>;
static constexpr int MOD=1e9+7;
static constexpr auto qpow(lint a,lint b){
    lint res=1;
    while(b){
        if(b&1) (res*=a)%=MOD;
        (a*=a)%=MOD;b>>=1;
    }
    return res;
}
static constexpr auto inv(lint x){
    return qpow(x,MOD-2);
}
struct qry{int a,b;};
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n,m,s,t;cin>>n>>m>>s>>t;
    vector<qry> qryx;qryx.reserve(n*2+7);
    t-=s;
    cir(i,0,m){
        int l,r,x;cin>>x>>l>>r;
        if(r-s<0||l-s>t) continue;
        qryx.push_back({l-s-1,-1});
        qryx.push_back({r-s,1});
    }
    lint ans=1,lx=-1,cnt=n;
    qryx.push_back({t,0});
    sort(qryx.begin(),qryx.end(),[](qry&a,
        qry&b){return a.a<b.a;});
    vector<pair<int,int>> tgs;
    tgs.reserve(n*2+7);
    cir(i,0,qryx.size()){
        int x=qryx[i].a,cnt=qryx[i].b;
        while(i+1<qryx.size()&&qryx[i+1].a==x)
            ++i,cnt+=qryx[i].b;
        tgs.push_back({x,cnt});
    }
    for(auto&[a,b]:tgs){
        if(a>t) break;
        if(a<0){
            cnt+=b;continue;
        }
        (ans*=qpow(cnt,a-lx))%=MOD;
        lx=a;cnt+=b;
    }
    cout<<ans<<'\n';
    return 0;
}
