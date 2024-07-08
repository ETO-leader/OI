#include<bits/stdc++.h>
using namespace std;
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n;cin>>n;vector<int> v(n);
    set<int> Aps;
    for(auto&i:v) cin>>i;
    int l=0,r=0,ans=0;
    while(r<n){
        while(Aps.count(v[r]))
            Aps.erase(v[l]),++l;
        Aps.insert(v[r]);
        ans=max(ans,r-l+1);
        ++r;
    }
    cout<<ans<<'\n';
    return 0;
}
