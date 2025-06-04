#include<bits/stdc++.h>
#include<tr1/functional>
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
using lint=long long;
template<const int tid>
class tree{
private:
    vector<vector<pair<int,lint>>> gr;
    vector<lint> depth;
    vector<int> siz;
    unordered_map<tuple<int,int,int>,lint,tr1::hash<tuple<int,int,int>>>*cnt;
    vector<tuple<int,int,int>>*id;
    auto dfs(int u,lint dep,int f=-1,lint fw=-1)->int{
        depth[u]=dep;
        if(f>-1) gr[u].erase(ranges::find(gr[u],pair(f,fw)));
        siz[u]=1;
        for(auto&[v,w]:gr[u]) siz[u]+=dfs(v,dep+w,u,w);        
        ranges::sort(gr[u],[&](int u,int v){
            return siz[u]>siz[v];
        });
        return siz[u];
    }
    auto changenode(int u,int&c,int w){
        c-=(*cnt)[(*id)[u]];
        get<tid>((*id)[u])=w;
        c+=(*cnt)[(*id)[u]];
        ++(*cnt)[(*id)[u]];
    }
    auto change(int u,int&c,int w)->void{
        changenode(u,c,w);
        for(auto&i:gr[u]) dfs(i,w);
    }
public:
    auto link(int u,int v,lint w){
        gr[u].emplace_back(v,w);
        gr[v].emplace_back(u,w);
    }
    auto init(){dfs(0,0);}
    auto dep(){return depth;}
    auto args(auto*_cnt,auto*_id){
        cnt=_cnt;id=_id;
    }
    /*
        @returns delta
    */
    auto access(int u){
        if(gr[u].empty()) return 0ll;
        auto c=0;
        changenode(u,c,get<tid>((*id)[gr[u][0].first]));
        for(auto&[v,w]:gr[u]) if(v!=gr[u][0].first) change(v,c,get<tid>((*id)[gr[u][0].first]));
        return c*depth[u]; 
    }
    tree(int _n):gr(_n),depth(_n),siz(_n){}
};
/*
    gr_x is inited
*/
auto checkmin(vector<int> dep_u,vector<int> dep_v,vector<int> dep_w,tree<0>*gr_u,tree<1>*gr_v,tree<2>*gr_w){
    vector<tuple<int,int,int>> id;
    unordered_map<tuple<int,int,int>,lint,tr1::hash<tuple<int,int,int>>> cnt;
    if(gr_u) gr_u->args(&cnt,&id);
    if(gr_v) gr_v->args(&cnt,&id);
    if(gr_w) gr_w->args(&cnt,&id);
    vector<tuple<int,int,int>> tps;
    for(auto c=-1;auto&x:dep_u) tps.emplace_back(x,++c,0);
    for(auto c=-1;auto&x:dep_v) tps.emplace_back(x,++c,1);
    for(auto c=-1;auto&x:dep_w) tps.emplace_back(x,++c,2);
    ranges::sort(tps,greater<tuple<int,int,int>>());
    auto ans=0ll;
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
    // tree<0> gr_u(n);
    // tree<1> gr_v(n);
    // tree<2> gr_w(n);
    // cir(i,0,n-1){
    //     int u,v;lint w;inf>>u>>v>>w;--u;--v;
    //     gr_u.link(u,v,w);
    // }
    // cir(i,0,n-1){
    //     int u,v;lint w;inf>>u>>v>>w;--u;--v;
    //     gr_v.link(u,v,w);
    // }
    // cir(i,0,n-1){
    //     int u,v;lint w;inf>>u>>v>>w;--u;--v;
    //     gr_w.link(u,v,w);
    // }
    // gr_u.init();
    // gr_v.init();
    // gr_w.init();
    // const auto dep_u=gr_u.dep();
    // const auto dep_v=gr_v.dep();
    // const auto dep_w=gr_w.dep();
    // const auto ans=
    //     checkmin(dep_u,{},{},&gr_u,nullptr,nullptr)+
    //     checkmin({},dep_v,{},nullptr,&gr_v,nullptr)+
    //     checkmin({},{},dep_w,nullptr,nullptr,&gr_w)-
    //     checkmin(dep_u,dep_v,{},&gr_u,&gr_v,nullptr)-
    //     checkmin(dep_u,{},dep_w,&gr_u,nullptr,&gr_w)-
    //     checkmin({},dep_v,dep_w,nullptr,&gr_v,&gr_w)+
    //     checkmin(dep_u,dep_v,dep_w,&gr_u,&gr_v,&gr_w);
    // ouf<<ans<<'\n';
    return 0;
}
