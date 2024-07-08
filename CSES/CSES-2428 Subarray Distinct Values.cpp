#include<bits/stdc++.h>
using namespace std;
using lint=long long;
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n,k;cin>>n>>k;vector<int> v(n);
    unordered_map<int,int> um;
    for(auto&i:v) cin>>i;
    lint ans=0;int l=0,r=0;
    while(r<n){
        um[v[r]]++;
        while(um.size()>k){
            um[v[l]]--;
            if(!um[v[l]]) um.erase(v[l]);
            ++l;
        }
        ans+=(r-l+1);++r;
    }
    cout<<ans<<'\n';
    return 0;
}