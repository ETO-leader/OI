#pragma GCC optimize("Ofast")
#pragma GCC optimize("inline")
#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
ifstream fcin("mod.in");
ofstream fcout("mod.out");
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
    int n;fcin>>n;vector<int> a(n);
    for(auto&i:a) fcin>>i;
    vector<int> c(*max_element(a.begin(),a.end())+1);
    for(auto&i:a) ++c[i];
    const auto m=(int)(c.size())-1;
    auto ans=1ll;
    cir(i,1,m+1){
        vector f(m+1,vector<lint>(2));
        f[i-1][0]=1;
        auto las=i-1;
        cir(x,i,m+1){
            if(c[x]){
                cir(p,1,i+1) if(x-p>i-2){
                    (f[x][1]+=f[x-p][0]+f[x-p][1])%=MOD;
                }
                las=x;
            }else{
                f[x][0]=f[las][1];
            }
        }
        (ans+=f[m][1])%=MOD;
    }
    fcout<<ans<<'\n';
    return 0;
}
