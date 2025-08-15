#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
class bit{
private:
    vector<int64_t> a;
    constexpr auto lowbit(auto x) const{return x&(-x);}
public:
    auto update(int u,int64_t w){
        for(++u;u<(int)(a.size());u+=lowbit(u)) a[u]+=w;
    }
    auto query(int u){
        auto res=0ll;
        for(++u;u;u-=lowbit(u)) res+=a[u];
        return res;
    }
    bit(int n):a(n+1){}
};
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int T;cin>>T;
    while(T--) [&]{
        int n;cin>>n;
        basic_string<int> a(n,0);
        for(auto&i:a) cin>>i,--i;
        a+=a;
        cir(i,n,n*2) a[i]+=n;
        bit cnt(n*3+7);
        vector<int> ans(n);
        for(auto i=n*2-1;~i;--i){
            const auto target=(a[i]<i?a[i]+n:a[i]);
            const auto dis=target-i;
            ans[a[i]%n]=dis-cnt.query(target);
            cnt.update(target,1);
        }
        for(auto&x:ans) cout<<x<<' ';
        cout<<'\n';
    }();
    return 0;
}
