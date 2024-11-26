#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int n;cin>>n;vector<int> a(n),b(n);
    for(auto&i:a) cin>>i;
    for(auto&i:b) cin>>i;
    vector<int> cur(n);
    priority_queue<pair<int,int>,vector<pair<int,int>>,greater<pair<int,int>>> q;
    cir(i,0,n) q.emplace(a[i]+b[0],i);
    cir(i,0,n){
        const auto[w,u]=q.top();q.pop();
        cout<<w<<' ';
        ++cur[u];
        if(cur[u]<n) q.emplace(a[u]+b[cur[u]],u);
    }
    cout<<'\n';
    return 0;
}
