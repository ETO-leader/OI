#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
static constexpr int _inf=1e9+7;
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int T;cin>>T;
    while(T--){
        int n;string s;cin>>n>>s;
        vector<int> cnt(n+1);
        cir(i,1,n+1) cnt[i]=s[i-1]-'0'+cnt[i-1];
        int ans=0;
        cir(i,1,n+1) cir(j,i,n+1){
            vector<int> f(n+1,_inf);
            f[i-1]=0;
            cir(x,i,j+1) cir(p,i-1,x){
                f[x]=min(f[x],f[p]+min(cnt[x]-cnt[p],(x-p+2)/3));
            }
            ans+=f[j];
        }
        cout<<ans<<'\n';
    }
    return 0;
}
