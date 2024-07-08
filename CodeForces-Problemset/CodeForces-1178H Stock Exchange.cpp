#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
const int _dinf=1e9+7;
template<typename T,T _inf>
class graph{
private:
    vector<T> D;
    vector<bool> inq;
    struct edge{int v,rid;T f,w;};
    vector<vector<edge>> G;
    vector<int> fx,fid;
    bool spfa(int s,int t){
        queue<int> q;q.push(s);
        fill(D.begin(),D.end(),_inf);
        D[s]=0;fx[s]=-1;
        vector<bool> vis(G.size());
        while(!q.empty()){
            auto u=q.front();q.pop();
            inq[u]=false;vis[u]=true;
            for(auto&[v,rid,f,w]:G[u]) if(f>0){
                if(D[u]+w>=D[v]) continue;
                fx[v]=u;D[v]=D[u]+w;
                fid[v]=G[v][rid].rid;
                if(!inq[v]) q.push(v);
            }
        }
        return vis[t];
    }
    T getflow(int s,int t){
        int u=t;T flow=_inf;
        while(u!=s){
            flow=min(flow,G[fx[u]][fid[u]].f);
            u=fx[u];
        }
        return flow;
    }
    auto max_flow(int s,int t){
        T resw=0,flw=0;
        while(spfa(s,t)){
            int u=t;T flow=getflow(s,t);
            while(u!=s){
                G[fx[u]][fid[u]].f-=flow;
                G[u][G[fx[u]][fid[u]].rid].f+=flow;
                u=fx[u];
            }
            resw+=D[t]*flow;
        }
        return make_pair(resw,flw);
    }
public:
    void insert(int u,int v,T fw=_inf,T w=0){
        G[u].push_back({v,(int)(G[v].size()),fw,w});
        G[v].push_back({u,(int)(G[u].size()-1),0,-w});
    }
    T max_flow_size(int s,int t){
        return max_flow(s,t).first;
    }
    graph(int _n):
        fid(_n),G(_n),fx(_n),inq(_n),D(_n){}
};
const lint _inf=1e9+7;
struct stock{
    lint a,b;bool str;int id;
    lint price(lint d) const{return a*d+b;}
};
vector<stock> st;
void build_graph(int n,lint ans,graph<lint,_inf>&G){
    const int s=0,t=n*7+1;
    auto getid=[&](int x,int row){
        ++x;
        if(!row) return x;
        if(row==3) return n*5+x;
        return n*2*(row-1)+n+x;
    };
    cir(i,0,n) G.insert(s,getid(i,0),1);
    int lp=0;
    for(auto&i:st){
        if(lp) G.insert(getid(i.id,1),lp);
        if(i.str){
            G.insert(getid(i.id,0),getid(i.id,2),_inf,1);
            G.insert(getid(i.id,0),getid(i.id,1),_inf,1);
        }
        lp=getid(i.id,1);
    }
    cir(i,0,n*2){
        G.insert(getid(i,1),getid(i,2),_inf,1);
        if(!st[i].str)
            G.insert(getid(st[i].id,1),getid(st[i].id,3));
    }
    sort(st.begin(),st.end(),[&](stock&a,stock&b){
        return a.price(ans)==b.price(ans)?
        a.str:a.price(ans)>b.price(ans);});
    lp=0;
    for(auto&i:st){
        if(lp)
            G.insert(lp,getid(i.id,2));
        if(!i.str)
            G.insert(getid(i.id,2),getid(i.id,3));
        lp=getid(i.id,2);
    }
    cir(i,n,n*2) G.insert(getid(i,3),t,1);
}
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n;cin>>n;st.resize(n*2);
    cir(i,0,n*2){
        cin>>st[i].a>>st[i].b;
        st[i].str=(i<n);st[i].id=i;
    }
    sort(st.begin(),st.end(),[](stock&a,stock&b){
        return a.price(0)==b.price(0)?
        (!a.str):a.price(0)<b.price(0);});
    lint l=0,r=_dinf,ans=-1;
    while(r>=l){
        const int mid=(l+r)/2;
        [&](){
            lint mx=0;auto stx=st;
            queue<lint> pr;
            for(auto&i:stx){
                mx=max(mx,i.price(mid));
                if(i.str) pr.push(mx);
            }
            sort(stx.begin(),stx.end(),[&](stock&a,stock&b){
                return a.price(mid)==b.price(mid)?
                a.str:a.price(mid)<b.price(mid);});
            for(auto&i:stx){
                if(!i.str){
                    if(pr.front()<i.price(mid))
                        return false;
                    pr.pop();
                }
            }
            return true;
        }()?(r=mid-1),(ans=mid):(l=mid+1);
    }
    const int s=0,t=n*7+1;
    if(ans<0) exit((cout<<"-1\n",0));
    graph<lint,_inf> G(n*7+2);
    build_graph(n,ans,G);
    cout<<ans<<' '<<G.max_flow_size(s,t)<<'\n';
    return 0;
}
