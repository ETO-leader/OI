#include<bits/extc++.h>
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
    template<>
    struct hash<tuple<unsigned long long,int,int>>{
        size_t operator()(const tuple<unsigned long long,int,int>&x) const{
            return (get<0>(x)<<34)^(static_cast<unsigned long long>(get<1>(x))<<17)^get<2>(x);
        }
    };
}
using lint=unsigned long long;
template<const int tid>
class tree{
private:
    vector<vector<pair<int,lint>>> gr;
    vector<lint> depth;
    vector<int> siz,dfn,rdfn,rid,sn;
    unordered_map<lint,lint>*cnt;
    vector<tuple<lint,int,int>>*id;
    int dfs(int u,lint dep,int&uc,int f=-1,lint fw=-1){
        depth[u]=dep;
        rid[dfn[u]=++uc]=u;
        if(f>-1) gr[u].erase(find(gr[u].begin(),gr[u].end(),pair<int,lint>(f,fw)));
        siz[u]=1;
        for(auto&[v,w]:gr[u]) siz[u]+=dfs(v,dep+w,uc,u,w);
        // sort(gr[u].begin(),gr[u].end(),[&](pair<int,lint> u,pair<int,lint> v){
        //     return siz[u.first]>siz[v.first];
        // });
        sn[u]=-1;
        for(auto&[v,w]:gr[u]) if(sn[u]<0||siz[sn[u]]<siz[v]) sn[u]=v;
        rdfn[u]=uc;
        return siz[u];
    }
    void changenode(int u,lint&c,int w){
        const auto hlas=hash<tuple<lint,int,int>>{}((*id)[u]);
        c-=(--(*cnt)[hlas]);
        get<tid>((*id)[u])=w;
        const auto hcur=hash<tuple<lint,int,int>>{}((*id)[u]);
        c+=(++(*cnt)[hcur])-1;
    }
    void change(int x,lint&c,int w){
        cir(u,dfn[x],rdfn[x]+1) changenode(rid[u],c,w);
    }
public:
    void link(int u,int v,lint w){
        gr[u].emplace_back(v,w);
        gr[v].emplace_back(u,w);
    }
    void init(){auto c=-1;dfs(0,0,c);}
    const vector<lint> dep(){return depth;}
    void args(unordered_map<lint,lint>*_cnt,vector<tuple<lint,int,int>>*_id){
        cnt=_cnt;id=_id;
    }
    lint access(int u){
        if(gr[u].empty()) return 0ull;
        auto c=0ull;
        changenode(u,c,get<tid>((*id)[sn[u]]));
        for(auto&[v,w]:gr[u]) if(v!=sn[u]) change(v,c,get<tid>((*id)[sn[u]]));
        return c*depth[u];
    }
    tree(int _n):gr(_n),depth(_n),siz(_n),dfn(_n),rdfn(_n),rid(_n),sn(_n){}
};
class cnt_tree{
private:
    vector<vector<pair<int,lint>>> gr;
    static constexpr int ups=21;
    int dfs(int u,lint&ans,lint depth,int f=-1){
        int ucnt=1;
        for(auto&p:gr[u]){
            int v=p.first;lint w=p.second;
            if(v!=f){
                const int vcnt=dfs(v,ans,depth+w,u);
                ans+=(lint)(ucnt)*vcnt*depth;
                ucnt+=vcnt;
            }
        }
        return ucnt;
    }
public:
    void link(int u,int v,lint w){
        gr[u].emplace_back(v,w);
        gr[v].emplace_back(u,w);
    }
    lint check(){
        lint ans=0ull;
        dfs(0,ans,0);
        return ans;
    }
    cnt_tree(int _n):gr(_n){}
};
lint checkmin(const int n,vector<lint> dep_u,vector<lint> dep_v,vector<lint> dep_w,tree<0>*gr_u,tree<1>*gr_v,tree<2>*gr_w){
    vector<tuple<lint,int,int>> id(n);
    cir(i,0,n){
        if(gr_u) get<0>(id[i])=i;
        if(gr_v) get<1>(id[i])=i;
        if(gr_w) get<2>(id[i])=i;
    }
    unordered_map<lint,lint> cnt;
    for(auto&x:id) ++cnt[hash<tuple<lint,int,int>>{}(x)];
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
            case 0:
                ans+=gr_u->access(u);
                break;
            case 1:
                ans+=gr_v->access(u);
                break;
            case 2:
                ans+=gr_w->access(u);
                break;
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
    cnt_tree cgr_u(n),cgr_v(n),cgr_w(n);
    cir(i,0,n-1){
        int u,v;lint w;inf>>u>>v>>w;--u;--v;
        gr_u.link(u,v,w);
        cgr_u.link(u,v,w);
    }
    cir(i,0,n-1){
        int u,v;lint w;inf>>u>>v>>w;--u;--v;
        gr_v.link(u,v,w);
        cgr_v.link(u,v,w);
    }
    cir(i,0,n-1){
        int u,v;lint w;inf>>u>>v>>w;--u;--v;
        gr_w.link(u,v,w);
        cgr_w.link(u,v,w);
    }
    gr_u.init();
    gr_v.init();
    gr_w.init();
    const auto dep_u=gr_u.dep();
    const auto dep_v=gr_v.dep();
    const auto dep_w=gr_w.dep();
    const auto ans=
        cgr_u.check()+
        cgr_v.check()+
        cgr_w.check()-
        checkmin(n,dep_u,dep_v,{},&gr_u,&gr_v,nullptr)-
        checkmin(n,dep_u,{},dep_w,&gr_u,nullptr,&gr_w)-
        checkmin(n,{},dep_v,dep_w,nullptr,&gr_v,&gr_w)+
        checkmin(n,dep_u,dep_v,dep_w,&gr_u,&gr_v,&gr_w)
    ;
    ouf<<ans<<'\n';
    return 0;
}
