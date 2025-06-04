#include<bits/stdc++.h>
#define cir(i,a,b) for(auto i=a;i<b;++i)
using namespace std;
ifstream inf("who.in");
ofstream ouf("who.out");
class fileio{
public:
    ~fileio(){
        inf.close();ouf.close();
    }
} use_fileio;
using lint=long long;
int main(){
    ios::sync_with_stdio(false),inf.tie(nullptr);
    int T;inf>>T;
    while(T--) []{
        lint a,b,p;inf>>a>>b>>p;
        vector<lint> sqrcnt(p);
        cir(i,0ll,p) ++sqrcnt[i*i%p];
        auto ans=0ll;
        cir(x,0ll,p) ans+=sqrcnt[(x*x%p*x+a*x+b)%p];
        ouf<<ans<<'\n';
    }();
    return 0;
}
