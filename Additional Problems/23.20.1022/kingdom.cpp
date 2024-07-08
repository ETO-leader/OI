#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
ifstream fcin("kingdom.in");
ofstream fcout("kingdom.out");
class fileio{
public:
    ~fileio(){
        fcin.close();fcout.close();
    }
} use_fileio;
using VI=vector<int>;
static constexpr int _inf=1e9+7;
class graph{
private:
    vector<VI> G,scci;
    VI dfn,low,scc,sccsiz,w,ins,stc;
    int dfncnt;
    void tarjan(int u){
        dfn[u]=low[u]=++dfncnt;
        stc.push_back(u);ins[u]=true;
        for(auto&i:G[u]){
            if(!dfn[i]){
                tarjan(i);
                low[u]=min(low[u],low[i]);
            }else if(ins[i]){
                low[u]=min(low[u],dfn[i]);
            }
        }
        if(dfn[u]==low[u]){
            int lx=0;
            sccsiz.push_back(0);
            scci.push_back(VI(0));
            while(lx!=u){
                lx=stc.back();
                sccsiz.back()+=w[lx];
                scc[lx]=sccsiz.size()-1;
                ins[lx]=false;
                scci.back().push_back(lx);
                stc.pop_back();
            }
        }
    }
    int checkdeg(int sccid){
        int res=0;
        for(auto&u:scci[sccid]){
            for(auto&i:G[u]) res+=(scc[i]!=sccid);
        }
        return res;
    }
    int n;
public:
    int get(){
        cir(i,1,n+1) if(!dfn[i]) tarjan(i);
        int res=_inf;
        cir(i,0,sccsiz.size()) if(!checkdeg(i))
            res=min(res,sccsiz[i]);
        return res;
    }
    void insert(int u,int v){G[u].push_back(v)};
    graph(int n):G(n+1),scc(n+1),ins(n+1),
        dfn(n+1),low(n+1),dfncnt(0){}
};
struct node{
    int c,n,u,s;
    int get(){return u+n*s+c;}
};

int main(){
    ios::sync_with_stdio(false),fcin.tie(0);
    int n,c;fcin>>n>>c;

    return 0;
}
