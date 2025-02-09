#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
static constexpr auto MOD=998244353;
class invaild{};
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int T;cin>>T;
    while(T--) [&]{
        int n,m;cin>>n>>m;vector<int> a(n),b(m);
        for(auto&i:a) cin>>i;
        for(auto&i:b) cin>>i;
        map<int,int> cnt;
        for(auto&i:a) ++cnt[i];
        ranges::sort(b,greater<int>());
        auto dfs=[&](auto __self,int w){
            if(cnt[w]) return --cnt[w],void();
            if(!w) throw invaild();
            __self(__self,w/2);
            __self(__self,(w/2)+(w&1));
        };
        for(auto&x:b) try{
            dfs(dfs,x);
        }catch(invaild){
            return cout<<"No"<<'\n',void();
        }
        for(auto&[a,b]:cnt) if(b) return cout<<"No"<<'\n',void();
        cout<<"Yes"<<'\n';
    }();
    return 0;
}
