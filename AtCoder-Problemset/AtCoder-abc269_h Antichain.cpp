#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
static constexpr auto omega=3;
static constexpr auto MOD=998244353;
using poly=vector<lint>;
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
class polybase{
private:
    auto change(poly&a,const int n){
        vector<int> rev(n);
        cir(i,0,n) rev[i]=(rev[i>>1]>>1)|((n>>1)*(i&1));
        cir(i,0,n) if(i<rev[i]) swap(a[i],a[rev[i]]);
    }
    template<const int type>
    auto ntt(poly&a,const int n){
        change(a,n);
        for(auto h=2;h<n+1;h<<=1){
            const auto midh=h>>1;
            const auto wx=math.qpow(omega,(MOD-1)/h);
            for(auto i=0;i<n;i+=h){
                auto u=1ll;
                cir(k,i,i+midh){
                    const auto wk=a[k+midh]*u%MOD;
                    a[k+midh]=(a[k]+MOD-wk)%MOD;
                    (a[k]+=wk)%=MOD;
                    (u*=wx)%=MOD;
                }
            }
        }
        if(type==-1){
            const auto ivn=math.inv(n);
            reverse(a.begin()+1,a.end());
            for(auto&i:a) (i*=ivn)%=MOD;
        }
    }
public:
    auto mul(poly a,poly b){
        const auto n=1<<((int)(ceil(log2(a.size()+b.size()))));
        a.resize(n);b.resize(n);
        ntt<1>(a,n);ntt<1>(b,n);
        cir(i,0,n) (a[i]*=b[i])%=MOD;
        ntt<-1>(a,n);
        while((a.size()>1)&&(!a.back())) a.pop_back();
        return a;
    }
} polys;
auto operator+(poly a,poly b)->poly{
    if(a.size()<b.size()) return b+a;
    cir(i,0,(int)(b.size())) (a[i]+=b[i])%=MOD;
    return a;
}
auto operator*(poly a,poly b){
    return polys.mul(a,b);
}
auto operator*(poly a,lint x){
    for(auto&i:a) (i*=x)%=MOD;
    return a;
}
class tree{
private:
    vector<vector<int>> gr,lights;
    vector<poly> f;
    vector<int> siz,uf;
    auto divide(int l,int r,vector<int>&nodes){
        if(l>r) return poly{1};
        if(l==r) return f[nodes[l]];
        auto lsiz=0,rsiz=0;
        cir(i,l,r+1) rsiz+=(int)(f[nodes[i]].size());
        auto pos=pair(rsiz,-1);
        cir(i,l,r+1) pos=min(pos,pair(max(lsiz+=f[nodes[i]].size(),rsiz-=f[nodes[i]].size()),i));
        const auto mid=pos.second;
        return divide(l,mid,nodes)*divide(mid+1,r,nodes);
    }
    // \sum\prod, \prod
    auto dividef(int l,int r,vector<int>&nodes){
        if(l>r) return pair(poly{0},poly{1});
        if(l==r) return pair(f[nodes[l]],f[nodes[l]]);
        auto lsiz=0,rsiz=0;
        cir(i,l,r+1) rsiz+=(int)(f[nodes[i]].size());
        auto pos=pair(rsiz,-1);
        cir(i,l,r+1) pos=min(pos,pair(max(lsiz+=f[nodes[i]].size(),rsiz-=f[nodes[i]].size()),i));
        const auto mid=pos.second;
        const auto[lsum,lprod]=dividef(l,mid,nodes);
        const auto[rsum,rprod]=dividef(mid+1,r,nodes);
        return pair(
            lsum+rsum*lprod,
            lprod*rprod
        );
    }
    auto initnode(int u){
        f[u]=divide(0,(int)(lights[u].size())-1,lights[u]);
    }
    auto initpath(vector<int> nodes){
        return dividef(0,(int)(nodes.size())-1,nodes);
    }
    auto init(int u)->int{
        for(auto&i:gr[u]) siz[u]+=init(i);
        return ++siz[u];
    }
    auto path(int u,int fr=-1){
        vector<int> res;
        while(u!=fr) res.emplace_back(u=uf[u]);
        ranges::reverse(res);
        return res;
    }
    auto dfs(int u,int top,int fr=0){
        uf[u]=fr;
        if(gr[u].empty()){
            f[u]=poly{1,1};
            auto[pre,prod]=initpath(path(u,top));
            pre.emplace(pre.begin(),0);
            ++pre[1];
            f[top]=pre+prod;
            return;
        }
        ranges::sort(gr[u],[&](auto u,auto v){return siz[u]<siz[v];});
        lights[u]=gr[u];lights[u].pop_back();
        const auto hv=gr[u].back();
        for(auto&i:lights[u]) dfs(i,i,u);
        initnode(u);
        dfs(hv,top,u);
    }
public:
    auto link(int f,int u){
        gr[f].emplace_back(u);
    }
    auto check(){
        init(0);
        dfs(0,0,0);
        auto res=f[0];
        res.resize(gr.size()+1);
        return res;
    }
    tree(int _n):gr(_n),lights(_n),f(_n),siz(_n),uf(_n){}
};
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int n;cin>>n;tree gr(n);
    cir(u,1,n){
        int f;cin>>f;--f;gr.link(f,u);
    }
    auto ans=gr.check();
    ans.erase(ans.begin());
    ranges::copy(ans,ostream_iterator<lint>(cout,"\n"));
    return 0;
}
