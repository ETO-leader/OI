#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
static constexpr int _inf=1e9+7;
class ek_algorithm{
private:
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
    int n,m,k,c,d;cin>>n>>m>>k>>c>>d;
    vector<int> psx(k);
    for(auto&i:psx) cin>>i;
    vector<vector<int>> grx(n+1);
    cir(i,0,m){
        int u,v;cin>>u>>v;
        grx[u].push_back(v);grx[v].push_back(u);
    }
    ek_algorithm gr(n*200+7);
    nodegen ngen;
    const auto s=ngen.getnode(),t=ngen.getnode();
    vector<int> lnds(n),nds(n);
    for(auto&i:nds) i=ngen.getnode();
    for(auto&i:psx) gr.insert(s,nds[i-1],1,0);
    cir(cx,0,199){
        swap(nds,lnds);
        for(auto&i:nds) i=ngen.getnode();
        cir(i,1,n+1){
            gr.insert(lnds[i-1],nds[i-1],_inf,c*(i!=1));
            for(auto&x:grx[i]){
                cir(p,1,k+1) gr.insert(lnds[i-1],nds[x-1],1,d*p*p-d*(p-1)*(p-1)+c);
            }
        }
    }
    gr.insert(nds[0],t,_inf,0);
    cout<<gr.flow(s,t).first<<'\n';
    return 0;
}
