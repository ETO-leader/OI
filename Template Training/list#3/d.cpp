#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
static constexpr auto sqr=400;
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int n,q;cin>>n>>q;vector<lint> a(n);
    for(auto&i:a) cin>>i;
    vector<vector<lint>> cnt(sqr);
    cir(i,1,sqr) cnt[i].resize(sqr);
    cir(p,1,sqr) cir(i,0,n) cnt[p][i%p]+=a[i];
    cir(i,0,q){
        string op;cin>>op;
        if(op=="A"){
            int p,y;cin>>p>>y;(y+=(p-1))%=p;
            cout<<(p<sqr?cnt[p][y]:[&](){
                auto res=0ll;
                for(auto cur=y;cur<n;cur+=p) res+=a[cur];
                return res;
            }())<<'\n';
        }else{
            int p,w;cin>>p>>w;--p;
            const auto delta=w-a[p];
            a[p]=w;
            cir(c,1,sqr) cnt[c][p%c]+=delta;
        }
    }
    return 0;
}
