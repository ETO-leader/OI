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
        int n,q;cin>>n>>q;
        vector<int> a(n);
        for(auto&i:a) cin>>i;
        bit x(n);
        cir(i,0,n) x.update(i,a[i]);
        set<int> posi;
        cir(i,0,n) if(a[i]==1) posi.emplace(i);
        cir(i,0,q){
            int op;cin>>op;
            if(op==1){
                int w;cin>>w;
                auto l=0,r=n-1,ans=-1;
                while(l-1<r){
                    const auto mid=(l+r)/2;
                    x.query(mid)<w-1?(l=mid+1):((r=mid-1),(ans=mid));
                }
                if(x.query(ans)<w-1){
                    cout<<"NO"<<'\n';
                }else if(x.query(ans)==w){
                    cout<<"YES"<<'\n';
                }else{
                    if(posi.empty()){
                        cout<<"NO"<<'\n';
                    }else{
                        cout<<(*posi.rbegin()>ans||ans+(*posi.begin()+1)<n?"YES":"NO")<<'\n';
                    }
                }
            }else{
                int p,w;cin>>p>>w;--p;
                if(a[p]==1) posi.erase(p);
                x.update(p,-a[p]);
                a[p]=w;
                if(a[p]==1) posi.emplace(p);
                x.update(p,a[p]);
            }
        }
    }();
    return 0;
}
