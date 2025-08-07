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
        auto res=0u;
        for(auto i=31;~i;--i){
            const auto w=(x>>i)&1;
            if(tr[u][!w]) res|=(1u<<i),u=tr[u][!w];
            else if(tr[u][w]) u=tr[u][w];
            else break;
        }
        return res;
    }
    trie(int _n):tr((_n<<5)+7),cnt(0){}
};
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int n;cin>>n;trie tr(n);
    auto ans=0u;
    cir(i,0,n){
        uint w;cin>>w;
        ans=max(ans,tr.query(w));
        tr.emplace(w);
    }
    cout<<ans<<'\n';
    return 0;
}
