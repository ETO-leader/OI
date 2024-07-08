#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using VI=vector<int>;
auto mindiff(VI&a,VI&b){
    const int n=a.size();
    unordered_map<int,int> pos;
    VI cnt(n);
    cir(i,0,n) pos[a[i]]=i;
    cir(i,0,n) if(pos.count(b[i]))
        ++cnt[(i+n-pos[b[i]])%n];
    return *max_element(cnt.begin(),cnt.end());
}
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n,k;cin>>n>>k;VI a(k),b(k);
    unordered_set<int> aps;
    for(auto&i:a) cin>>i,aps.insert(i);
    for(auto&i:b) cin>>i,aps.insert(i);
    auto ans=mindiff(a,b);
    reverse(b.begin(),b.end());
    ans=max(ans,mindiff(a,b));
    reverse(b.begin(),b.end());
    cout<<ans+(n-aps.size())<<'\n';
    return 0;
}
