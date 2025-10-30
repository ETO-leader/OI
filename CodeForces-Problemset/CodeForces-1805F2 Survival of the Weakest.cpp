#include<bits/stdc++.h>
#define cir(i,a,b) for(auto i=a;i<b;++i)
using namespace std;
using lint=long long;
static constexpr auto c=45;
static constexpr auto MOD=(int)(1e9+7);
auto cmod(lint w){return w-=(w>MOD-1)?MOD:0;}
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int n;cin>>n;vector<lint> a(n);
    for(auto&x:a) cin>>x;
    ranges::sort(a);
    vector<pair<lint,lint>> x,nx;
    cir(i,0,min(n,c)) x.emplace_back(a[i]-a[0],a[i]);
    cir(i,0,n-1){
        nx.clear();
        const auto il=(i>50000?min(c/2,n):min(c,n));
        cir(i,0,il) cir(j,i+1,min(c,n)) nx.emplace_back(x[i].first+x[j].first,cmod(x[i].second+x[j].second));
        ranges::sort(nx);
        x=vector(nx.begin(),nx.begin()+min({n,c,(int)(nx.size())}));
        const auto bw=nx.front().first;
        for(auto&[a,b]:x) a-=bw;
    }
    cout<<x[0].second<<'\n';
    return 0;
}

