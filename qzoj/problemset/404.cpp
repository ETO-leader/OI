#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int n,k;cin>>n>>k;
    vector<lint> w(n);
    for(auto&i:w) cin>>i;
    sort(w.begin(),w.end());
    vector<lint> a;
    cir(i,1,n) a.emplace_back(w[i]-w[i-1]);
    a.emplace(a.begin(),(lint)(1e15l));
    a.emplace(a.end(),(lint)(1e15l));
    priority_queue<pair<lint,int>,vector<pair<lint,int>>,greater<>> q;
    cir(i,0,n+1) q.emplace(a[i],i);
    set<int> ok,vis;
    cir(i,0,n+1) ok.emplace(i);
    auto ans=0ll;
    cir(i,0,k){
        while(!ok.count(q.top().second)) q.pop();
        const auto[uw,u]=q.top();q.pop();
        ans+=uw;
        const auto lp=*prev(ok.lower_bound(u));
        const auto rp=*ok.upper_bound(u);
        q.emplace(a[u]=(a[lp]+a[rp]-uw),u);
        ok.erase(lp);
        ok.erase(rp);
    }
    cout<<ans<<'\n';
    return 0;
}
