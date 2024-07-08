#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using VI=vector<int>;
class dsu{
private:
    VI f;
public:
    int findset(int x){
        return f[x]==x?x:(f[x]=findset(f[x]));
    }
    void merge(int x,int y){
        f[findset(x)]=findset(y);}
    dsu(int x):f(x){
        iota(f.begin(),f.end(),0);}
};
struct edge{int v,eid;};
vector<vector<edge>> G;
vector<edge> fx;
void dfs(int u,int f=0){
    for(auto&[v,ex]:G[u]) if(v!=f)
        dfs(v,u),fx[v]={u,ex};
}
ostream&operator<<(ostream&os,VI v){
    if(!v.empty()) os<<v[0];
    cir(i,1,v.size()) os<<' '<<v[i];
    return os;
}
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int T;cin>>T;
    while(T--){
        int n,m;cin>>n>>m;
        G.clear();fx.clear();
        G.resize(n+1);fx.resize(n+1);
        [&](){
            dsu ds(n+1);
            stringstream iostr;
            cir(i,0,m){
                int u,v;cin>>u>>v;
                iostr<<u<<' '<<v<<'\n';
            }
            cir(i,0,m){
                int u,v;iostr>>u>>v;
                if(ds.findset(u)==ds.findset(v)){
                    dfs(u);VI ans(1,i+1);
                    while(u!=v){
                        ans.push_back(fx[v].eid);
                        v=fx[v].v;
                    }
                    sort(ans.begin(),ans.end());
                    cout<<ans<<'\n';
                    return;
                }
                ds.merge(u,v);
                G[u].push_back({v,i+1});
                G[v].push_back({u,i+1});
            }
            cout<<-1<<'\n';
        }();
    }
    return 0;
}
