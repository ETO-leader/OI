#include<bits/stdc++.h>
#if defined(__linux)
    #include<bits/extc++.h>
#else
    #include<ext/pb_ds/assoc_container.hpp>
    #include<ext/pb_ds/hash_policy.hpp>
#endif
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
constexpr auto qpow(lint a,lint b,const int p){
    auto res=1ll;
    while(b){
        if(b&1) (res*=a)%=p;
        (a*=a)%=p;b>>=1;
    }
    return res;
}
constexpr auto inv(lint x,const int p){
    return qpow(x,p-2,p);
}
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int T;cin>>T;
    while(T--) [&](){
        int n,p;cin>>n>>p;vector<int> a(n);
        for(auto&i:a) cin>>i;
        auto check=[&](int x,int y){
            const auto ivq=inv(a[y]*inv(a[x],p)%p,p);
            auto res=0;
            __gnu_pbds::gp_hash_table<int,int> f;
            cir(i,0,n){
                auto fx=1;
                if(f.find(a[i]*ivq%p)!=f.end()){
                    fx+=f[a[i]*ivq%p];
                }
                f[a[i]]=max(f[a[i]],fx);
                res=max(res,fx);
            }
            return res;
        };
        auto ans=0;
        mt19937 rnd('qwq');
        cir(i,0,30){
            const auto px=rnd()%n;
            if(px+1<n) ans=max(ans,check(px,px+1));
            if(px+2<n) ans=max(ans,check(px,px+2));
        }
        cout<<(ans*2<n?-1:ans)<<'\n';
    }();
    return 0;
}
