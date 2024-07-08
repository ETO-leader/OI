#include<bits/stdc++.h>
using namespace std;
using lint=long long;
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n;cin>>n;vector<lint> b(n/2),a1,a2;
    for(auto&i:b) cin>>i;
    lint l=0,r=1e18+7;
    for(auto&i:b){
        if(i>l+r) l+=(i-(l+r));
        else r-=((l+r)-i);
        a1.push_back(l);
        a2.push_back(r);
    }
    reverse(a2.begin(),a2.end());
    for(auto&i:a1) cout<<i<<' ';
    for(auto&i:a2) cout<<i<<' ';
    cout<<'\n';
    return 0;
}
