#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
template<typename T>
struct dsu{
    vector<T> F,siz,Mx,Exmx;
    vector<pair<T,T>> ops;
    dsu(T n):F(n),Mx(n),siz(n,1){
        iota(F.begin(),F.end(),0);
        iota(Mx.begin(),Mx.end(),0);
    }
    T findset(int x){return x==F[x]?x:findset(F[x]);}
    T merge(int x,int y){
        x=findset(x),y=findset(y);
        if(x==y){
            ops.push_back({-1,-1});return Mx[x];
        }
        if(siz[y]<siz[x]) swap(x,y);
        ops.push_back({x,y});siz[y]+=siz[x];
        Exmx.push_back(Mx[y]);Mx[y]=max(Mx[y],Mx[x]);
        return F[x]=y,Mx[y];
    }
    void remoke(){
        if(ops.empty()) return;
        T x=ops.back().first,y=ops.back().second;
        ops.pop_back();
        if(x<0||y<0) return;
        F[x]=x;siz[y]-=siz[x];
        Mx[y]=Exmx.back();Exmx.pop_back();
    }
};
struct edge{int u,v,w;};
const int MOD=1e9+7;
using lint=long long;
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n,m;cin>>n>>m;dsu<int> ds(n+1);
    vector<edge> G(m);
    for(auto&i:G) cin>>i.u>>i.v>>i.w;
    sort(G.begin(),G.end(),[](edge&a,edge&b){return a.w<b.w;});
    dsu<int> tds(n+1);int Cnt=0;
    unordered_map<int,int> Che;
    cir(i,0,m){
        if(tds.findset(G[i].u)!=tds.findset(G[i].v))
            Che[G[i].w]++,tds.merge(G[i].u,G[i].v),++Cnt;
    }
    if(Cnt!=n-1){cout<<0<<'\n';exit(0);}
    lint ans=1;
    cir(i,0,m){
        vector<edge> ve;
        while(i!=m-1&&G[i].w==G[i+1].w) ve.push_back(G[i]),++i;
        ve.push_back(G[i]);
        if(!Che.count(G[i].w)) continue;
        auto chn=Che[G[i].w];
        const int _sz=1<<ve.size();
        lint answ=0;
        cir(k,0,_sz){
            int cnt=0;
            if(__builtin_popcount(k)!=chn) continue;
            cir(j,0,ve.size()) if((1<<j)&(k)){
                if(ds.findset(ve[j].u)==ds.findset(ve[j].v)) break;
                cnt++;ds.merge(ve[j].u,ve[j].v);
            }
            if(cnt==chn) (answ+=1)%=MOD;
            cir(i,0,cnt) ds.remoke();
        }
        if(!answ) cout<<G[i].w<<'\n';
        for(auto&i:ve) if(ds.findset(i.u)!=ds.findset(i.v))
            ds.merge(i.u,i.v);
        (ans*=(answ))%=MOD;
    }
    cout<<ans<<'\n';
    return 0;
}