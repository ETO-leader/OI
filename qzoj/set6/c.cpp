#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int n,q;lint m;cin>>m>>n>>q;
    vector<lint> a(n);
    for(auto&i:a) cin>>i;
    a.emplace(a.begin(),0);
    a.emplace_back(m+1);
    priority_queue<pair<lint,lint>> qx;
    cir(i,1,n+2) qx.emplace(a[i]-a[i-1]-1,-(a[i-1]+1));
    vector<lint> id(q);
    for(auto&i:id) cin>>i;
    unordered_map<lint,lint> ans;
    for(auto&x:id) ans.emplace(x,0);
    const auto mx=*max_element(id.begin(),id.end());
    cir(i,0,n) if(ans.count(i+1)) ans[i+1]=a[i+1];
    cir(i,0,mx){
        const auto[len,p]=qx.top();qx.pop();
        const auto l=-p,r=(-p)+len-1;
        const auto mid=(l+r)/2;
        if(ans.count(i+n+1)) ans[i+n+1]=mid;
        qx.emplace((mid-1)-l+1,-l);
        qx.emplace(r-(mid+1)+1,-(mid+1));
    }
    for(auto&x:id) cout<<ans[x]<<'\n';
    return 0;
}
