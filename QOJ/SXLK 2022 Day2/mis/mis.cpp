#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int n;cin>>n;vector<int64_t> d(n);
    for(auto&i:d) cin>>i;
    vector<pair<int,int>> es;
    cir(i,1,n){
        int f;cin>>f;--f;
        es.emplace_back(f,i);
    }
    auto check=[&](vector<int> ord){
        auto res=(int64_t)(0);
        auto qwq=d;
        for(auto&x:ord){
            const auto[u,v]=es[x];
            res+=qwq[u]+qwq[v];
            swap(qwq[u],qwq[v]);
        }
        return res;
    };
    vector<int> ord(n-1);
    iota(ord.begin(),ord.end(),0);
    auto ans=numeric_limits<int64_t>::max();
    do{
        ans=min(ans,check(ord));
    }while(next_permutation(ord.begin(),ord.end()));
    cout<<ans<<'\n';
    return 0;
}
