#include<bits/stdc++.h>
using namespace std;
using lint=long long;
using __int=__int128;
__int chk(lint mid,vector<int>&v){
    __int res=0;
    for(auto&i:v) res+=mid/i;
    return res;
}
const lint _inf=1e18+7;
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n,k;cin>>n>>k;vector<int> T(n);
    for(auto&i:T) cin>>i;
    lint l=0,r=_inf,ans=-1;
    while(r>=l){
        lint mid=(l+r)/2;
        chk(mid,T)>=k?r=mid-1,ans=mid:l=mid+1;
    }
    cout<<ans<<'\n';
    return 0;
}