#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    vector<vector<int>> t(2,vector<int>(4));
    for(auto&x:t) for(auto&i:x) cin>>i;
    vector<vector<int>> s(2,vector<int>(4));
    for(auto&x:s) for(auto&i:x) cin>>i;
    auto depth=0;
    map<vector<vector<int>>,int> vis;
    auto dfs=[&](auto __self,vector<vector<int>> cur,int lst)->bool {
        if(vis.count(cur)&&vis[cur]>lst-1) return false;
        if(cur==t){
            cout<<depth<<'\n';
            for(auto&x:cur){
                for(auto&i:x) cout<<i<<' ';
                cout<<'\n';
            }
            return true;
        }
        vis[cur]=lst;
        if(!lst) return false;
        auto nxt=cur;
        swap(nxt[0],nxt[1]);
        if(__self(__self,nxt,lst-1)){
            for(auto&x:cur){
                for(auto&i:x) cout<<i<<' ';
                cout<<'\n';
            }
            return true;
        }
        nxt=cur;
        nxt[0].emplace_back(nxt[0].front());
        nxt[0].erase(nxt[0].begin());
        nxt[1].emplace_back(nxt[1].front());
        nxt[1].erase(nxt[1].begin());
        if(__self(__self,nxt,lst-1)){
            for(auto&x:cur){
                for(auto&i:x) cout<<i<<' ';
                cout<<'\n';
            }
            return true;
        }
        nxt=cur;
        nxt[0][1]=cur[0][2];
        nxt[0][2]=cur[1][2];
        nxt[1][2]=cur[1][1];
        nxt[1][1]=cur[0][1];
        if(__self(__self,nxt,lst-1)){
            for(auto&x:cur){
                for(auto&i:x) cout<<i<<' ';
                cout<<'\n';
            }
            return true;
        }
        return false;
    };
    while(!dfs(dfs,s,depth)) ++depth;
    return 0;
}
