#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
static constexpr auto _infl=(lint)(1e16l);
class graph{
private:
    struct edge{
        int v;lint w;
        edge(int _v,lint _w):v(_v),w(_w){}
    };
    vector<vector<edge>> gr;
    auto spfa(int ux){
        vector dis(gr.size(),_infl);
        vector<int> inq(gr.size());
        queue<int> q;q.push(ux);dis[ux]=0;
        while(!q.empty()){
            const auto u=q.front();q.pop();
            inq[u]=false;
            for(auto&[v,w]:gr[u]) if(dis[u]+w<dis[v]){
                dis[v]=dis[u]+w;
                if(!inq[v]) q.push(v);
                inq[v]=true;
            }
        }
        return dis;
    }
public:
    auto link(int u,int v,lint w){
        gr[u].emplace_back(v,w);
    }
    auto sp(const auto u){return spfa(u);}
    graph(int _n):gr(_n){}
};
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int n,m;cin>>n>>m;graph gr(n+1);
    cir(v,1,n+1) gr.link(0,v,0);
    cir(i,0,m){
        int u,v,w;string c;cin>>u>>v>>w>>c;
        if(c=="<") gr.link(u,v,w-1);
        else if(c=="=") gr.link(v,u,-w),gr.link(u,v,w);
        else gr.link(v,u,-w-1);
    }
    const auto dis=gr.sp(0);
    auto ans=0ll,mn=*max_element(dis.begin(),dis.end());
    cir(i,1,n+1) ans+=-dis[i]-mn+1;
    cout<<ans<<'\n';
    return 0;
}
