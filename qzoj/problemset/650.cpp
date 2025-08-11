#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
static constexpr auto _inf=(int)(1e9+7);
static constexpr auto lim=45000;
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    lint a,b;cin>>a>>b;
    auto mn=_inf;
    vector<int> ans,cur;
    auto cmp=[&](lint u,lint d){
        return (__int128_t)(u)*b<(__int128_t)(a)*d;
    };
    auto cmpeq=[&](lint u,lint d){
        return (__int128_t)(u)*b<(__int128_t)(a)*d;
    };
    auto dfs=[&](auto __self,lint u,lint d,int l,int dep){
        if(dep==1){
            const auto g=__gcd(b,d);
            const auto nd=d/g*b;
            const auto nu=d/g*a-b/g*u;
            if(nd%nu||nd/nu>mn-1||nd/nu<l+1) return;
            cur.emplace_back(nd/nu);
            ans=cur;mn=nd/nu;
            cur.pop_back();
            return;
        }
        cir(v,l+1,lim){
            if(v>mn-1) break;
            const auto g=__gcd<lint>(d,v);
            const auto nd=d/g*v;
            const auto c=u*v/g;
            const auto x=d/g;
            if(cmp(x*dep+c,nd)) break;
            if(!cmpeq(x+c,nd)) continue;
            cur.emplace_back(v);
            __self(__self,x+c,nd,v,dep-1);
            cur.pop_back();
        }
    };
    auto d=0;
    while(mn==_inf){
        dfs(dfs,0,1,1,++d);
    }
    cir(i,0,(int)(ans.size())-1){
        cout<<"1/"<<ans[i]<<"+";
    }
    cout<<"1/"<<ans.back()<<'\n';
    return 0;
}
