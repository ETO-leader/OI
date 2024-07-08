#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using VI=vector<int>;
class graph{
    vector<VI> G;
    VI nw,sw,scc,st,dfn,low,in_s;
    int dfncnt;
    void tarjan(int u){
        dfn[u]=low[u]=++dfncnt;
        st.push_back(u);in_s[u]=true;
        for(auto&i:G[u]){
            if(!dfn[i])
                tarjan(i),low[u]=min(low[u],low[i]);
            else
                low[u]=min(low[u],dfn[i]);
        }
        if(low[u]==dfn[u]){
            
        }
    }
};
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    return 0;
}