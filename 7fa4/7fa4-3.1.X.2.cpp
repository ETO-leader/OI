#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
vector<vector<int>> G;
vector<int> Tin,ans;
#define impossible()\
    {cout<<"Impossible!\n";return false;}
bool topsort(int n){
    priority_queue<int> pq;
    cir(i,1,n+1) if(!Tin[i]) pq.push(i);
    while(!pq.empty()){
        int ux=pq.top();pq.pop();
        ans.push_back(ux);
        for(auto&i:G[ux]) if(!(--Tin[i]))
            pq.push(i);
    }
    if(*max_element(Tin.begin(),Tin.end()))
        impossible();
    return true;
}
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int T;cin>>T;
    while(T--){
        int n,m;cin>>n>>m;
        G.clear();Tin.clear();
        G.resize(n+1);Tin.resize(n+1);
        cir(i,0,m){
            int u,v;cin>>u>>v;
            G[v].push_back(u);Tin[u]++;
        }
        auto tag=topsort(n);
        reverse(ans.begin(),ans.end());
        if(tag){
            for(auto&i:ans) cout<<i<<' ';cout<<'\n';
        }
        ans.clear();
    }
    return 0;
}