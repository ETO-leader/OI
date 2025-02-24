#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
static constexpr auto MOD=(int)(1e9+7);
class mathbase{
private:
    vector<lint> invx;
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
    auto initinv(auto x){
        invx.resize(x);
        cir(i,0,x) invx[i]=inv(i);
    }
    auto finv(auto x) const{return x>-1?invx[x]:(MOD-invx[-x]);}
} math;
static constexpr auto inv2=math.inv(2);
class lagrange{
public:
    auto check(vector<lint> x,vector<lint> y,lint target){
        auto res=0ll;
        const auto n=(int)(x.size());
        cir(i,0,n){
            auto prod=y[i];
            cir(j,0,n) if(i!=j) (prod*=(target+MOD-x[j])*math.finv(x[i]-x[j])%MOD)%=MOD;
            (res+=prod)%=MOD;
        }
        return res;
    }
};
class tree{
private:
    vector<vector<int>> gr;
    vector<lint> l,r,method,returned;
    vector<int> dfn,fx;
    auto init(int u,int f=-1)->void{
        fx[u]=f;
        for(auto&i:gr[u]) if(i!=f) init(i,u);
        dfn.emplace_back(u);
    }
    auto dfs(lint w,lint k,auto&ans){
        for(auto&u:dfn){
            const auto val=max<lint>(min(w+k,r[u])-max(w,l[u])+1,0);
            if(!val){
                returned[u]=0;continue;
            }
            auto res=1ll,pre=0ll;
            for(auto&i:gr[u]) if(i!=fx[u]){
                const auto wx=returned[i];
                (ans+=wx*val%MOD*pre)%=MOD;
                (res+=wx)-=(res>MOD-1?MOD:0);
                (pre+=wx)-=(pre>MOD-1?MOD:0);
            }
            (ans+=((res*=val)%=MOD))%=MOD;
            ans-=ans>MOD-1?MOD:0;
            returned[u]=res;
        }
    }
    constexpr auto getsum(lint l,lint r){
        return l-1<r?((r+l)*(r-l+1)>>1)%MOD:0;
    }
    auto dfssum(lint w,lint k,auto&ans){
        for(auto&u:dfn){
            const auto val=max<lint>(min(w+k,r[u])-max(w,l[u])+1,0);
            const auto sum=getsum(max(w,l[u]),min(w+k,r[u]));
            auto res=0ll,pre=0ll,presum=0ll;
            for(auto&i:gr[u]) if(i!=fx[u]){
                const auto wx=returned[i];
                (ans+=
                    val*method[i]%MOD*presum+
                    val*pre%MOD*wx+
                    pre*sum%MOD*method[i]
                )%=MOD;
                (res+=wx)-=(res>MOD-1?MOD:0);
                (pre+=method[i])-=(pre>MOD-1?MOD:0);
                (presum+=wx)-=(presum>MOD-1?MOD:0);
            }
            ans+=(res=(res*val+(pre+1)*sum)%MOD);
            ans-=ans>MOD-1?MOD:0;
            method[u]=(pre+1)*val%MOD;
            returned[u]=res;
        }
    }
public:
    auto link(int u,int v){
        gr[u].emplace_back(v);
        gr[v].emplace_back(u);
    }
    auto init(){init(0);}
    auto chkval(lint l,lint r,lint k){
        const auto n=(int)(gr.size());
        vector<lint> x,y;
        cir(w,l,min(l+n+7,r+1)){
            x.emplace_back(w);
            auto res=0ll,ans=0ll;
            dfs(w,k,ans);
            (res+=ans)%=MOD;
            ans=0;
            dfs(w+1,k-1,ans);
            (res+=MOD-ans)%=MOD;
            y.emplace_back(res);
        }
        cir(i,1,(int)(y.size())) (y[i]+=y[i-1])%=MOD;
        return lagrange().check(x,y,r);
    }
    auto chksum(lint l,lint r,lint k){
        const auto n=(int)(gr.size());
        vector<lint> x,y;
        cir(w,l,min(l+n*2+7,r+1)){
            x.emplace_back(w);
            auto res=0ll,ans=0ll;
            dfssum(w,k,ans);
            (res+=ans)%=MOD;
            ans=0;
            dfssum(w+1,k-1,ans);
            (res+=MOD-ans)%=MOD;
            y.emplace_back(res);
        }
        cir(i,1,(int)(y.size())) (y[i]+=y[i-1])%=MOD;
        return lagrange().check(x,y,r);
    }
    tree(int _n,vector<lint> _l,vector<lint> _r):gr(_n),l(_l),r(_r),method(_n),returned(_n),fx(_n){}
};
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int n,k;cin>>n>>k;
    math.initinv(n*2+7);
    vector<lint> l(n),r(n);
    cir(i,0,n) cin>>l[i]>>r[i];
    tree tr(n,l,r);
    cir(i,0,n-1){
        int u,v;cin>>u>>v;--u;--v;
        tr.link(u,v);
    }
    tr.init();
    const auto mxr=*max_element(r.begin(),r.end());
    set<lint> posx;
    for(auto&x:l) posx.emplace(x-1),posx.emplace(x),posx.emplace(x-k);
    for(auto&x:r) posx.emplace(x-1),posx.emplace(x),posx.emplace(x-k);
    posx.emplace(mxr+7);
    posx.emplace(1);
    vector<lint> ax(posx.begin(),posx.end());
    while(ax.front()<1) ax.erase(ax.begin());
    auto ans=0ll,anssum=0ll;
    cir(i,0,(int)(ax.size())-1) (ans+=tr.chkval(ax[i],ax[i+1]-1,k))%=MOD;
    cir(i,0,(int)(ax.size())-1) (anssum+=tr.chksum(ax[i],ax[i+1]-1,k))%=MOD;
    cout<<ans<<'\n'<<anssum<<'\n';
    return 0;
}
