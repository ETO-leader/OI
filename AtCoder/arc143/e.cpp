#include<bits/stdc++.h>
#define cir(i,a,b) for(auto i=a;i<b;++i)
using namespace std;
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int n;cin>>n;
    vector<vector<int>> tr(n);
    cir(i,0,n-1){
        int u,v;cin>>u>>v;--u;--v;
        tr[u].emplace_back(v);
        tr[v].emplace_back(u);
    }
    string s;cin>>s;
    vector<int> col(n);
    cir(i,0,n) col[i]=(s[i]=='B');
    vector<vector<int>> gr(n);
    vector<int> inc(n);
    auto dfs=[&](auto __self,int u,int f)->int {
        for(auto&i:tr[u]) if(i!=f){
            const auto vc=__self(__self,i,u);
            if(!vc){
                gr[i].emplace_back(u);
                col[u]^=true;++inc[u];
            }else{
                gr[u].emplace_back(i);
                ++inc[i];
            }
        }
        return col[u];
    };
    dfs(dfs,0,-1);
    if(col[0]){
        cout<<-1<<'\n';
    }else{
        priority_queue<int,vector<int>,greater<>> q;
        cir(i,0,n) if(!inc[i]) q.emplace(i);
        while(!q.empty()){
            const auto u=q.top();q.pop();
            cout<<u+1<<' ';
            for(auto&i:gr[u]) if(!(--inc[i])) q.emplace(i);
        }
        cout<<'\n';
    }
    return 0;
}
