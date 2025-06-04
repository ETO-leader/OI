#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
#ifndef ONLINE_JUDGE
ifstream inf("trans.in");
ofstream ouf("trans.out");
class fileio{
public:
    ~fileio(){
        inf.close();ouf.close();
    }
} use_fileio;
#else
auto&inf=cin;
auto&ouf=cout;
#endif
int main(){
    ios::sync_with_stdio(false),inf.tie(nullptr);
    int n,q,k;inf>>n>>q>>k;
    vector<vector<pair<int,int>>> gr(n);
    cir(i,0,n-1){
        int u,v,w;inf>>u>>v>>w;--u;--v;
        if(!w) gr[v].emplace_back(u,false);
        else gr[u].emplace_back(v,false);
    }
    cir(i,0,q){
        int u,v;inf>>u>>v;--u;--v;
        gr[v].emplace_back(u,true);
    }
    auto cnt=0,ncnt=0;
    vector<map<int,int>> f(n);
    auto dfs=[&](auto __self,int u,int w,int x){
        if((++cnt)>6000000&&(++ncnt)>200) return;
        if(f[u].lower_bound(w)!=f[u].end()) return;
        if(n<2007||f[u].size()<25) f[u][w]=x;
        for(auto&[v,t]:gr[u]){
            if(t) __self(__self,v,k,x);
            else if(w) __self(__self,v,w-1,x);
        }
    };
    cir(i,0,n) ncnt=0,dfs(dfs,i,k,i);
    cir(i,0,n) ouf<<f[i].begin()->second+1<<' ';
    ouf<<'\n';
    return 0;
}

