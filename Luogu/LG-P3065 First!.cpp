#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using graph=vector<vector<int>>;
template<size_t siz>
class trie{
private:
    const int alpnum=26;
    struct Node{
        unordered_map<char,int> ch;
        bool ed;
    };
    vector<Node> nd;int cnt;
    int nid(Node&nd,char nxt){
        if(!nd.ch.count(nxt)) nd.ch[nxt]=++cnt;
        return nd.ch[nxt];
    }
    int id(char c){return c-'a';}
    bool makegr(string&s,graph&G){
        int u=0;
        for(auto&i:s){
            if(nd[u].ed) return false;
            for(auto&j:nd[u].ch) if(j.first!=i)
                G[id(i)].push_back(id(j.first));
            u=nid(nd[u],i);
        }
        return true;
    }
    bool dfs(int u,vector<int>&vis,graph&G){
        vis[u]=-1;
        for(auto&i:G[u]){
            if(vis[i]==-1||((!vis[i])&&(!dfs(i,vis,G))))
                return false;
        }
        return vis[u]=true;
    }
public:
    trie():nd(siz),cnt(0){}
    void insert(string&s){
        int u=0;
        for(auto&i:s) u=nid(nd[u],i);
        nd[u].ed=true;
    }
    bool top_sort(string&s){
        graph G(alpnum);vector<int> vis(alpnum);
        if(!makegr(s,G)) return false;
        cir(i,0,alpnum) if((!vis[i])&&(!dfs(i,vis,G)))
            return false;
        return true;
    }
};
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n;cin>>n;vector<string> vs(n),ans;
    const int mxsz=3e5+7;trie<mxsz> Tr;
    for(auto&i:vs) cin>>i,Tr.insert(i);
    for(auto&i:vs) if(Tr.top_sort(i)) ans.push_back(i);
    cout<<ans.size()<<'\n';
    for(auto&i:ans) cout<<i<<'\n';
    return 0;
}