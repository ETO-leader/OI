#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
static constexpr auto _infl=(lint)(1e15l); 
class ssp{
private:
    struct edge{
        int v;lint fl,w;int rev;
    };
    vector<vector<edge>> gr;
    vector<int> fr,eid;
    map<pair<int,int>,int> es;
    auto spfa(int s,int t){
        const auto n=(int)(gr.size());
        vector<lint> dis(n,_infl),rest(n),inq(n);
        queue<int> q;q.emplace(s);
        rest[s]=_infl;dis[s]=0;
        while(!q.empty()){
            const auto u=q.front();q.pop();
            inq[u]=false;
            for(auto cnt=-1;auto&[v,fl,w,rev]:gr[u]) if(++cnt;dis[v]>dis[u]+w&&fl){
                dis[v]=dis[u]+w;rest[v]=min(rest[u],fl);
                fr[v]=u;eid[v]=cnt;
                if(!inq[v]) q.emplace(v);
                inq[v]=true;
            }
        }
        return rest[t];
    }
    auto update(int s,int t,lint&cur){
        const auto fl=spfa(s,t);
        if(!fl) return false;
        for(;t!=s;t=fr[t]){
            const auto u=fr[t];
            gr[u][eid[t]].fl-=fl;
            gr[t][gr[u][eid[t]].rev].fl+=fl;
            cur+=gr[u][eid[t]].w*fl;
        }
        return true;
    }
public:
    auto link(int u,int v,lint fl,int w){
        gr[u].emplace_back(v,fl,w,gr[v].size());
        gr[v].emplace_back(u,0,-w,gr[u].size()-1);
    }
    auto flow(int s,int t){
        auto ans=0ll;
        while(update(s,t,ans));
        return ans;
    }
    ssp(int _n):gr(_n),fr(_n),eid(_n){}
};
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    
    return 0;
}
