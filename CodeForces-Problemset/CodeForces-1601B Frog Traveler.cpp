#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using VI=vector<int>;
const int _inf=1e9+7;
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n;cin>>n;VI a(n),b(n),c(n+1);
    for(auto&i:a) cin>>i;
    for(auto&i:b) cin>>i;
    a.insert(a.begin(),0);
    b.insert(b.begin(),0);
    cir(i,1,n+1) c[i]=max(0,i+b[i]-a[i+b[i]]);
    VI mn(n+2,_inf),f(n+2,_inf);
    for(int i=n;i;--i){
        mn[i]=min({mn[i+1],i,c[i]});
        f[i]=min(i,c[i])<mn[i+1]?i:f[i+1];
    }
    int p=n,cur=0;VI ans;
    while(p&&(cur++)<n){
        ans.push_back((p=f[p]));
        if(p<mn[p]+1) break;
        p=mn[p];
    }
    if(p) exit(((cout<<"-1\n"),0));
    cout<<ans.size()<<'\n';
    ans.erase(ans.begin());
    for(auto&i:ans) cout<<i<<' ';
    cout<<0<<'\n';
    return 0;
}
