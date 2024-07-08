#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
class ek_algorithm{
private:
    static constexpr int _inf=1e9+7;
    struct edge{
        int v,fl,rev;int w;
    };
    vector<vector<edge>> gr;
    vector<int> dis;
    vector<int> fx,esid;
    auto spfa(int ux){
        queue<int> q;q.push(ux);
        fill(dis.begin(),dis.end(),_inf);
        fill(fx.begin(),fx.end(),-1);
        fill(esid.begin(),esid.end(),-1);
        vector<bool> inq(gr.size());
        dis[ux]=0;
        while(!q.empty()){
            auto u=q.front();q.pop();
            inq[u]=false;int c=-1;
            for(auto&[v,fl,rev,w]:gr[u]){
                ++c;
                if((!fl)||dis[u]+w>dis[v]-1) continue;
                dis[v]=dis[u]+w;fx[v]=u;esid[v]=c;
                if(!inq[v]) q.push(v),inq[v]=true;
            }
        }
    }
    auto flow(int s,int t,int&ans){
        spfa(s);
        if(dis[t]>_inf-1) throw exception();
        auto u=t;int fl=_inf;
        while(u!=s){
            fl=min(fl,gr[fx[u]][esid[u]].fl);
            u=fx[u];
        }
        ans+=fl*dis[t];
        u=t;
        while(u!=s){
            auto&ex=gr[fx[u]][esid[u]];
            auto&re=gr[u][gr[fx[u]][esid[u]].rev];
            ex.fl-=fl;re.fl+=fl;u=fx[u];
        }
        return fl;
    }
public:
    auto flow(int s,int t){
        int cost=0,flw=0;
        while(true) try{
            flw+=flow(s,t,cost);
        }catch(exception&){
            break;
        }
        return pair(cost,flw);
    }
    auto insert(int u,int v,int fl,int w){
        gr[u].push_back({v,fl,(int)(gr[v].size()),w});
        gr[v].push_back({u,0,(int)(gr[u].size()-1),-w});
    }
    ek_algorithm(int _n):gr(_n+1),
        dis(_n+1),fx(_n+1),esid(_n+1){}
};
class nodegen{
private:
    int cnt;
public:
    auto getnode(){return cnt++;}
    nodegen():cnt(0){}
};
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n,m;cin>>n>>m;
    vector<vector<int>> mp(n,vector<int>(m));
    vector<vector<int>> nid(n,vector<int>(m));
    int srtcnta=0;
    for(auto&i:mp) for(auto&j:i) cin>>j,srtcnta+=j;
    nodegen ngen;ek_algorithm gr(n*m+n+m+7);
    const auto s=ngen.getnode(),t=ngen.getnode();
    for(auto&i:nid) for(auto&j:i) j=ngen.getnode();
    int asum=0,bsum=0;
    cir(i,0,n){
        int x;cin>>x;asum+=x;
        auto ndi=ngen.getnode();
        gr.insert(s,ndi,x,0);
        cir(j,0,m){
            gr.insert(ndi,nid[i][j],1,(mp[i][j]?-1:1));
        }
    }
    cir(j,0,m){
        int x;cin>>x;bsum+=x;
        auto ndi=ngen.getnode();
        gr.insert(ndi,t,x,0);
        cir(i,0,n){
            gr.insert(nid[i][j],ndi,1,0);
        }
    }
    auto[cost,flow]=gr.flow(s,t);
    cout<<((flow==asum&&flow==bsum)?cost+srtcnta:-1)<<'\n';
    return 0;
}
