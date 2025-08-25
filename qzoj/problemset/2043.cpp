#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
static constexpr auto MOD=998244353;
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int n,d;cin>>n>>d;
    vector<int> w(n),b(n);
    for(auto&i:w) cin>>i;
    for(auto&i:b) cin>>i;
    int p1,p2,q1,q2,rp1,rp2,rq1,rq2,c;
    cin>>p1>>p2>>q1>>q2>>rp1>>rp2>>rq1>>rq2>>c;
    vector<lint> f(p1+1),g(q1+1);
    f[0]=g[0]=1;
    auto emplace=[](int q1,auto&f,int v){
        for(auto c=q1-v;~c;--c) (f[c+v]+=f[c])%=MOD;
    };
    auto remove=[](int q1,auto&f,int v){
        cir(c,0,q1-v+1) (f[c+v]+=MOD-f[c])%=MOD;
    };
    map<int,int> cw;
    cir(i,0,n) cw[b[i]]+=w[i];
    auto s=accumulate(w.begin(),w.end(),0ll);
    auto calc=[&f,&g,&s](int p1,int p2,int q1,int q2){
        auto ansf=0ll;
        cir(i,0,p1+1) if(s-i<p2+1) (ansf+=f[i])%=MOD;
        auto ansg=0ll;
        cir(i,0,q1+1) if(s-i<q2+1) (ansg+=g[i])%=MOD;
        return (ansf*ansg)%MOD;
    };
    for(auto&[a,b]:cw) emplace(p1,f,b);
    for(auto&x:w) emplace(q1,g,x);
    auto ans=calc(min(p1,rp1),min(p2,rp2),min(q1,rq1),min(q2,rq2));
    const auto nf=f,ng=g;
    if(c) cir(i,0,n){
        remove(p1,f,cw[b[i]]);
        remove(q1,g,w[i]);
        s-=w[i];
        if(cw[b[i]]-w[i]) emplace(p1,f,cw[b[i]]-w[i]);
        f.resize(min(p1,rp1-w[i])+1);
        g.resize(min(q1,rq1-w[i])+1);
        (ans+=calc(min(p1,rp1-w[i]),min(p2,rp2-w[i]),min(q1,rq1-w[i]),min(q2,rq2-w[i])))%=MOD;
        f=nf;g=ng;
        s+=w[i];
    }
    cout<<ans<<'\n';
    return 0;
}
