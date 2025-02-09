#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
static constexpr auto MOD=998244353;
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int T;cin>>T;
    while(T--) [&]{
        int n;cin>>n;vector<int> a(n);
        for(auto&i:a) cin>>i;
        vector<lint> f(n+1);
        f[0]=1;
        a.insert(a.begin(),0);
        cir(i,1,n+1){
            // a(las) + (i - las - 1) = a(i)
            // a(las) - las + 1 = a(i) - i
            cir(x,max(i-2,0),i) if(a[x]+(i-x-1)==a[i]) (f[i]+=f[x])%=MOD;
        }
        cout<<(f[n-1]+f[n])%MOD<<'\n';
    }();
    return 0;
}
