#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
ifstream inf("aba.in");
ofstream ouf("aba.out");
class fileio{
public:
    ~fileio(){
        inf.close();ouf.close();
    }
} use_fileio;
int main(){
    ios::sync_with_stdio(false),inf.tie(nullptr);
    int n,r,a,b;inf>>n>>r>>a>>b;
    --r;
    if(a<b+1){
        ouf<<1<<'\n';
        exit(0);
    }
    vector<vector<int>> gr(n);
    cir(i,0,n-1){
        int u,v;inf>>u>>v;--u;--v;
        gr[u].emplace_back(v);
        gr[v].emplace_back(u);
    }
    if(gr[r].size()==n-1){
        ouf<<1<<'\n';
        exit(0);
    }
    auto ok=true;
    cir(i,1,n-1) ok&=count(gr[i].begin(),gr[i].end(),i+1);
    if(ok){
        // if(!r) ouf<<
    } 
    return 0;
}
