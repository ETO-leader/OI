#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
static constexpr auto _inf=(int)(1e9+7);
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int n;cin>>n;
    vector<pair<int,int>> c(n);
    auto sumb=0;
    for(auto&[a,b]:c) cin>>a>>b,sumb+=b;
    vector f(2,vector(sumb+1,vector<int>(sumb+1)));
    auto cur=0;
    f[cur][0][0]=0;
    auto pre=0;
    for(auto&[a,b]:c){
        for(auto&x:f[cur^1]) ranges::fill(x,_inf);
        cir(wa,0,pre+1) cir(wb,0,pre+1){
            f[cur^1][wa+b][wb]=min(f[cur^1][wa+b][wb],f[cur][wa][wb]+(a!=1));
            f[cur^1][wa][wb+b]=min(f[cur^1][wa][wb+b],f[cur][wa][wb]+(a!=2));
            f[cur^1][wa][wb]=min(f[cur^1][wa][wb],f[cur][wa][wb]+(a!=3));
        }
        pre+=b;cur^=1;        
    }
    cout<<((sumb%3||f[cur][sumb/3][sumb/3]==_inf)?-1:f[cur][sumb/3][sumb/3])<<'\n';
    return 0;
}
