#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
static constexpr auto _infl=(lint)(1e15l); 
class ssp{
private:
    struct edge{
        int v;lint fl,w;int rev;
        edge(auto _v,auto _fl,auto _w,auto _r):v(_v),fl(_fl),w(_w),rev(_r){}
    };
    vector<vector<edge>> gr;
    vector<int> cur,inst;
    map<pair<int,int>,int> es;
    auto spfa(int s){
        const auto n=(int)(gr.size());
        vector<lint> udis(n,_infl),dis(n,_infl),inq(n);
        queue<int> q;q.emplace(s);
        dis[s]=0;udis[s]=0;
        while(!q.empty()){
            const auto u=q.front();q.pop();
            inq[u]=false;
            for(auto&[v,fl,w,rev]:gr[u]) if(dis[v]>dis[u]+w&&fl){
                dis[v]=dis[u]+w;
                if(!inq[v]) q.emplace(v);
                inq[v]=true;
            }
        }
        return make_pair(udis,dis);
    }
    auto dfs(int u,const int t,lint rst,const vector<lint>&udis,const vector<lint>&dis){
        auto res=0ll;
        if(u==t) return rst;
        inst[u]=true;
        for(auto&x=cur[u];x<(int)(gr[u].size());++x){
            auto&[v,fl,w,rev]=gr[u][x];
            if((!fl)||dis[u]+w!=dis[v]||inst[v]) continue;
            const auto vw=dfs(v,t,min(rst,fl),udis,dis);
            fl-=vw;gr[v][rev].fl+=vw;
            res+=vw;
            if(!(rst-=vw)) return inst[u]=false,res;
        }
        inst[u]=false;
        return res;
    }
    auto update(int s,int t,lint&flw,lint&ans){
        while(true){
            fill(cur.begin(),cur.end(),0);
            fill(inst.begin(),inst.end(),false);
            const auto[udis,dis]=spfa(s);
            const auto cst=dis[t];
            if(cst>_infl-1) return;
            const auto fl=dfs(s,t,_infl,udis,dis);
            flw+=fl;
            ans+=cst*fl;
        }
    }
public:
    auto link(int u,int v,lint fl,lint w){
        gr[u].emplace_back(v,fl,w,gr[v].size());
        gr[v].emplace_back(u,0,-w,gr[u].size()-1);
    }
    auto flow(int s,int t){
        auto fl=0ll,ans=0ll;
        update(s,t,fl,ans);
        return ans;
    }
    ssp(int _n):gr(_n),cur(_n),inst(_n){}
};
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int d,n1,n2,c1,c2,tc;cin>>d>>n1>>n2>>c1>>c2>>tc;
    vector<int> x(d);
    for(auto&i:x) cin>>i;
    const auto s=d*2,t=d*2+1;
    ssp gr(d*2+7);
    gr.link(s,0,_infl,tc);
    cir(i,0,d){
        gr.link(i,t,x[i],0);
        gr.link(s,i+d,x[i],0);
        if(i+1<d) gr.link(i,i+1,_infl,0);
        if(i+n1<d) gr.link(i+d,i+n1,x[i],c1);
        if(i+n2<d) gr.link(i+d,i+n2,x[i],c2);
    }
    cout<<gr.flow(s,t)<<'\n';
    return 0;
}
