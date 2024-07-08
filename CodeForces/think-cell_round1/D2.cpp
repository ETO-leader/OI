#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
static constexpr lint _inf=1e18+7;
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int T;cin>>T;
    while(T--){
        int n;string s;cin>>n>>s;
        s.insert(s.begin(),' ');
        vector<int> cnt(n+1);
        cir(i,1,n+1) cnt[i]=s[i]-'0'+cnt[i-1];
        vector<vector<lint>> f(n+2,vector<lint>(3));
        for(int i=n;i;--i) cir(w,0,3) if(i+w<n+1){
            f[i][w]=f[i+1][(w+2)%3]+(s[i]=='1')*(n-i-w+3)/3;
            f[i][w]=min(f[i][w],min(cnt[i+w]-cnt[i-1],1)+f[min(i+3,n+1)][w]+max((n-i-w)/3,0));
        }
        lint ans=0;
        for(auto&i:f) ans+=i[0]+i[1]+i[2];
        cout<<ans<<'\n';
    }
    return 0;
}
