#include<bits/extc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
static constexpr auto MOD=(int)(1e6+7);
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int n,m;cin>>n>>m;
    vector<int> w(n,-1);
    cir(i,0,m){
        int a,b;cin>>a>>b;--a;--b;
        w[a]=b;
    }
    vector<vector<int>> f(n,vector<int>(n));
    cir(i,0,n) if(w[n-1]<0||i==w[n-1]) f[i][i]=1;
    cir(len,2,n+1) cir(l,0,n-len+1){
        const auto r=l+len-1;
        if(w[n-len]<0){
            f[l][r]=(f[l+1][r]+f[l][r-1])%MOD;
        }else{
            if(l==w[n-len]) (f[l][r]+=f[l+1][r])%=MOD;
            if(r==w[n-len]) (f[l][r]+=f[l][r-1])%=MOD;
        }
    }
    cout<<f[0][n-1]<<'\n';
    return 0;
}
