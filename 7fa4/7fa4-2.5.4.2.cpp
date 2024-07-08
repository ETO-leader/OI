#include<bits/stdc++.h>
using namespace std;
using lint=long long;
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n,m;cin>>n>>m;vector<lint> vl(n);
    m=n-m;
    for(auto&i:vl) cin>>i;
    sort(vl.begin(),vl.end());
    auto ck=[&](lint mid){
        lint lap=-mid,lef=0,pt=0;
        while(pt<n){
            while(pt<n&&vl[pt]-lap<mid) ++pt,++lef;
            lap=vl[pt];++pt;
        }
        return lef;
    };
    lint l=0,r=1e18+7,ans=-1;
    while(r>=l){
        lint mid=(l+r)/2;
        ck(mid)<=m?l=mid+1,ans=mid:r=mid-1;
    }
    cout<<ans<<endl;
    return 0;
}