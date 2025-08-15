#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    auto T=1;
    while(T--) [&]{
        int n,m;cin>>n>>m;
        auto ansa=0,ansb=0;
        cir(c,0,n){
            string s;cin>>s;
            auto ca=0,cb=0;
            cir(i,0,m-1){
                if(s[i]-'0'+s[i+1]-'0'<2){
                    ++ca;++i;
                }
            }
            cir(i,0,m-1){
                if(s[i]-'0'+s[i+1]-'0'==2){
                    ++cb;++i;
                }
            }
            ca=min(ca,m/4);
            cb=min(cb,m/4);
            ansa+=m/4*3-(ranges::count(s,'0')-ca);
            ansb+=ranges::count(s,'1')-cb;
        }
        cout<<ansb<<' '<<ansa<<'\n';
    }();
    return 0;
}
