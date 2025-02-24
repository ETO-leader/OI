#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
static constexpr auto MOD=(int)(1e9+7);
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
} math;
class lagrange{
public:
    auto check(vector<lint> x,vector<lint> y,lint target){
        auto res=0ll;
        const auto n=(int)(x.size());
        cir(i,0,n){
            auto prod=y[i];
            cir(j,0,n) if(i!=j) (prod*=(target+MOD-x[j])*math.inv(x[i]+MOD-x[j])%MOD)%=MOD;
            (res+=prod)%=MOD;
        }
        return res;
    }
};
class tree{
private:
    vector<vector<int>> gr;
    vector<lint> l,r;
    auto dfs(int u,int s,lint w,lint k,auto&wx,lint cur=1,int f=-1)->void{
        (cur*=max<lint>(min(w+k,r[u])-max(w,l[u])+1,0))%=MOD;
        if(u>s-1) wx[u]=cur;
        for(auto&i:gr[u]) if(i!=f) dfs(i,s,w,k,wx,cur,u);
    }
public:
    auto link(int u,int v){
        gr[u].emplace_back(v);
        gr[v].emplace_back(u);
    }
    auto chkval(lint w,lint k){
        auto res=0ll;
        cir(i,0,(int)(gr.size())){
            vector<lint> wx(gr.size());
            dfs(i,i,w,k,wx);
            for(auto&i:wx) (res+=i)%=MOD;
            dfs(i,i,w+1,k-1,wx);
            for(auto&i:wx) (res+=MOD-i)%=MOD;
        }
        return res;
    }
    tree(int _n,vector<lint> _l,vector<lint> _r):gr(_n),l(_l),r(_r){}
};
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int n,k;cin>>n>>k;
    vector<lint> l(n),r(n);
    cir(i,0,n) cin>>l[i]>>r[i];
    tree tr(n,l,r);
    cir(i,0,n-1){
        int u,v;cin>>u>>v;--u;--v;
        tr.link(u,v);
    }
    const auto mxr=*max_element(r.begin(),r.end());
    auto ans=0ll;
    cir(i,1,mxr+7) (ans+=tr.chkval(i,k))%=MOD;
    cout<<ans<<'\n';
    return 0;
}
