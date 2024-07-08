#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
#define NoSolution\
    {cout<<"IMPOSSIBLE\n";exit(0);}
using namespace std;
using idedge=pair<int,int>;
vector<vector<idedge>> G;
vector<int> run(int m){
    if(accumulate(G.begin(),G.end(),0,[](int&a,auto&b){
        return a+(b.size()&1);})) NoSolution;
    vector<int> res,vis(m);
    stack<int> st;st.push(1);
    while(!st.empty()){
        auto u=st.top();
        while(!G[u].empty()){
            auto bk=G[u].back();G[u].pop_back();
            auto v=bk.first,id=bk.second;
            if(!vis[id]){st.push(v);vis[id]=true;goto nxt;}
        }
        res.push_back(u);st.pop();
        nxt:;
    }
    return res;
}
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n,m;cin>>n>>m;G.resize(n+1);
    cir(i,0,m){
        int u,v;cin>>u>>v;
        G[u].push_back({v,i});G[v].push_back({u,i});
    }
    auto data=run(m);
    if(data.size()!=m+1) NoSolution;
    for(auto&i:data) cout<<i<<' ';
    cout<<'\n';
    return 0;
}