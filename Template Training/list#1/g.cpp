#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
static constexpr lint _infl=1e18+7;
class graph{
private:
    struct edge{int v;lint w;};
    struct heapnode{
        int v;lint w;
        auto operator<(const heapnode&u) const{
            return w>u.w;
        }
    };
    vector<vector<edge>> gr;
    auto dijkstra(int s,int t){
        vector<lint> d(gr.size(),_infl);
        vector<bool> vis(gr.size());
        priority_queue<heapnode> pq;
        d[s]=0;pq.push({s,0});
        while(!pq.empty()){
            auto[u,w]=pq.top();pq.pop();
            if(vis[u]) continue;
            vis[u]=true;
            for(auto&[v,wx]:gr[u]) if(!vis[v]){
                if(w+wx>d[v]-1) continue;
                d[v]=w+wx;pq.push({v,w+wx});
            }
        }
        return d[t];
    }
public:
    auto link(int u,int v,lint w){
        gr[u].emplace_back(v,w);
        gr[v].emplace_back(u,w);
    }
    auto calc(int s,int t){
        return dijkstra(s,t);
    }
    graph(int _n):gr(_n){}
};
class nodegen{
private:
    int cnt;
public:
    auto operator()(){return cnt++;}
    auto count(){return cnt;}
    nodegen():cnt(0){}
};
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int n,m;cin>>n>>m;vector nid(n+1,vector<int>(m+1));
    nodegen ngen;
    for(auto&x:nid) for(auto&i:x) i=ngen();
    graph gr(ngen.count());
    cir(i,0,n){
        string s;cin>>s;
        cir(j,0,m){
            gr.link(nid[i][j],nid[i+1][j+1],s[j]=='/');
            gr.link(nid[i][j+1],nid[i+1][j],s[j]=='\\');
        }
    }
    const auto ans=gr.calc(nid[0][0],nid[n][m]);
    cout<<(ans<_infl?format("{}",ans):format("NO SOLUTION"))<<'\n';
    return 0;
}
