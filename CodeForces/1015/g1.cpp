#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
static constexpr auto _infl=(lint)(1e15l);
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int T;cin>>T;
    while(T--) [&]{
        int n;cin>>n;vector<int> a(n);
        for(auto&i:a) cin>>i;
        vector<int> col(n+1,-1);
        cir(i,0,n) if(a[i]) col[a[i]]=(i&1);
        vector f(n+1,vector(n+1,_infl));
        f[0][0]=0;
        cir(i,1,n+1){
            if(col[i]){
                cir(j,0,n+1) f[i][j]=min(f[i][j],f[i-1][j]);
            }
            if(col[i]!=1){
                cir(j,1,n+1) f[i][j]=min(f[i][j],f[i-1][j-1]);
            }
            cir(j,0,n+1) f[i][j]+=(n/2-(i-j))*j+(i-j)*((n+1)/2-j);
        }
        auto ans=0ll;
        cir(i,1,n+1) ans+=(lint)(i*i);
        ans-=f[n][(n+1)/2];
        cout<<ans<<'\n';
    }();
    return 0;
}
