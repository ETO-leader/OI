#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
class tree{
private:
    vector<vector<int>> gr;
    auto dfs(int u,int f=-1)->pair<int,int>{
        auto res=pair<int,int>(0,u);
        for(auto&i:gr[u]) if(i!=f){
            const auto[w,x]=dfs(i,u);
            res=max(res,{w+1,x});
        }
        return res;
    }
public:
    auto link(int u,int v){
        gr[u].emplace_back(v);
        gr[v].emplace_back(u);
    }
    auto check(){
        return dfs(dfs(0).second).first;
    }
    tree(int _n):gr(_n){}
};
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int n;cin>>n;tree gr(n);
    cir(i,0,n-1){
        int u,v;cin>>u>>v;--u;--v;
        gr.link(u,v);
    }
    cout<<gr.check()<<'\n';
    return 0;
}
