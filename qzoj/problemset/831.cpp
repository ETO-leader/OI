#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int n,m;cin>>n>>m;
    vector<vector<pair<int,int>>> vx(n+1);
    cir(i,0,m){
        int u,v;cin>>u>>v;
        vx[u].emplace_back(v,i);
        vx[v].emplace_back(u,i);
    }
    vector<int> vis(m);
    vector<int> ans;
    auto dfs=[&](auto __self,int u)->void {
        while(!vx[u].empty()){
            const auto[v,id]=vx[u].back();vx[u].pop_back();
            if(vis[id]) continue;
            vis[id]=true;
            __self(__self,v);
        }
        ans.emplace_back(u);
    };
    auto p=1,cnt=0;
    cir(i,0,n+1) if(!vx[i].empty()) p=i;
    cir(i,0,n+1) if(vx[i].size()&1) p=i,++cnt;
    dfs(dfs,p);
    if((int)(ans.size())==m+1&&((cnt==0)||(cnt==2))){
        cout<<1<<'\n';
        reverse(ans.begin(),ans.end());
        if(m) for(auto&i:ans) cout<<i<<' ';
        cout<<'\n';
    }else{
        cout<<0<<'\n';
    }
    return 0;
}
