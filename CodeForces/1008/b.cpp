#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
static constexpr auto _inf=(int)(1e9+7);
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int T;cin>>T;
    while(T--) [&]{
        const auto valx=[&](){
            auto res=0;
            cir(i,0,30) if(!(i&1)) res|=1<<i;
            return res; 
        }();
        const auto valy=[&](){
            auto res=0;
            cir(i,0,30) if(i&1) res|=1<<i;
            return res; 
        }();
        cout<<valx<<'\n';
        cout.flush();
        int wx;cin>>wx;
        cout<<valy<<'\n';
        cout.flush();
        int wy;cin>>wy;
        vector<int> s(30);
        cir(b,0,30){
            if(!(b&1)){
                auto cur=false;
                cir(x,0,b){
                    if(x&1) cur=(2+cur)>1;
                    else cur=(s[x]+cur)>1;
                }
                // 进位: cur
                const auto w=((wy>>b)&1)^cur;
                if(w){
                    s[b]=1;
                }else{
                    if((wy>>(b+1))&1) s[b]=2;
                    else s[b]=0;
                }
            }else{
                auto cur=false;
                cir(x,0,b){
                    if(!(x&1)) cur=(2+cur)>1;
                    else cur=(s[x]+cur)>1;
                }
                // 进位: cur
                const auto w=((wx>>b)&1)^cur;
                if(w){
                    s[b]=1;
                }else{
                    if((wx>>(b+1))&1) s[b]=2;
                    else s[b]=0;
                }
            }
        }
        cout<<'!'<<'\n';
        cout.flush();
        int w;cin>>w;
        auto ans=0;
        cir(i,0,30) if((w>>i)&1) s[i]=2;
        cir(i,0,30) ans+=(s[i]<<i);
        cout<<ans<<'\n';
        cout.flush();
    }();
    return 0;
}
