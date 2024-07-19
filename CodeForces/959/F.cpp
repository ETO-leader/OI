#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int T;cin>>T;
    while(T--) [&](){
        int n,m;cin>>n>>m;
        vector<vector<int>> gr(n);
        vector<int> deg(n),u(m),v(m),w(m),vis(n);
        cir(i,0,m){
            cin>>u[i]>>v[i]>>w[i];
            --u[i];--v[i];
            gr[u[i]].push_back(i);
            gr[v[i]].push_back(i);
            deg[u[i]]^=w[i];
            deg[v[i]]^=w[i];
        }
        auto dfs=[&](auto __self,int ux)->void{
            vis[ux]=true;
            for(auto&i:gr[ux]){
                const auto vx=u[i]^v[i]^ux;
                if(vis[vx]||w[i]) continue;
                __self(__self,vx);
                if(deg[vx]==1){
                    deg[ux]^=1;deg[vx]^=1;w[i]^=1;
                }
            }
        };
        cir(u,0,n) if(!vis[u]){
            dfs(dfs,u);
            if(deg[u]) return cout<<"NO"<<'\n',void();
        }
        vector<int> ans;
        auto check=[&](auto __self,int ux)->void{
            while(!gr[ux].empty()){
                const auto i=gr[ux].back();
                const auto vx=u[i]^v[i]^ux;
                gr[ux].pop_back();
                if(!w[i]) continue;
                w[i]=0;
                __self(__self,vx);
            }
            ans.push_back(ux);
        };
        check(check,0);
        cout<<format("YES\n{}\n",ans.size()-1);
        for(auto&i:ans) cout<<i+1<<' ';
        cout<<'\n';
    }();
    return 0;
}
