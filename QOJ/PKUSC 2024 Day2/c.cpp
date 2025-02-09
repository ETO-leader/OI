#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
auto generate_edges(int n,int m,unsigned seed){
    mt19937 gen(seed);
    vector<tuple<int,int,lint>> edges(m);
    auto max=-1u/n*n;
    auto sample=[&]{
        auto x=0u;
        do{x=gen();}while(x>max-1);
        return x%n+1;
    };
    for(auto&[u,v,w]:edges){
        u=sample();
        v=sample();
        w=gen();
    }
    return edges;
}
class graph{
private:
    class edge{
    private:
        lint vdist;
        int index;
        vector<pair<int,lint>>*nxt;
    public:
        auto node() const{return (*nxt)[index].first;}
        auto dist() const{return vdist;}
        auto next() const{
            return (index+1<(int)(nxt->size()))?
                optional(edge(vdist-(*nxt)[index].second,nxt,index+1)):
                nullopt;
        }
        edge(auto _w,auto*_nxt,int ind=0):vdist(_w+(*_nxt)[ind].second),nxt(_nxt),index(ind){}
    };
    class cmp_edge{
    public:
        auto operator()(const auto&a,const auto&b) const{
            return a.dist()>b.dist();
        }
    };
    vector<lint> distl,distr;
    vector<vector<pair<int,lint>>> gr,rgr;
    vector<int> visl,visr;
public:
    auto link(int u,int v,lint w){
        gr[u].emplace_back(v,w);
        rgr[v].emplace_back(u,w);
    }
    auto init(){
        for(auto&x:gr){
            ranges::sort(x,[](auto&a,auto&b){return a.second<b.second;});
        }
        for(auto&x:rgr){
            ranges::sort(x,[](auto&a,auto&b){return a.second<b.second;});
        }
    }
    auto dist(int ux,int vx){
        if(ux==vx) return 0ll;
        vector sl{pair(ux,0ll)},sr{pair(vx,0ll)};
        priority_queue<edge,vector<edge>,cmp_edge> ql,qr;
        ql.emplace(0,&sl);
        qr.emplace(0,&sr);
        vector<int> ul,ur;
        const auto u=[&]{
            auto cur=false;
            while((!ql.empty())&&(!qr.empty())){
                if(cur){
                    const auto e=ql.top();ql.pop();
                    const auto u=e.node();
                    if(auto v=e.next()) ql.emplace(v.value());
                    if(visl[u]) continue;
                    cur^=true;
                    visl[u]=true;distl[u]=e.dist();
                    ul.emplace_back(u);
                    if(visr[u]) return u;
                    if(!gr[u].empty()) ql.emplace(edge(e.dist(),&gr[u]));
                }else{
                    const auto e=qr.top();qr.pop();
                    const auto u=e.node();
                    if(auto v=e.next()) qr.emplace(v.value());
                    if(visr[u]) continue;
                    cur^=true;
                    visr[u]=true;distr[u]=e.dist();
                    ur.emplace_back(u);
                    if(visl[u]) return u;
                    if(!rgr[u].empty()) qr.emplace(edge(e.dist(),&rgr[u]));
                }
            }
            return -1;
        }();
        const auto res=[&]{
            if(u<0) return -1ll;
            auto ans=distl[u]+distr[u];
            for(auto&u:ul){
                for(auto&[v,w]:gr[u]) if(visr[v]) ans=min(ans,distl[u]+distr[v]+w);
            }
            for(auto&u:ur){
                for(auto&[v,w]:rgr[u]) if(visl[v]) ans=min(ans,distl[v]+distr[u]+w);
            }
            return ans;
        }();
        for(auto&u:ul) visl[u]=false;
        for(auto&u:ur) visr[u]=false;
        return res;
    }
    graph(int _n):gr(_n),rgr(_n),distl(_n),distr(_n),visl(_n),visr(_n){}
};
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int n,m,q;uint seed;cin>>n>>m>>q>>seed;
    graph gr(n);
    const auto es=generate_edges(n,m,seed);
    for(auto&[u,v,w]:es) gr.link(u-1,v-1,w);
    gr.init();
    cir(i,0,q){
        int u,v;cin>>u>>v;--u;--v;
        println("{}",gr.dist(u,v));
    }
    return 0;
}
