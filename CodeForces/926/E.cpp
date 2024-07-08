#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using VI=vector<int>;
static constexpr int _inf=1e9+7;
class solver{
private:
    vector<VI> gr,up;
    VI h;
    static constexpr auto ups=21;
    auto dfs(int u,int f=0)->void{
        up[u][0]=f;h[u]=h[f]+1;
        cir(i,1,ups) up[u][i]=up[up[u][i-1]][i-1];
        for(auto&i:gr[u]) if(i!=f) dfs(i,u);
    }
    auto lca(int u,int v){
        if(h[u]<h[v]) swap(u,v);
        cir(i,0,ups) if((h[u]-h[v])&(1<<i))
            u=up[u][i];
        if(u==v) return u;
        for(auto i=ups-1;~i;--i) if(up[u][i]!=up[v][i])
            u=up[u][i],v=up[v][i];
        return up[u][0];
    }
    auto route(int u,int v,int x,int y){
        vector<int> lx={lca(u,x),lca(u,y),lca(v,x),lca(v,y)};
        sort(lx.begin(),lx.end(),[this](int u,int v){
            return h[u]>h[v];
        });
        return pair(lx[0],lx[1]);
    }
public:
    solver(int n):gr(n+1),up(n+1,VI(ups)),h(n+1){
        cir(i,0,n-1){
            int u,v;cin>>u>>v;
            gr[u].push_back(v);gr[v].push_back(u);
        }
        dfs(1);
        int k;cin>>k;vector<pair<int,int>> rs(k);
        for(auto&[u,v]:rs) cin>>u>>v;
        VI f(1<<k,_inf);f[0]=0;
        vector<pair<int,int>> rts(1<<k);
        VI stx(1<<k);
        cir(s,1,(1<<k)) [&](){
            int lasx=-1,lasy=-1;
            int p=-1;
            cir(i,0,k) if(s&(1<<i)){
                p=i;break;
            }
            assert(p>-1);
            if(__builtin_popcount(s)==1){
                stx[s]=true;rts[s]=rs[p];
                return;
            }
            if(!stx[s^(1<<p)]) return;
            lasx=rts[s^(1<<p)].first,lasy=rts[s^(1<<p)].second;
            auto fx=route(lasx,lasy,rs[p].first,rs[p].second);
            lasx=fx.first,lasy=fx.second;
            if(lasx==lasy) return;
            rts[s]={lasx,lasy};
            stx[s]=true;
        }();
        cir(s,0,(1<<k)) if(stx[s]) cir(i,0,k){
            if(s&(1<<i)) stx[s^(1<<i)]=false;
        }
        VI oks;
        cir(i,0,(1<<k)) if(stx[i]) oks.push_back(i);
        cir(s,0,(1<<k)-1) if(f[s]<_inf){
            for(auto&i:oks) if((s&i)!=i) f[s|i]=min(f[s|i],f[s]+1);
        }
        cout<<f[(1<<k)-1]<<'\n';
    }
};
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int T;cin>>T;
    while(T--) [](){
        int n;cin>>n;
        solver solve(n);
    }();
    return 0;
}
