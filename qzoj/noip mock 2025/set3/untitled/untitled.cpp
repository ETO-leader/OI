#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int n;cin>>n;
    vector<set<int>> a(n);
    vector<int> ans(n,-1);
    cir(i,0,n) cir(j,0,n){
        int x;cin>>x;--x;
        if(x!=i) a[i].emplace(x);
    }
    vector<int> vis(n);
    cir(c,0,n) cir(i,0,n) if(a[i].empty()&&(!vis[i])){
        vis[i]=true;
        cir(p,0,n) if(a[p].count(i)){
            ans[p]=i;
            a[p].erase(i);
        }
        break;
    }
    for(auto&i:ans) cout<<i+1<<' ';
    cout<<'\n';
    return 0;
}
