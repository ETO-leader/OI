#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
class trie{
private:
    vector<array<int,2>> tr;
    int cnt;
public:
    auto emplace(uint x){
        auto u=0;
        for(auto i=31;~i;--i){
            const auto w=(x>>i)&1;
            if(!tr[u][w]) tr[u][w]=++cnt;
            u=tr[u][w];
        }
    }
    auto query(uint x){
        auto u=0;
        auto ans=0u;
        for(auto i=31;~i;--i){
            const auto w=(x>>i)&1;
            if(tr[u][!w]) u=tr[u][!w],ans|=(1u<<i);
            else u=tr[u][w];
        }
        return ans;
    }
    trie(int _n):tr((_n<<5)+7),cnt(0){}
};
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int n;cin>>n;vector<uint> a(n);
    for(auto&i:a) cin>>i;
    vector<uint64_t> w(n),rw(n);
    [&]{
        trie tr(n+1);
        tr.emplace(0);
        auto pxor=0;
        cir(i,0,n){
            pxor^=a[i];
            w[i]=tr.query(pxor);
            tr.emplace(pxor);
        }
    }();
    [&]{
        trie tr(n+1);
        tr.emplace(0);
        auto pxor=0;
        for(auto i=n-1;~i;--i){
            pxor^=a[i];
            rw[i]=tr.query(pxor);
            tr.emplace(pxor);
        }
    }();
    auto ans=(uint64_t)(0);
    auto pmx=w[0];
    cir(i,1,n){
        ans=max(ans,pmx+rw[i]);
        pmx=max(pmx,w[i]);
    }
    cout<<ans<<'\n';
    return 0;
}
