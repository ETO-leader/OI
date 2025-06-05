#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
#ifndef ONLINE_JUDGE
ifstream inf("respect.in");
ofstream ouf("respect.out");
class fileio{
public:
    ~fileio(){
        inf.close();ouf.close();
    }
} use_fileio;
#else
auto&inf=cin;
auto&ouf=cout;
#endif
namespace std{
    template<typename _Ty>
    inline void emplace(size_t&seed,const _Ty&val) {
        seed^=std::hash<_Ty>{}(val)+0x9e3779b9+(seed<<6)+(seed>>2);
    }
    template<typename _Ty,size_t lim,size_t index=0>
    struct tupleimpl{
        static void apply(size_t&seed,const _Ty&x){
            emplace(seed,get<index>(x));
            tupleimpl<_Ty,lim,index+1>::apply(seed,x);
        }
    };
    template<typename _Ty,size_t lim>
    struct tupleimpl<_Ty,lim,lim>{
        static void apply(size_t&,const _Ty&){}
    };
    template<typename..._Ty>
    struct hash<tuple<_Ty...>>{
        size_t operator()(const tuple<_Ty...>&x)const{
            auto seed=(size_t)(0);
            tupleimpl<tuple<_Ty...>,tuple_size<tuple<_Ty...>>::value>::apply(seed,x);
            return seed;
        }
    };
}
using lint=long long;
template<const int tid>
class tree{
private:
    vector<vector<pair<int,lint>>> gr;
    vector<lint> depth;
    vector<int> siz;
    unordered_map<tuple<lint,int,int>,lint,hash<tuple<lint,int,int>>>*cnt;
    vector<tuple<lint,int,int>>*id;
    int dfs(int u,lint dep,int f=-1,lint fw=-1){
        depth[u]=dep;
        if(f>-1) gr[u].erase(find(gr[u].begin(),gr[u].end(),pair<int,lint>(f,fw)));
        siz[u]=1;
        for(auto&[v,w]:gr[u]) siz[u]+=dfs(v,dep+w,u,w);
        sort(gr[u].begin(),gr[u].end(),[&](pair<int,lint> u,pair<int,lint> v){
            return siz[u.first]>siz[v.first];
        });
        return siz[u];
    }
    void changenode(int u,int&c,int w){
        --(*cnt)[(*id)[u]];
        c-=(*cnt)[(*id)[u]];
        get<tid>((*id)[u])=w;
        c+=(*cnt)[(*id)[u]];
        ++(*cnt)[(*id)[u]];
    }
    void change(int u,int&c,int w){
        changenode(u,c,w);
        for(auto&[v,x]:gr[u]) change(v,c,w);
    }
public:
    void link(int u,int v,lint w){
        gr[u].emplace_back(v,w);
        gr[v].emplace_back(u,w);
    }
    void init(){dfs(0,0);}
    const vector<lint>& dep(){return depth;}
    void args(unordered_map<tuple<lint,int,int>,lint,hash<tuple<lint,int,int>>>*_cnt,vector<tuple<lint,int,int>>*_id){
        cnt=_cnt;id=_id;
    }
    lint access(int u){
        if(gr[u].empty()) return 0ll;
        int c=0;
        changenode(u,c,get<tid>((*id)[gr[u][0].first]));
        for(auto&[v,w]:gr[u]) if(v!=gr[u][0].first) change(v,c,get<tid>((*id)[gr[u][0].first]));
        return c*depth[u];
    }
    tree(int _n):gr(_n),depth(_n),siz(_n){}
};
lint checkmin(const int n,vector<lint> dep_u,vector<lint> dep_v,vector<lint> dep_w,tree<0>*gr_u,tree<1>*gr_v,tree<2>*gr_w){
    vector<tuple<lint,int,int>> id(n);
    cir(i,0,n){
        if(gr_u) get<0>(id[i])=i;
        if(gr_v) get<1>(id[i])=i;
        if(gr_w) get<2>(id[i])=i;
    }
    unordered_map<tuple<lint,int,int>,lint,hash<tuple<lint,int,int>>> cnt;
    for(auto&x:id) ++cnt[x];
    if(gr_u) gr_u->args(&cnt,&id);
    if(gr_v) gr_v->args(&cnt,&id);
    if(gr_w) gr_w->args(&cnt,&id);
    vector<tuple<lint,int,int>> tps;
    for(int c=-1;(size_t)(++c)<dep_u.size();) tps.emplace_back(dep_u[c],c,0);
    for(int c=-1;(size_t)(++c)<dep_v.size();) tps.emplace_back(dep_v[c],c,1);
    for(int c=-1;(size_t)(++c)<dep_w.size();) tps.emplace_back(dep_w[c],c,2);
    sort(tps.begin(),tps.end(),greater<tuple<lint,int,int>>());
    lint ans=0;
    for(auto&[dep,u,tid]:tps){
        switch(tid){
            case 0: ans+=gr_u->access(u); break;
            case 1: ans+=gr_v->access(u); break;
            case 2: ans+=gr_w->access(u); break;
        }
    }
    return ans;
}
int main(){
    ios::sync_with_stdio(false),inf.tie(nullptr);
    int n;inf>>n;
    tree<0> gr_u(n);
    tree<1> gr_v(n);
    tree<2> gr_w(n);
    cir(i,0,n-1){
        int u,v;lint w;inf>>u>>v>>w;--u;--v;
        gr_u.link(u,v,w);
    }
    cir(i,0,n-1){
        int u,v;lint w;inf>>u>>v>>w;--u;--v;
        gr_v.link(u,v,w);
    }
    cir(i,0,n-1){
        int u,v;lint w;inf>>u>>v>>w;--u;--v;
        gr_w.link(u,v,w);
    }
    gr_u.init();
    gr_v.init();
    gr_w.init();
    const vector<lint>& dep_u=gr_u.dep();
    const vector<lint>& dep_v=gr_v.dep();
    const vector<lint>& dep_w=gr_w.dep();
    const lint ans=
        checkmin(n,dep_u,{},{},&gr_u,nullptr,nullptr)+
        checkmin(n,{},dep_v,{},nullptr,&gr_v,nullptr)+
        checkmin(n,{},{},dep_w,nullptr,nullptr,&gr_w)-
        checkmin(n,dep_u,dep_v,{},&gr_u,&gr_v,nullptr)-
        checkmin(n,dep_u,{},dep_w,&gr_u,nullptr,&gr_w)-
        checkmin(n,{},dep_v,dep_w,nullptr,&gr_v,&gr_w)+
        checkmin(n,dep_u,dep_v,dep_w,&gr_u,&gr_v,&gr_w)
    ;
    ouf<<ans<<'\n';
    return 0;
}

