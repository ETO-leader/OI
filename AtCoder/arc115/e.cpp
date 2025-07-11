#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
static constexpr auto MOD=998244353;
static constexpr auto _inf=(int)(1e9+7);
class chtholly{
private:
    multimap<int,lint> f;
    lint sum;
public:
    auto append(int p,lint w){
        (sum+=p*w)%=MOD;
        f.emplace(p,w);
    }
    auto update(int c){
        auto p=f.lower_bound(c);
        auto w=0ll;
        for(auto it=p;it!=f.end();++it){
            (sum+=MOD-it->first*it->second%MOD)%=MOD;
            (w+=it->second)%=MOD;
        }
        f.erase(p,f.end());
        (sum+=c*w)%=MOD;
        f.emplace(c,w);
    }
    auto accumulate(){return sum;}
    chtholly():sum(0){}
};
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n;cin>>n;
    vector<int> a(n);
    for(auto&i:a) cin>>i;
    vector<lint> f(n+1);
    f[0]=1;
    vector<chtholly> pf(2);
    pf[0].append(_inf,1);
    cir(i,1,n+1){
        pf[0].update(a[i-1]);
        pf[1].update(a[i-1]);
        (f[i]=pf[(i&1)^1].accumulate()+MOD-pf[i&1].accumulate())%=MOD;
        pf[i&1].append(_inf,f[i]);
    }
    cout<<f[n]<<'\n';
    return 0;
}
