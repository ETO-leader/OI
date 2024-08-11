#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
ifstream fcin("or.in");
ofstream fcout("or.ans");
class fileio{
public:
    ~fileio(){
        fcin.close();fcout.close();
    }
} use_fileio;
using lint=long long;
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int T;fcin>>T;
    while(T--) [&](){
        lint l,r;fcin>>l>>r;
        if(l==r) return fcout<<1<<'\n',void();
        auto p=60;
        for(;((l>>p)&1)==((r>>p)&1);--p);
        const auto posw=(1ll<<p);
        const auto lx=l&(posw-1);
        auto rxw=r&(posw-1);
        auto rw=1ll;
        while((rw<<=1)<rxw+1);
        const auto rx=rw-1;
        auto ans=(r|rx)-l+1;
        ans+=(posw-lx)-max(rx-lx+1,0ll);
        fcout<<ans<<'\n';
    }();
    return 0;
}
