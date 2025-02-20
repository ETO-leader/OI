#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
static constexpr auto _inf=(int)(1e9+7);
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int T;cin>>T;
    while(T--) [&]{
        int n;cin>>n;vector<int> a(n);
        for(auto&i:a) cin>>i;
        auto pos=-1;
        cir(i,0,n) if(!a[i]){
            pos=i;break;
        }
        if(pos<0){
            cout<<n<<'\n';
            return;
        }
        const auto ans=n-ranges::count(a,0);
        vector<int> x;
        cir(i,0,pos) x.emplace_back(a[i]);
        x.emplace_back(0);
        cir(i,pos+1,n) if(a[i]) x.emplace_back(a[i]);
        set<int> suf;
        cir(i,0,n+7) suf.emplace(i);
        vector<int> c(x.size());
        for(auto i=(int)(x.size())-1;~i;--i){
            c[i]=*suf.begin();
            suf.extract(x[i]);
        }
        vector<int> pmn=x;
        cir(i,1,(int)(x.size())) pmn[i]=min(pmn[i-1],pmn[i]);
        auto ok=true;
        cir(i,0,(int)(c.size())) if(pmn[i]<c[i]) ok=false;
        cout<<ans+ok<<'\n';
    }();
    return 0;
}
