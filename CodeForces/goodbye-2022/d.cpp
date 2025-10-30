#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
static constexpr auto MOD=998244353;
class dsu{
private:
    vector<int> f;
public:
    auto findset(auto u)->int{
        return f[u]==u?u:f[u]=findset(f[u]);
    }
    auto merge(int u,int v){
        u=findset(u);v=findset(v);
        f[u]=v;
    }
    dsu(int _n):f(_n){ranges::iota(f,0);}
};
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int T;cin>>T;
    while(T--) [&]{
        int n;cin>>n;
        vector<int> a(n),b(n);
        for(auto&x:a) cin>>x,--x;
        for(auto&x:b) cin>>x,--x;
        dsu qwq(n);
        vector<int> cnt(n),siz(n),self(n);
        cir(i,0,n) qwq.merge(a[i],b[i]);
        cir(i,0,n) ++siz[qwq.findset(i)];
        cir(i,0,n) if(a[i]!=b[i]){
            ++cnt[qwq.findset(a[i])];
        }else{
            ++cnt[qwq.findset(a[i])];
            ++self[qwq.findset(a[i])];
        }
        auto ans=1ll;
        cir(i,0,n) if(qwq.findset(i)==i){
            if(siz[i]!=cnt[i]) ans=0;
            if(self[i]){
                (ans*=n)%=MOD;
            }else{
                (ans*=2)%=MOD;
            }
        }
        cout<<ans<<'\n';
    }();
    return 0;
}
