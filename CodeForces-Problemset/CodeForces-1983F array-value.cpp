#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
class trie{
private:
    static constexpr auto lgx=32;
    vector<array<int,2>> tr;
    vector<int> mx;
    int cnt;
public:
    auto insert(uint x,const int id){
        auto u=0;
        for(auto i=lgx-1;~i;--i){
            const auto w=(x>>i)&1;
            if(!tr[u][w]) tr[u][w]=++cnt;
            mx[u=tr[u][w]]=id;
        }
    }
    auto query(uint x,uint lim){
        auto u=0,ans=-1;
        for(auto i=lgx-1;~i;--i){
            const auto w=(x>>i)&1;
            const auto lw=(lim>>i)&1;
            if(lw){
                if(tr[u][w]) ans=max(ans,mx[tr[u][w]]);
                if(!tr[u][w^1]) return ans;
                u=tr[u][w^1];
            }else{
                if(!tr[u][w]) return ans;
                u=tr[u][w];
            }
        }
        return max(ans,mx[u]);
    }
    trie(int _n):tr(_n*lgx),mx(_n*lgx),cnt(0){}
};
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int T;cin>>T;
    while(T--) [&](){
        int n;lint k;cin>>n>>k;vector<uint> a(n);
        for(auto&i:a) cin>>i;
        auto check=[&](int lim){
            auto ans=0ll;
            auto premx=-1;
            trie tr(n);
            for(auto c=-1;auto&x:a){
                ans+=(premx=max(premx,tr.query(x,lim)))+1;
                tr.insert(x,++c);
            }
            return ans>k-1;
        };
        auto l=0,r=numeric_limits<int>::max(),ans=0;
        while(l-1<r){
            const auto mid=midpoint(l,r);
            check(mid)?((ans=mid),(r=mid-1)):(l=mid+1);
        }
        cout<<ans<<'\n';
    }();
    return 0;
}
