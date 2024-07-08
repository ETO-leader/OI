#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
static constexpr auto MOD=998244353;
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n,d;cin>>n>>d;vector<int> a(n);
    unordered_set<int> aps;
    for(auto&i:a){
        cin>>i;
        if(i>-1) aps.insert(--i);
    }
    vector<vector<lint>> f(2,vector<lint>(1<<(d*2+1)));
    auto stp=0,stx=(1<<(d+1))-1;
    cir(i,0,d) if(aps.count(i)) stx|=(1<<(i+d));
    f[0][stx]=1;
    cir(i,0,n){
        stp^=1;
        fill(f[stp].begin(),f[stp].end(),0);
        if(a[i]>-1){
            if(abs(a[i]-i)>d) continue;
            const auto apd=(int)(aps.count(i+d)||(i+d>n-1));
            cir(s,0,(1<<(d*2+1))){
                (f[stp][(s>>1)|(apd<<(d*2))]+=f[stp^1][s])%=MOD;
            }
            continue;
        }
        const auto apd=(int)(aps.count(i+d)||(i+d>n-1));
        cir(s,0,(1<<(d*2+1))){
            const auto nst=(s>>1)|(apd<<(d*2));
            cir(p,0,d*2+1) if(!(nst&(1<<p))){
                (f[stp][nst|(1<<p)]+=f[stp^1][s])%=MOD;
            }
        }
    }
    cout<<f[stp].back()<<'\n';
    return 0;
}
