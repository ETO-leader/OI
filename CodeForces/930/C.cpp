#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
static constexpr lint _inf=1e18+7;
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
        vector<lint> d(gr.size(),_inf);
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
    auto insert(int u,int v,lint w){
        gr[u].push_back({v,w});
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
    auto getnode(){return cnt++;}
    auto count(){return cnt;}
    nodegen():cnt(0){}
};
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int T;cin>>T;
    while(T--){
        int n,m;cin>>n>>m;vector<lint> c(n);
        for(auto&i:c) cin>>i;
        vector a(n,vector<lint>(m));
        for(auto&i:a) for(auto&x:i) cin>>x;
        nodegen ngen;
        vector oun(n,vector<int>(m));
        vector<int> uin(n);
        for(auto&i:uin) i=ngen.getnode();
        const auto s=ngen.getnode(),t=ngen.getnode();
        for(auto&i:oun) for(auto&x:i) x=ngen.getnode();
        graph gr(ngen.count());
        cir(i,0,n) cir(j,0,m) gr.insert(uin[i],oun[i][j],c[i]);
        cir(i,0,n) cir(j,0,m) gr.insert(oun[i][j],uin[i],0);
        gr.insert(s,uin[0],0);gr.insert(uin[n-1],t,0);
        cir(nw,0,m){
            vector<int> rk(n);
            iota(rk.begin(),rk.end(),0);
            sort(rk.begin(),rk.end(),[&](auto&ax,auto&bx){
                return a[ax][nw]<a[bx][nw];
            });
            cir(i,1,n){
                gr.insert(oun[rk[i-1]][nw],oun[rk[i]][nw],0);
                gr.insert(oun[rk[i]][nw],oun[rk[i-1]][nw],
                    a[rk[i]][nw]-a[rk[i-1]][nw]);
            }
        }
        cout<<gr.calc(s,t)-c[0]+c[n-1]<<'\n';
    }
    return 0;
}
