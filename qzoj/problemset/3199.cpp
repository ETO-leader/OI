#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
static constexpr auto maxn=(int)(5e6+7);
static constexpr auto maxb=(int)(1e8);
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int T;cin>>T;
    bitset<maxb> isp;
    isp.set();
    vector<int> pr;
    for(auto i=2;pr.size()<maxn&&i<maxb;i=isp._Find_next(i)){
        pr.emplace_back(i);
        for(auto j=(int64_t)(i)*i;j<maxb;j+=i) isp.reset(j);
    }
    while(T--) [&]{
        int p;cin>>p;
        cout<<pr[p-1]<<'\n';
    }();
    return 0;
}
