#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
#define NoSolution\
    {cout<<"IMPOSSIBLE\n";exit(0);}
using namespace std;
using idedge=pair<int,int>;
vector<vector<idedge>> G;
vector<int> run(vector<int>&Rin,int n,int m){
    cir(i,2,n) if(Rin[i]!=G[i].size()) NoSolution;
    if(Rin[1]>=G[1].size()||G[1].size()-Rin[1]>1) NoSolution;
    if(Rin[n]<=G[n].size()||Rin[n]-G[n].size()>1) NoSolution;
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
    reverse(res.begin(),res.end());
    return res;
}
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n,m;cin>>n>>m;G.resize(n+1);
    vector<int> Rin(n+1);
    cir(i,0,m){
        int u,v;cin>>u>>v;Rin[v]++;
        G[u].push_back({v,i});
    }
    auto data=run(Rin,n,m);
    if(data.size()!=m+1) NoSolution;
    for(auto&i:data) cout<<i<<' ';
    cout<<'\n';
    return 0;
}