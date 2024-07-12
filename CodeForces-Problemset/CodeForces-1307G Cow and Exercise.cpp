#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
static constexpr auto _inf=(lint)(1e14l);
class ek_algorithm{
private:
    struct edge{
        int v,rev;lint w,fl;
    };
    vector<vector<edge>> gr;
    auto spfa(int s,int t){
        queue<int> q;q.push(s);
        vector dis(gr.size(),_inf);
        vector<int> inq(gr.size()),fr(gr.size()),ex(gr.size());
        dis[s]=0;
        while(!q.empty()){
            const auto u=q.front();q.pop();
            inq[u]=false;
            for(auto c=-1;auto&[v,rev,w,fl]:gr[u]){
                ++c;
                if(!(fl&&dis[u]+w<dis[v])) continue;
                dis[v]=dis[u]+w;fr[v]=u;ex[v]=c;
                if(!inq[v]) q.push(v);
                inq[v]=true;
            }
        }
        return tuple(dis[t]<_inf,fr,ex);
    }
public:
    auto insert(int u,int v,lint w,lint fl){
        gr[u].push_back({v,(int)(gr[v].size()),w,fl});
        gr[v].push_back({u,(int)(gr[u].size())-1,-w,0ll});
    }
    auto flow(int s,int t){
        vector<pair<lint,lint>> res;
        auto fl=0ll,cst=0ll;
        while(true){
            auto[ok,fr,ex]=spfa(s,t);
            if(!ok) break;
            auto flx=_inf;auto u=t;
            while(u!=s){
                const auto rex=ex[u];
                u=fr[u];
                flx=min(flx,gr[u][rex].fl);
            }
            auto cstx=0ll;u=t;
            while(u!=s){
                const auto v=u;
                const auto rex=ex[u];
                u=fr[u];
                cstx+=gr[u][rex].w*flx;
                gr[u][rex].fl-=flx;
                gr[v][gr[u][rex].rev].fl+=flx;
            }
            res.push_back({fl+=flx,cst+=cstx});
        }
        return res;
    }
    ek_algorithm(int n):gr(n){}
};
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int n,m;cin>>n>>m;ek_algorithm gr(n);
    const auto s=0,t=n-1;
    cir(i,0,m){
        int u,v,w;cin>>u>>v>>w;
        gr.insert(u-1,v-1,w,1);
    }
    const auto ax=gr.flow(s,t);
    int q;cin>>q;
    cir(i,0,q){
        int x;cin>>x;
        auto ans=1e18l;
        for(auto&[a,b]:ax) ans=min(ans,(long double)(b+x)/a);
        cout<<fixed<<setprecision(15)<<ans<<'\n';
    }
    return 0;
}
