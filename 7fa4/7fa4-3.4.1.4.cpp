#include<bits/stdc++.h>
using namespace std;
class trie01{
private:
    struct node{
        vector<node*> s;
        node():s(2,NULL){}
    };
    node*root;
    const size_t len=31;
    using basic_T=int;
public:
    void insert(basic_T ins){
        node*u=root;
        for(int i=len;~i;--i){
            int nxt=(ins>>i)&1;
            if(!u->s[nxt]) u->s[nxt]=new node();
            u=u->s[nxt];
        }
    }
    basic_T xormax(basic_T fnd){
        node*u=root;
        basic_T res=0;
        for(int i=len;~i;--i){
            int nxt=((fnd>>i)&1)^1;
            if(!u->s[nxt]) nxt^=1;
            (res<<=1)|=nxt;
            u=u->s[nxt];
        }
        return res;
    }
    trie01(){root=new node();}
};
struct edge{int v,w;};
vector<vector<edge>> G;
vector<int> wi;
trie01 tr;
void dfs(int u,int w=0,int f=0){
    for(auto&[v,wx]:G[u]) if(v!=f)
        dfs(v,w^wx,u);
    tr.insert(w);wi[u]=w;
}
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n;cin>>n;G.resize(n+1);
    wi.resize(n+1);
    for(int i=0;i<n-1;++i){
        int u,v,w;cin>>u>>v>>w;
        G[u].push_back({v,w});
        G[v].push_back({u,w});
    }
    dfs(1);int ans=0;
    for(auto&i:wi)
        ans=max<int>(ans,i^tr.xormax(i));
    cout<<ans<<'\n';
    return 0;
}
