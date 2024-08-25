#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
ifstream fcin("pair.in");
ofstream fcout("pair.out");
class fileio{
public:
    ~fileio(){
        fcin.close();fcout.close();
    }
} use_fileio;
using lint=long long;
static constexpr auto MOD=998244353;
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    string s;fcin>>s;
    const auto n=(int)(s.size());
    vector f(n+1,vector(2,vector<lint>(2)));
    f[n][1][1]=1;
    for(auto i=n;i;--i) cir(lx,0,2) cir(ly,0,2){
        const auto lxw=lx?s[n-i]-'0':1,lyw=ly?s[n-i]-'0':1;
        cir(nxw,0,lxw+1) cir(nyw,0,lyw+1) if(!(nxw&&nyw)){
            (f[i-1][lx&&(nxw==lxw)][ly&&(nyw==lyw)]+=f[i][lx][ly])%=MOD;
        }
    }
    fcout<<[&](){
        auto res=0ll;
        cir(i,0,2) cir(j,0,2) (res+=f[0][i][j])%=MOD;
        return res;
    }()<<'\n';
    return 0;
}
