#pragma GCC optimize("Ofast")
#pragma GCC optimize("inline")
#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=unsigned long long;
static constexpr auto _inf=(int)(1e9+7);
class tree{
private:
    vector<vector<pair<int,int>>> gr;
    vector<int> mind,imp,chs,vaild,fr;
    vector<pair<int,int>> q;
    auto update(int ux){
        auto head=0u,tail=1u;
        mind[ux]=0;q[0]={ux,0};
        while(head<tail){
            const auto[u,wx]=q[head];++head;
            for(auto&[v,w]:gr[u]) if(mind[v]>max(wx,w)){
                mind[v]=max(wx,w);q[tail]={v,mind[v]};++tail;
            }
        }
    }
    auto bfs(int ux){
        auto head=0u,tail=1u;q[0]={ux,0};
        auto res=0ull;
        fr[ux]=-1;
        while(head<tail){
            const auto[u,wx]=q[head];++head;
            if(imp[u]) res+=(mind[u]-wx);
            for(auto&[v,w]:gr[u]) if(v!=fr[u]&&mind[v]>max(wx,w)){
                q[tail]={v,max(wx,w)};++tail;fr[v]=u;
            }
        }
        return res;
    }
public:
    auto link(int u,int v,int w){
        gr[u].emplace_back(v,w);
        gr[v].emplace_back(u,w);
    }
    auto init(){
        cir(u,0,(int)(gr.size())){
            auto ok=imp[u];
            for(auto&i:gr[u]) if(imp[i.first]) ok=true;
            vaild[u]=ok;
        }
    }
    auto cost(int u){
        if(!vaild[u]) return 0ull;
        return bfs(u);
    }
    auto curcost(){
        auto res=0ull;
        cir(i,0,(int)(gr.size())){
            res+=imp[i]*mind[i];
        }
        return res;
    }
    auto importn(int u){imp[u]=true;}
    auto insert(int u){chs[u]=true;update(u);}
    tree(int _n):gr(_n),mind(_n,_inf),imp(_n),chs(_n),vaild(_n),q(_n+7),fr(_n){}
};
class dsu{
private:
    vector<int> f;
public:
    auto findset(int u)->int{
        return f[u]==u?u:(f[u]=findset(f[u]));
    }
    auto merge(int u,int v){
        f[findset(v)]=findset(u);
    }
    dsu(int _n):f(_n){ranges::iota(f,0);}
};
auto mst(vector<tuple<int,int,int>> es,const int n){
    ranges::sort(es,[&](auto&a,auto&b){
        return get<2>(a)<get<2>(b);
    });
    vector<tuple<int,int,int>> res;
    dsu ds(n);
    for(auto&[u,v,w]:es){
        if(ds.findset(u)==ds.findset(v)) continue;
        ds.merge(u,v);
        res.emplace_back(u,v,w);
    }
    return res;
}
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int T;cin>>T;
    while(T--) [&](){
        int n,m,c;cin>>n>>m>>c;
        vector<int> imp(c);
        for(auto&i:imp) cin>>i,--i;
        vector<tuple<int,int,int>> es(m);
        for(auto&[u,v,w]:es) cin>>u>>v>>w,--u,--v;
        const auto tre=mst(es,n);
        tree tr(n);
        for(auto&[u,v,w]:tre) tr.link(u,v,w);
        for(auto&i:imp) tr.importn(i);
        tr.init();
        vector<int> chs(n);
        auto cnt=0;
        auto update=[&](){
            if(cnt==c) return tr.curcost();
            ++cnt;
            auto mx=pair(0ull,-1);
            cir(i,0,n) if(!chs[i]) mx=max(mx,pair(tr.cost(i),i));
            if(mx.second<0) return tr.curcost();
            tr.insert(mx.second);
            chs[mx.second]=true;
            return tr.curcost();
        };
        cir(i,0,n) print("{} ",update());
        println("");
    }();
    return 0;
}
