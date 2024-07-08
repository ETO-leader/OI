#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using ull=unsigned long long;
const int _inf=1e9+7;
const int MOD=1e9+7;
//Notice: Version 0 means the basic version
template<typename idtype,typename hash_tp=ull>
class segment{
private:
    int n;
    vector<ull> pwn;
    struct node{
        hash_tp hsh;int l,r;
        node*ls,*rs;
        int length(){return r-l+1;}
        void maintain(auto&__pwn){
            hsh=ls->hsh;
            if(rs) hsh+=rs->hsh*__pwn[ls->length()];
        }
        node(hash_tp h,int l,int r):hsh(h),
            l(l),r(r),ls(nullptr),rs(nullptr){}
    };
    node*build(int l,int r){
        node*res=new node(0ull,l,r);
        if(l==r) return res;
        const int mid=(l+r)/2;
        res->ls=build(l,mid);res->rs=build(mid+1,r);
        return res;
    }
    node*__update(node*idu,int p,hash_tp w){
        assert(idu);
        node*res=new node(w,idu->l,idu->r);
        if(res->l==res->r) return res;
        res->ls=idu->ls;res->rs=idu->rs;
        const int mid=(res->l+res->r)/2;
        if(mid>=p)
            res->ls=__update(idu->ls,p,w);
        else
            res->rs=__update(idu->rs,
                p,w*pwn[idu->ls->length()]);
        res->maintain(pwn);
        return res;
    }
    auto chash(node*u,node*v,node*l){
        return u->ls->hsh+v->ls->hsh-l->ls->hsh*2;
    }
    bool __compare(node*u1,node*v1,
        node*l1,node*u2,node*v2,node*l2){
        if(u1->l==u2->l)
            return (u1->hsh+v1->hsh-l1->hsh*2)
                <(u2->hsh+v2->hsh-l2->hsh*2);
        if(chash(u1,v1,l1)==chash(u2,v2,l2))
            return __compare(u1->ls,v1->ls,l1->ls,
                u2->ls,v2->ls,l2->ls);
        return __compare(u1->rs,v1->rs,l1->rs,
            u2->rs,v2->rs,l2->rs);
    }
    void initpw(){
        cout<<"Init: "<<n<<endl;
        pwn.resize(n+1);
        cir(i,1,n+1) pwn[i]=pwn[i-1]*n;
    }
    unordered_map<idtype,node*> ver;
    vector<node*> vn;
public:
    void update(idtype nt,idtype v,int p,hash_tp w){
        assert(ver.count(v));
        ver[nt]=__update(ver[v],p,w);
        vn.push_back(ver[nt]);
    }
    bool compare(idtype u1,idtype v1,idtype l1,
        idtype u2,idtype v2,idtype l2){
        return __compare(ver[u1],ver[v1],
            ver[l1],ver[u2],ver[v2],ver[l2]);
    }
    bool have_version(idtype ______________v){
        return ver.count(______________v);
    }
    void cpversion(idtype x){ver[x]=ver[0];}
    segment(int _n):n(_n){
        ver[0]=build(0,_n-1);initpw();
    }
};
template<typename T>
class graph_tree{
private:
    struct edge{
        int v;T w;bool del;
    };
    vector<vector<edge>> nG,G;
    void insert_e(int u,int v,T w){
        G[u].push_back({v,w,false});
        G[v].push_back({u,w,false});
    }
    void to_binary(int u,int f=0){
        if(nG[u].empty()) return;
        auto it=nG[u].begin();
        for(it;it!=nG[u].end();++it)
            if(it->v==f) break;
        if(it!=nG[u].end()) nG[u].erase(it);
        if(nG[u].empty()) return;
        int rt=u;insert_e(rt,nG[u][0].v,nG[u][0].w);
        cir(i,1,(int)(nG[u].size())-1) {
            int nrt=G.size();G.push_back(vector<edge>());
            insert_e(rt,nrt,0);
            insert_e(rt,nG[u][i].v,nG[u][i].w);
        }
        auto _sz=nG[u].size();
        if(nG[u].size()>1)
            insert_e(rt,nG[u][_sz-1].v,nG[u][_sz-1].w);
        for(auto&[v,w,del]:nG[u])
            if(v!=f) to_binary(v,u);
    }
    vector<int> siz,cnt,hx;
    int dfssz(int u,int f=0){
        siz[u]=1;
        cout<<"Went into "<<u<<'\n'<<flush;
        for(auto&[v,w,del]:G[u]){
            cout<<u<<"->"<<v<<" ("<<w<<") STATE:"<<(del?"deleted":"normal")<<'\n'<<flush;
            if(v!=f&&(!del)) siz[u]+=dfssz(v,u);
        }
        cout<<u<<":"<<siz[u]<<'\n'<<flush;
        return siz[u];
    }
    struct edge_l{int u,v;};
    void findimp_e(int u,int _sz,int&mn,edge_l&e,int f=0){
        for(auto&[v,w,del]:G[u]) if(v!=f&&(!del)){
            findimp_e(v,_sz,mn,e,u);
            const int sizi=max(siz[v],_sz-siz[v]);
            if(sizi<=mn) (mn=sizi),(e={u,v});
        }
    }
    segment<int> seg;
    void dfsx(int u,vector<int>&nl,int f=0){
        assert(u<G.size());assert(u<cnt.size());
        for(auto&[v,w,del]:G[u]) if(v!=f&&(!del)){
            seg.update(u,f,w,(++cnt[w]));
            dfsx(v,nl,u);--cnt[w];
        }
        if(seg.have_version(u)) nl.push_back(u);
    }
    vector<vector<int>> up;int ht;
    void dfs(int u,int f=0){
        up[u][0]=f;hx[u]=hx[f]+1;
        cir(i,1,ht) up[u][i]=up[up[u][i-1]][i-1];
        for(auto&[v,w,del]:G[u])
            if(v!=f&&(!del)) dfs(v,u);
    }
    int lca(int u,int v){
        if(u==v) return u;
        if(hx[u]<hx[v]) swap(u,v);
        cir(i,0,ht) if((1<<i)&(hx[u]-hx[v])) u=up[u][i];
        if(u==v) return u;
        for(int i=ht-1;~i;--i) if(up[u][i]!=up[v][i])
            u=up[u][i],v=up[v][i];
        return up[u][0];
    }
    //delete the edge : u -> v
    void del_edge(int u,int v){
        for(auto&[vx,w,del]:G[u]){
            if(vx==v) del=true;
            return;
        }
        abort();
    }
    void srtdiv(vector<int>&nl,int u,int w){
        sort(nl.begin(),nl.end(),[&](int a,int b){
            return seg.compare(a,u,
                lca(a,u),b,u,lca(b,u))*w;
        });
    }
    int midu,midv,midlca;
    ull __merge(vector<int>&nl,vector<int>&nr){
        int r=0;ull res=0;
        for(auto&i:nl){
            while(r<nr.size()&&seg.compare(i,nr[r],
                lca(i,nr[r]),midu,midv,midlca)) ++r;
            res+=r;
        }
        return res;
    }
    vector<pair<vector<int>,vector<int>>> ar;
    ull divide(int ux){
        cout<<ux<<":\n"<<flush;
        const int _sz=dfssz(ux);
        cerr<<_sz<<' '<<ux<<'\n';
        if(_sz<=1) return 0ull;
        edge_l ex={-1,-1};int mn=_inf;
        findimp_e(ux,_sz,mn,ex);
        auto&[u,v]=ex;
        del_edge(u,v);del_edge(v,u);
        cout<<"delete edge:"<<u<<"<->"<<v<<'\n'<<flush;
        cerr<<mn<<" -> "<<u<<','<<v<<'\n';
        vector<int> nl,nr;
        dfsx(u,nl);dfsx(v,nr);
        srtdiv(nl,u,1);srtdiv(nr,u,-1);
        ar.push_back({nl,nr});
        return __merge(nl,nr)+divide(u)+divide(v);
    }
    edge_l __findnew_e(int ul,int vl,int ur,int vr,bool undefined){
        vector<edge_l> ve;
        for(auto&[a,b]:ar){
            int l=0,r=b.size()*undefined;
            for(auto&i:a){
                if(!undefined){
                    while(r<b.size()&&seg.compare(i,b[r],
                        lca(i,b[r]),ur,vr,lca(ur,vr))) ++r;
                }
                while(l<b.size()&&seg.compare(ul,vl,
                    lca(ul,vl),i,b[l],lca(i,b[l]))) ++l;
                if(r&&l<b.size())
                    ve.push_back({i,b[(l+r)/2]});
            }
        }
        const int m=ve.size()/2;
        nth_element(ve.begin(),ve.begin()+m,
            ve.end(),[&](edge_l&u,edge_l&v){
                return seg.compare(u.u,u.v,
                    lca(u.u,u.v),v.u,v.v,lca(v.u,v.v));
        });
        assert(ve.size());
        return ve[m-1];
    }
    T find_e_w(int u,int v){
        for(auto&[_v,w,del]:G[u])
            if(_v==v) return w;
        abort();
    }
    void calc(int u,int l,vector<int>&v){
        while(u!=l)
            v[find_e_w(up[u][0],u)]++,u=up[u][0];
    }
    int n;
public:
    void setnewmid(int nu,int nv){
        midu=nu;midv=nv;
    }
    auto calc(int u,int v){
        vector<int> res(n);
        calc(u,lca(u,v),res);calc(v,lca(u,v),res);
        return res;
    }
    void insert(int u,int v,T w){
        nG[u].push_back({v,w,false});
        nG[v].push_back({u,w,false});
    }
    pair<int,int> u_findnew_e(int ul,int vl){
        auto [u,v]=__findnew_e(ul,vl,114,514,true);
        return {u,v};
    }
    pair<int,int> findnew_e(int ul,int vl,int ur,int vr){
        auto [u,v]=__findnew_e(ul,vl,ur,vr,false);
        return {u,v};
    }
    ull join(){
        G.clear();G.resize(n+1);up.clear();
        up.assign(n<<1,vector<int>(ht));
        to_binary(1);dfs(1);midlca=lca(midu,midv);
        return divide(1);
    }
    graph_tree(int _n):n(_n-1),G(_n<<1),cnt(_n<<1),
        nG(_n),seg(_n<<1),siz(_n<<1),hx(_n<<1){
        ht=log2(_n<<1)+2;
    }
};
ull rezip(vector<int>&v,int n){
    ull res=0,p=1;
    for(auto&i:v) ((res+=i*p)%=MOD),(p*=n)%=MOD;
    return res;
}
mt19937 rnd(time(NULL));
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n;cin>>n;graph_tree<int> G(n+1);
    ull k;cin>>k;
    cir(i,0,n-1){
        int u,v,w;cin>>u>>v>>w;
        G.insert(u,v,w);
    }
    int ul=1,ur=1,vl=-1,vr=-1;
    auto undefined=[&](){
        return vl<0||vr<0;};
    int ml=rnd()%n+1,mr=rnd()%n+1;
    G.setnewmid(ml,mr);
    cir(i,0,60){
        ull rnk=G.join();
        rnk<k?(vl=ml,vr=mr):(ur=ml,vr=mr);
        auto new_e=undefined()?G.u_findnew_e(ul,vl):
            G.findnew_e(ul,vl,ur,vr);
        ml=new_e.first;mr=new_e.second;
        G.setnewmid(ml,mr);
    }
    //auto ans=G.calc(ul,vl);
    //cout<<rezip(ans,n)<<'\n';
    return 0;
}
