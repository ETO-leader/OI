#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
static constexpr auto MOD=(int)(1e9+7);
class bit_max{
private:
    vector<int> a;
    constexpr auto lowbit(auto x) const{return x&(-x);}
public:
    auto update(int u,int x){
        for(++u;u<(int)(a.size());u+=lowbit(u)) a[u]=max(a[u],x);
    }
    auto query(int u){
        auto res=0;
        for(++u;u;u-=lowbit(u)) res=max(res,a[u]);
        return res;
    }
    bit_max(int _n):a(_n+1){}
};
class bit_sum{
private:
    vector<int> a;
    constexpr auto lowbit(auto x) const{return x&(-x);}
public:
    auto update(int u,int x){
        for(++u;u<(int)(a.size());u+=lowbit(u)) (a[u]+=x)%=MOD;
    }
    auto query(int u){
        auto res=0ll;
        for(++u;u;u-=lowbit(u)) (res+=a[u])%=MOD;
        return res;
    }
    bit_sum(int _n):a(_n+1){}
};
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int n;cin>>n;
    vector<int> a(n);
    for(auto&i:a) cin>>i;
    map<int,int> id;
    for(auto&i:a) id.emplace(i,0);
    auto c=-1;
    for(auto&[a,b]:id) b=++c;
    for(auto&i:a) i=id[i];
    auto calc=[&](vector<int> x){
        const auto k=(int)(x.size());
        if(!k) return make_pair(vector<int>({0}),vector<int>({1}));
        vector<int> f(k);
        bit_max uf(n);
        cir(i,0,k){
            f[i]=uf.query(x[i]-1)+1;
            uf.update(x[i],f[i]);
        }
        vector<int> g(k);
        vector<vector<int>> posfk(k+1);
        cir(i,0,k) posfk[f[i]].emplace_back(i);
        cir(i,0,k) if(f[i]==1) g[i]=1;
        bit_sum ug(n);
        cir(i,1,k){
            auto ufx=deque<int>(posfk[i].begin(),posfk[i].end());
            ufx.emplace_back((int)(1e9));
            auto ugx=deque<int>(posfk[i+1].begin(),posfk[i+1].end());
            ugx.emplace_back((int)(1e9));
            while(ufx.size()>1||ugx.size()>1){
                if(ufx.front()<ugx.front()){
                    ug.update(x[ufx.front()],g[ufx.front()]);
                    ufx.pop_front();
                }else{
                    (g[ugx.front()]+=ug.query(x[ugx.front()]-1))%=MOD;
                    ugx.pop_front();
                }
            }
            for(auto&p:posfk[i]) ug.update(x[p],-g[p]);
        }
        return make_pair(f,g);
    };
    reverse(a.begin(),a.end());
    const auto[uf,ug]=calc(a);
    for(auto&x:a) x=n-1-x;
    const auto[vf,vg]=calc(a);
    auto ans=0;
    auto prod=0ll;
    cir(i,0,n) ans=max(ans,uf[i]+vf[i]-1);
    cir(i,0,n) if(uf[i]+vf[i]-1==ans) (prod+=(lint)(ug[i])*vg[i]%MOD)%=MOD;
    cir(i,0,n-ans) (prod*=2)%=MOD;
    cout<<ans<<' '<<prod<<'\n';
    return 0;
}
