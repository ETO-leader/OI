#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
vector<unordered_set<int>> G;
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n,q;cin>>n>>q;G.resize(n+1);
    int cnx=n;
    cir(i,0,q){
        int op;cin>>op;
        if(op==1){
            int u,v;cin>>u>>v;
            G[u].insert(v);G[v].insert(u);
            cnx-=(G[u].size()==1);
            cnx-=(G[v].size()==1);
        }else{
            int x;cin>>x;
            cnx+=(!G[x].empty());
            for(auto&i:G[x]){
                assert(G[i].count(x));
                G[i].erase(x);
                cnx+=G[i].empty();
            }
            G[x].clear();
        }
        cout<<cnx<<'\n';
    }
    return 0;
}
