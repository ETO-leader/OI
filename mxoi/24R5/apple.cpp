#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
ifstream fcin("apple.in");
ofstream fcout("apple.ans");
class fileio{
public:
    ~fileio(){
        fcin.close();fcout.close();
    }
} use_fileio;
class tree{
private:
    vector<vector<int>> gr;
public:
    auto insert(int u,int v){
        gr[u].push_back(v);
        gr[v].push_back(u);
    }
    auto dfs(int u,vector<vector<int>>&dis,int h=-1,int f=-1)->void{
        dis[++h].push_back(u);
        for(auto&i:gr[u]) if(i!=f) dfs(i,dis,h,u);
    }
    tree(int _n):gr(_n){}
};
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n;fcin>>n;tree gr(n);
    if(n>50000) exit((fcout<<"Never gonna give you up!\n",0));
    cir(i,0,n-1){
        int u,v;fcin>>u>>v;--u;--v;
        gr.insert(u,v);
    }
    string s;fcin>>s;
    mt19937_64 rnd(random_device().operator()());
    vector<uint64_t> rd(n);
    for(auto&i:rd) i=rnd();
    unordered_set<uint64_t> ans;
    cir(i,0,n) if(s[i]=='1'){
        vector<vector<int>> dis(n);
        gr.dfs(i,dis);
        auto wx=0ull;
        for(auto&x:dis){
            for(auto&u:x) wx^=rd[u];
            ans.insert(wx);
        }
    }
    fcout<<ans.size()<<'\n';
    return 0;
}
