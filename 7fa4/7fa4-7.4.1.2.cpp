#include<bits/stdc++.h>
#define int int64_t
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
static constexpr lint _inf=1e15+7;
class dinic{
private:
    struct edge{
        int v;lint w;int rev;
    };
    vector<vector<edge>> gr;
    vector<int> cur,dist,gap;
    bool unusual;
    auto dfs(int u,lint cst,const int vx){
        if(u==vx) return cst;
        auto res=(lint)(0);
        for(auto&i=cur[u];i<(int)(gr[u].size());++i){
            auto&[v,w,rev]=gr[u][i];
            if(w&&dist[u]-1==dist[v]){
                auto wx=dfs(v,min(cst,w),vx);
                w-=wx;res+=wx;
                gr[v][rev].w+=wx;
                if(!(cst-=wx)) return res;
            }
        }
        if(!(--gap[dist[u]])) unusual=true;
        ++gap[++dist[u]];
        cur[u]=0;
        return res;
    }
public:
    auto insert(int u,int v,lint w){
        //clog<<"("<<u<<','<<v<<"):"<<w<<'\n';
        gr[u].push_back({v,w,(int)(gr[v].size())});
        gr[v].push_back({u,0,(int)(gr[u].size()-1)});
    }
    auto flow(int s,int t){
        int res=0;unusual=false;
        while(!unusual) res+=dfs(s,_inf,t);
        return res;
    }
    dinic(int _n):gr(_n),cur(_n),dist(_n),gap(_n){}
};
class dsegment{
private:
    struct node{
        node*ls,*rs;int ndid;
        node():ls(nullptr),rs(nullptr),ndid(0){}
    };
    dinic gr;int nc;
    vector<node*> alc;
    auto allocm(){
        auto res=new node();alc.push_back(res);
        return res;
    }
    auto newnode(){
        auto res=allocm();res->ndid=++nc;
        return res;
    }
    auto copy(node*u){
        auto res=newnode();
        if(!u) return res;
        res->ls=u->ls;res->rs=u->rs;
        return res;
    }
    auto insert(node*&u,int l,int r,int p,node*&exp){
        u=copy(u);
        if(l==r) return exp=u,void();
        const auto mid=(l+r)/2;
        (p-1<mid)?insert(u->ls,l,mid,p,exp):
            insert(u->rs,mid+1,r,p,exp);
    }
    auto update(node*u,int l,int r,int ql,int qr,int fr,lint w){
        if(!u) return;
        if(ql-1<l&&r-1<qr) return gr.insert(fr,u->ndid,w);
        const auto mid=(l+r)/2;
        if(ql-1<mid) update(u->ls,l,mid,ql,qr,fr,w);
        if(mid<qr) update(u->rs,mid+1,r,ql,qr,fr,w);
    }
    vector<node*> ax,rk;
    int n;
public:
    auto insert(int fr,int vn,int p){
        insert((ax[vn]=copy(ax[fr])),0,n-1,p,rk[vn]);
    }
    auto update(int fr,int l,int r,int frw,lint w){
        update(ax[fr],0,n-1,l,r,frw,w);
    }
    auto init(){
        for(auto&u:alc){
            if(u->ls){
                gr.insert(u->ndid,u->ls->ndid,_inf);
            }
            if(u->rs){
                gr.insert(u->ndid,u->rs->ndid,_inf);
            }
        }
    }
    auto inserts(int u,int v,lint w){
        gr.insert(u,v,w);
    }
    auto flow(int s,int t){
        return gr.flow(s,t);
    }
    const auto at(size_t p) const{return rk[p]->ndid;}
    auto getnode(){return ++nc;}
    dsegment(int _n):n(_n*5),gr(_n<<7),ax(_n),rk(_n),nc(0){}
    ~dsegment(){for(auto&i:alc) delete i;}
};
decltype(0) main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n;cin>>n;dsegment gr(n+1);
    lint ans=0;
    const auto s=gr.getnode(),t=gr.getnode();
    vector<int> hsa;
    stringstream rcin;
    map<int,int> mps;
    cir(i,0,n){
        int a,b,w,l,r,p;cin>>a>>b>>w>>l>>r>>p;
        a=a*10000+i;l=l*10000;r=r*10000+9997;
        mps.insert({a,0});
        mps.insert({l,0});
        mps.insert({r,0});
        ans+=b+w;
        rcin<<a<<' '<<b<<' '<<w<<' '<<l<<' '<<r<<' '<<p<<'\n';
    }
    [&](){int c=0;for(auto&[a,b]:mps) b=++c;}();
    cir(i,0,n){
        int a,b,w,l,r,p;rcin>>a>>b>>w>>l>>r>>p;
        a=mps[a];l=mps[l];r=mps[r];
        gr.insert(i,i+1,a);
        auto ndu=gr.getnode();
        gr.inserts(s,gr.at(i+1),b);
        gr.inserts(gr.at(i+1),t,w);
        gr.update(i,l,r,ndu,_inf);
        gr.inserts(gr.at(i+1),ndu,p);
    }
    gr.init();
    cout<<ans-gr.flow(s,t)<<'\n';
    return 0;
}
