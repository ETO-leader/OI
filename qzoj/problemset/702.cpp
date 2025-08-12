#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
static constexpr auto _inf=(int)(1e9+7);
class dinic{
private:
    struct edge{
        int v,rev,w,fv;
        edge(auto _v,auto _rev,auto _w,auto _f):v(_v),rev(_rev),w(_w),fv(_f){}
    };
    vector<vector<edge>> gr;
    vector<int> cur,dist,gap;
    bool unusual;
    auto dfs(int u,const int vx,int rst){
        if(u==vx) return rst;
        auto res=0;
        for(auto&i=cur[u];i<(int)(gr[u].size());++i){
            auto&[v,rev,fl,fv]=gr[u][i];
            if(dist[u]!=dist[v]+1||(!fl)) continue;
            const auto vw=dfs(v,vx,min(rst,fl));
            fl-=vw;gr[v][rev].w+=vw;res+=vw;
            if(!(rst-=vw)) return res;
        }
        if(!(--gap[dist[u]])) unusual=true;
        ++gap[++dist[u]];
        cur[u]=0;
        return res;
    }
public:
    auto link(int u,int v,int w){
        gr[u].emplace_back(v,gr[v].size(),w,w);
        gr[v].emplace_back(u,gr[u].size()-1,0,0);
    }
    auto flow(int s,int t){
        auto res=0ll;
        unusual=false;
        fill(cur.begin(),cur.end(),0);
        fill(dist.begin(),dist.end(),0);
        fill(gap.begin(),gap.end(),0);
        while(!unusual) res+=dfs(s,t,_inf);
        return res;
    }
    auto revoke(int u,int v){
        gr[u].pop_back();gr[v].pop_back();
    }
    auto val(const int s){return gr[s].back().w;}
    auto info(){
        map<pair<int,int>,int64_t> es;
        cir(u,0,(int)(gr.size())) for(auto&[v,rev,fl,fv]:gr[u]) if(fv>fl){
            es[{u,v}]+=fv-fl;
        }
        return es;
    }
    dinic(int _n):gr(_n),cur(_n),dist(_n),gap(_n+7),unusual(false){}
};
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int c,d,n;cin>>c>>d>>n;
    const auto cat=[&](int p){
        return p;
    };
    const auto dog=[&](int p){
        return c+p;
    };
    const auto in=[&](int p){
        return c+d+p;
    };
    const auto out=[&](int p){
        return c+d+n+p;
    };
    const auto s=c+d+n*2,t=c+d+n*2+1;
    dinic gr(c+d+n*2+7);
    cir(i,0,n) gr.link(in(i),out(i),1);
    cir(i,0,n){
        string st,lv;cin>>st>>lv;
        if(st[0]=='C'){
            gr.link(s,in(i),_inf);
            gr.link(out(i),cat(atoi(st.substr(1).data())-1),_inf);
            gr.link(out(i),dog(atoi(lv.substr(1).data())-1),_inf);
        }else{
            gr.link(out(i),t,_inf);
            gr.link(dog(atoi(st.substr(1).data())-1),in(i),_inf);
            gr.link(cat(atoi(lv.substr(1).data())-1),in(i),_inf);
        }
    }
    cout<<n-gr.flow(s,t)<<'\n';
    return 0;
}
