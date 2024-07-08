#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
class graph{
private:
    vector<vector<int>> gr;
    vector<int> dfn,low,scc,stc,ins;
    int dfncnt,scccnt;
    auto tarjan(int u)->void{
        dfn[u]=low[u]=++dfncnt;
        stc.push_back(u);ins[u]=true;
        for(auto&i:gr[u]){
            if(!dfn[i]){
                tarjan(i);low[u]=min(low[u],low[i]);
            }else if(ins[i]){
                low[u]=min(low[u],dfn[i]);
            }
        }
        if(low[u]==dfn[u]){
            int ux=-1;++scccnt;
            while(ux!=u){
                ux=stc.back();stc.pop_back();
                ins[ux]=false;scc[ux]=scccnt-1;
            }
        }
    }
public:
    auto insert(int u,int v){
        gr[u].push_back(v);
    }
    auto init(){
        cir(i,0,(int)(gr.size())) if(!dfn[i]) tarjan(i);
    }
    auto check(int u,int v){
        return scc[u]==scc[v];
    }
    graph(int _n):gr(_n),dfn(_n),dfncnt(0),
        low(_n),scc(_n),ins(_n),scccnt(0){}
};
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n;cin>>n;unordered_map<string,int> ids;
    stringstream rcin,scin;
    cir(i,0,n){
        string g,b;cin>>g>>b;
        rcin<<g<<' '<<b<<'\n';
        scin<<g<<' '<<b<<'\n';
        ids.insert({g,0});
        ids.insert({b,0});
    }
    [&](){int c=0;for(auto&[a,b]:ids) b=c++;}();
    graph gr(n*2);
    cir(i,0,n){
        string g,b;rcin>>g>>b;
        gr.insert(ids[g],ids[b]);
    }
    int q;cin>>q;
    cir(i,0,q){
        string g,b;cin>>g>>b;
        gr.insert(ids[b],ids[g]);
    }
    gr.init();
    cir(i,0,n){
        string g,b;scin>>g>>b;
        cout<<(gr.check(ids[g],ids[b])?"Unsafe":"Safe")<<'\n';
    }
    return 0;
}
