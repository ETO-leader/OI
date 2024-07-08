#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
using VI=vector<lint>;
const lint _inf=1e15+7;
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int T;cin>>T;
    while(T--){
        int n;cin>>n;
        lint ans=0;
        cir(i,0,n+1){
            VI a(n);
            iota(a.begin(),a.end(),1);
            reverse(a.begin()+i,a.end());
            lint ansi=0,mx=0;
            cir(i,0,n){
                ansi+=a[i]*(i+1);
                mx=max(mx,a[i]*(i+1));
            }
            const auto w=ansi-mx;
            if(w>ans) ans=w;
        }
        cout<<ans<<'\n';
    }
    return 0;
}
