#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
static constexpr auto _infl=(lint)(1e16l);
class graph{
private:
    vector<vector<pair<int,lint>>> gr;
public:
    auto link(int u,int v,lint w){
        gr[u].emplace_back(v,w);
    }
    auto spfa(int s){
        const auto n=(int)(gr.size());
        queue<int> q;q.emplace(s);
        vector<lint> dis(n,_infl);
        vector<int> inq(n),visc(n);
        dis[s]=0;
        while(!q.empty()){
            const auto u=q.front();q.pop();
            inq[u]=false;
            if((++visc[u])>n) return false;
            for(auto&[v,w]:gr[u]) if(dis[u]+w<dis[v]){
                dis[v]=dis[u]+w;
                if(!inq[v]) q.emplace(v);
                inq[v]=true;
            }
        }
        return true;
    }
    graph(int _n):gr(_n){}
};
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int n,m;cin>>n>>m;graph gr(n+1);
    cir(i,0,m){
        int op;cin>>op;
        if(op==1){
            int u,v;lint w;cin>>u>>v>>w;
            gr.link(u,v,-w);
        }else if(op==2){
            int u,v;lint w;cin>>u>>v>>w;
            gr.link(v,u,w);
        }else{
            int u,v;cin>>u>>v;
            gr.link(u,v,0);
            gr.link(v,u,0);
        }
    }
    cir(i,1,n+1) gr.link(0,i,0);
    cout<<(gr.spfa(0)?"Yes":"No")<<'\n';
    return 0;
}
