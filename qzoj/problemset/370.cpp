#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int n;cin>>n;
    vector<vector<int>> vx(n+1);
    vector<int> inc(n+1);
    int u,v;
    while(cin>>u>>v){
        vx[u].emplace_back(v);
        ++inc[v];
    }
    stringstream ouf;
    auto dfs=[&](auto __self,int u)->void {
        --inc[u];
        ouf<<u<<' ';
        for(auto&x:vx[u]) if(!(--inc[x])) __self(__self,x);
    };
    cir(i,1,n+1) if(!inc[i]) dfs(dfs,i);
    if(*max_element(inc.begin(),inc.end())>0){
        cout<<"NO"<<'\n';
    }else{
        cout<<ouf.str()<<'\n';
    }
    return 0;
}
