#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
const lint _inf=1e15+7;
struct sci{lint t,w;};
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    lint n,m;cin>>n>>m;
    vector<sci> s(n);
    for(auto&[t,w]:s) cin>>t>>w;
    lint l=0,r=_inf,ans=-1;
    while(r>=l){
        const lint mid=(l+r)/2;
        [&](){
            lint wx=0,mx=0;
            for(auto&[t,w]:s) if(t<mid){
                wx+=(mid-t)*w;
                mx=max(mx,(mid-t)*w);
                if(wx-mx>m-1) return true;
            }
            return false;
        }()?((r=mid-1),(ans=mid)):(l=mid+1);
    }
    cout<<ans<<'\n';
    return 0;
}
