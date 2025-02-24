#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
static constexpr auto MOD=998244353;
class mathbase{
public:
    constexpr auto qpow(lint a,auto b){
        auto res=1ll;
        while(b){
            if(b&1) (res*=a)%=MOD;
            (a*=a)%=MOD;b>>=1;
        }
        return res;
    }
    constexpr auto inv(auto x){return qpow(x,MOD-2);}
    constexpr auto is_prime(int x){
        for(auto i=2;i*i<x+1;++i) if(!(x%i)) return false;
        return true;
    }
} math;
static constexpr auto sqrv=46;
static constexpr auto maxv=2007;
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int n;cin>>n;
    vector<int> cnt(maxv);
    cir(i,0,n){
        int w;cin>>w;++cnt[w];
    }
    int m;cin>>m;
    vector<int> sqrp,lgrp;
    cir(i,2,sqrv) if(math.is_prime(i)) sqrp.emplace_back(i);
    lgrp.emplace_back(1);
    cir(i,sqrv,maxv) if(math.is_prime(i)) lgrp.emplace_back(i);
    const auto k=(int)(sqrp.size());
    const auto g=(int)(lgrp.size());
    vector<int> s(maxv);
    for(auto cnt=-1;auto&p:sqrp){
        ++cnt;
        cir(i,1,maxv) if(!(i%p)) s[i]|=(1<<cnt);
    }
    vector<vector<pair<int,lint>>> qwq(g);
    // qwq[p]: [p * k's:(S, method)]
    cir(i,1,maxv) if(cnt[i]) for(auto c=g-1;~c;--c) if(!(i%lgrp[c])){
        qwq[c].emplace_back(s[i],math.qpow(2,cnt[i]));
        break;
    }
    // pre[S][p]: 前 p 个质数中不选 S 的方案数
    vector<vector<lint>> pre(1<<k,vector<lint>(g,1));
    cir(s,0,(1<<k)) cir(x,0,g){
        if(x) pre[s][x]=pre[s][x-1];
        for(auto&[ns,c]:qwq[x]) if(!(s&ns)){
            (pre[s][x]*=c)%=MOD;
        }
    }
    auto ipre=pre;
    for(auto&x:ipre) for(auto&i:x) i=math.inv(i);
    auto srange=[&](int s,int l,int r){
        if(l>r) return 1ll;
        return pre[s][r]*(l?ipre[s][l-1]:1)%MOD;
    };
    vector<int> ordl(sqrv),ordg(maxv);
    cir(i,0,k) ordl[sqrp[i]]=i;
    cir(i,0,g) ordg[lgrp[i]]=i;
    cir(i,0,m){
        int x;cin>>x;vector<int> p(x);
        for(auto&i:p) cin>>i;
        auto s=0;
        vector<int> qx;
        for(auto&i:p){
            if(i<sqrv) s|=(1<<ordl[i]);
            else qx.emplace_back(i);
        }
        sort(qx.begin(),qx.end());
        qx.erase(unique(qx.begin(),qx.end()),qx.end());
        auto ans=0ll;
        for(auto w=s;~w;w=(w-1)&s){
            vector<lint> f(2);
            f[0]=1;
            auto las=-1;
            for(auto&i:qx){
                (f[0]*=srange(w,las+1,ordg[i]-1))%=MOD;
                (f[1]*=srange(w,las+1,ordg[i]-1))%=MOD;
                const auto lf=f;
                (f[0]=lf[0]*srange(w,ordg[i],ordg[i])+lf[1])%=MOD;
                (f[1]=lf[1]*srange(w,ordg[i],ordg[i])+lf[0])%=MOD;
                las=ordg[i];
            }
            (f[0]*=srange(w,las+1,g-1))%=MOD;
            (f[1]*=srange(w,las+1,g-1))%=MOD;
            const auto sgn=__builtin_popcount(w)&1?MOD-1:1;
            (ans+=f[0]*sgn+f[1]*(MOD-sgn))%=MOD;
            if(!w) break;
        }
        cout<<ans<<'\n';
    }
    return 0;
}
