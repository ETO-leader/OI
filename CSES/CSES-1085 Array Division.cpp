#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
const lint _inf=1e18+7;
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n,k;cin>>n>>k;vector<int> v(n);
    for(auto&i:v) cin>>i;
    auto chk=[&v,&k](lint mid){
        if(mid<*max_element(v.begin(),v.end())) return false;
        lint sum=0,cnt=0;
        for(auto&i:v) if((sum+=i)>mid) sum=i,++cnt;
        return cnt+(sum>0)<=k;
    };
    lint l=0,r=_inf,ans=-1;
    while(l<=r){
        lint mid=(l+r)/2;
        chk(mid)?r=mid-1,ans=mid:l=mid+1;
    }
    cout<<ans<<'\n';
    return 0;
}