#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
static constexpr auto lowbit(auto x){return x&(-x);}
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int n;cin>>n;
    vector<int> p;
    auto dfs=[&](auto __self,uint vs,uint vsl,uint vsr){
        if(!vs){
            for(auto&x:p) cout<<x;
            cout<<'\n';
            return 1ll;
        }
        auto res=0ll;
        for(auto s=vs&vsl&vsr;s;s^=lowbit(s)){
            p.emplace_back(__lg(lowbit(s))+1);
            res+=__self(__self,vs^lowbit(s),((vsl^lowbit(s))>>1)|(1<<(n-1)),((vsr^lowbit(s))<<1)|1);
            p.pop_back();
        }
        return res;
    };
    cout<<dfs(dfs,(1<<n)-1,(1<<n)-1,(1<<n)-1)<<'\n';
    return 0;
}
