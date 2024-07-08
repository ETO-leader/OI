#include<bits/stdc++.h>
using namespace std;
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n,x;cin>>n>>x;vector<int> v(n);
    for(auto&i:v) cin>>i;
    int val=0,l=0,r=0,ans=0;
    while(r<n){
        val+=v[r];
        while(val>x) val-=v[l],++l;
        ans+=(val==x);++r;
    }
    cout<<ans<<'\n';
    return 0;
}