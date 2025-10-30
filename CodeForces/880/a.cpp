#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int T;cin>>T;
    while(T--) [&]{
        int a,b,c;lint k;cin>>a>>b>>c>>k;
        auto vla=1,wa=9;
        cir(i,0,a-1) vla*=10,((wa*=10)+=9);
        auto vlb=1,wb=9;
        cir(i,0,b-1) vlb*=10,((wb*=10)+=9);
        auto vlc=1,wc=9;
        cir(i,0,c-1) vlc*=10,((wc*=10)+=9);
        cir(i,vla,wa+1){
            const auto dl=max(vlb,vlc-i);
            const auto dr=min(wb,wc-i);
            if(dl<dr+1){
                if(k<(dr-dl+1)+1){
                    cout<<i<<" + "<<dl+k-1<<" = "<<i+(dl+k-1)<<'\n';
                    return;
                }else{
                    k-=(dr-dl+1);
                }
            }
        }
        cout<<-1<<'\n';
    }();
    return 0;
}
