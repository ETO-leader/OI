#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int n,m;cin>>n>>m;
    vector<vector<int>> vx(n);
    vector<int> inc(n);
    cir(i,0,m){
        int u,v;cin>>v>>u;--u;--v;
        vx[u].emplace_back(v);++inc[v];
    }
    vector<int> mxd(n);
    queue<int> q;
    cir(i,0,n) if(!inc[i]) q.emplace(i);
    while(!q.empty()){
        const auto u=q.front();q.pop();
        for(auto&i:vx[u]) if(!(--inc[i])){
            mxd[i]=mxd[u]+1;
            q.emplace(i);
        }
    }
    if(*max_element(inc.begin(),inc.end())){
        cout<<"Poor Xed"<<'\n';
    }else{
        cout<<n*100+accumulate(mxd.begin(),mxd.end(),0)<<'\n';
    }
    return 0;
}
