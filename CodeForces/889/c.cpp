#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
static constexpr auto MOD=(int)(1e9+7);
static constexpr auto inv2=(MOD+1)/2;
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    // int T;cin>>T;
    auto T=1;
    while(T--) [&]{
        int n,m;cin>>n>>m;
        vector<int> a(n);
        for(auto&i:a) cin>>i;
        vector f(m+2,vector<lint>(m+2));
        for(auto i=m+1;~i;--i) for(auto j=m+1;~j;--j){
            if(i!=j){
                if(i<m+1) (f[i][j]+=f[i+1][j]+1)%=MOD;
                if(j<m+1) (f[i][j]+=f[i][j+1]+1)%=MOD;
                if(i<m+1&&j<m+1) (f[i][j]*=inv2)%=MOD;
            }else{
                if(i<m+1) f[i][j]=(f[i+1][j+1]+1)%MOD;
            }
        }
        auto ans=0ll;
        cir(i,0,n-1) (ans+=f[a[i]][a[i+1]])%=MOD;
        cir(i,1,n-1) (ans+=MOD-(m+1-a[i]))%=MOD;
        if(n==1) (ans+=f[a[0]][a[0]])%=MOD;
        cout<<ans<<'\n';
    }();
    return 0;
}
