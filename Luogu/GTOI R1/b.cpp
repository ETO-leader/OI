#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int n;cin>>n;vector<int> a(n);
    for(auto&i:a) cin>>i,--i;
    vector<int> rpos(n);
    cir(i,0,n) rpos[a[i]]=i;
    vector<int> rw(n);
    cir(i,1,n) rw[min(rpos[i-1],rpos[i])]=max({rpos[i-1],rpos[i],rw[min(rpos[i-1],rpos[i])]});
    auto ans=1;
    auto p=0,mxr=rw[0];
    while(mxr<n-1){
        ++ans;
        const auto nr=mxr;
        for(;p<min(n,nr+1);++p) mxr=max(mxr,rw[p]);
        if(p<n) mxr=max(mxr,rw[p]);
    }
    cout<<ans<<'\n';
    return 0;
}
