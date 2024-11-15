#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
class bit{
private:
    vector<lint> a;
    constexpr auto lowbit(auto x){return x&(-x);}
public:
    auto update(int x,lint w){
        for(++x;x<a.size();x+=lowbit(x)) a[x]+=w;
    }
    auto query(lint x){
        auto res=0ll;
        for(++x;x;x-=lowbit(x)) res+=a[x];
        return res;
    }
    bit(int _x):a(_x+1){}
};
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int T;cin>>T;
    while(T--) [&](){
        int n;cin>>n;vector<int> a(n);
        for(auto&i:a) cin>>i;
        vector<int> value(n);
        auto x=0;
        cir(i,0,n) value[i]=(x=(x<a[i]?x+1:((x>a[i])?x-1:x)));
        auto check=[&](int mid){
            auto l=mid,r=mid;
            bit val(n+7);
            cir(i,0,n-1) val.update(value[i],1);
            val.update(0,1);
            if(val.query(mid)-val.query(mid-1)) return true;
            for(auto i=n-1;i;--i){
                val.update(value[i-1],-1);
                if(l<a[i]+1) --l;
                if(r<a[i]) --r;
                if(l>a[i]) ++l;
                if(r>a[i]-1) ++r;
                l=max(l,0);
                l=min(n+5,l);
                r=min(n+5,r);
                r=max(r,0);
                if(val.query(r)-val.query(l-1)) return true;
            }
            return false;
        };
        auto l=1,r=n+5,ans=0;
        while(l-1<r){
            const auto mid=midpoint(l,r);
            check(mid)?((l=mid+1),(ans=mid)):(r=mid-1);
        }
        println("{}",ans);
    }();
    return 0;
}
