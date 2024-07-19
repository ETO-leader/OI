#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int T;cin>>T;
    while(T--) [&](){
        int n,x;cin>>n>>x;
        vector<int> a(n),nxt(n,-1);
        for(auto&i:a) cin>>i;
        auto r=-1;auto wx=0ll;
        cir(l,0,n){
            if(l) wx-=a[l-1];
            while(r<n-1&&wx<x+1) wx+=a[++r];
            if(wx>x) nxt[l]=r;
        }
        vector<lint> f(n);
        auto ans=0ll;
        cir(i,0,n){
            if(nxt[i]>-1&&nxt[i]+1<n) f[nxt[i]+1]+=f[i]+1;
            ++f[i];
            ans+=f[i]*max(0,(nxt[i]<0?n:nxt[i])-i);
            // ans+=(a[i]<x+1);
        }
        cout<<ans<<'\n';
    }();
    return 0;
}
