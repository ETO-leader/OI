#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
static constexpr auto _inf=(int)(1e9+7);
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int T;cin>>T;
    while(T--) [&](){
        int n,m;cin>>n>>m;
        vector<array<pair<int,int>,5>> tp(n);
        cir(i,0,n){
            string s;cin>>s;
            string ns;
            for(auto&x:s) if(set{'n','a','r','e','k'}.count(x)) ns+=x;
            const auto chr="narek";
            cir(c,0,5){
                auto p=c,ans=0;
                for(auto&i:ns){
                    if(i==chr[(p+1)%5]) ans+=(p==3),(++p)%=5;
                }
                tp[i][c]={p,ans*5-(int)(ns.size())+ans*5};
            }
        }
        vector f(n+1,vector<int>(5,-_inf));
        array<int,5> pre;
        for(auto&i:pre) i=-_inf;
        pre[4]=0;
        for(auto&x:f) x[4]=0;
        cir(i,0,n){
            cir(c,0,5){
                f[i][tp[i][c].first]=max(f[i][tp[i][c].first],pre[c]+tp[i][c].second);
            }
            cir(c,0,5){
                pre[c]=max(pre[c],f[i][c]);
            }
        }
        auto ans=0;
        for(auto&x:f) ans=max(ans,*ranges::max_element(x));
        cout<<ans<<'\n';
    }();
    return 0;
}
