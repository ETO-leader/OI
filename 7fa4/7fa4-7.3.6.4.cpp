#include<bits/stdc++.h>
#ifdef __DEBUG__
    #include"eformat"
#endif
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
using VI=vector<int>;
static constexpr auto MOD=998244353;
class dsu{
private:
    VI f;
public:
    auto findset(int u)->int{
        return f[u]==u?u:f[u]=findset(f[u]);
    }
    auto merge(int u,int v){
        f[findset(u)]=findset(v);
    }
    dsu(int n):f(n){iota(f.begin(),f.end(),0);}
};
class matrix{
private:
    array<array<lint,2>,2> a;
public:
    auto&operator[](size_t p){return a[p];}
    auto operator*(matrix m) const{
        matrix res;
        cir(k,0,2) cir(i,0,2) cir(j,0,2)
            (res[i][j]+=a[i][k]*m[k][j])%=MOD;
        return res;
    }
    matrix(){memset(a.begin(),0,sizeof(a));}
};
class segment{
private:
    vector<matrix> tr;
    constexpr auto ls(int u){return u*2;}
    constexpr auto rs(int u){return u*2+1;}
    auto maintain(int u){
        tr[u]=tr[ls(u)]*tr[rs(u)];
    }
    auto update(int u,int l,int r,int p,matrix m){
        if(l==r) return tr[u]=m,void();
        const auto mid=(l+r)/2;
        p-1<mid?update(ls(u),l,mid,p,m):
            update(rs(u),mid+1,r,p,m);
        maintain(u);
    }
    auto query(int u,int l,int r,int ql,int qr){
        if(ql-1<l&&r-1<qr) return tr[u];
        const auto mid=(l+r)/2;
        if(qr-1<mid) return query(ls(u),l,mid,ql,qr);
        if(mid<ql) return query(rs(u),mid+1,r,ql,qr);
        return query(ls(u),l,mid,ql,qr)*
            query(rs(u),mid+1,r,ql,qr);
    }
    int n;
public:
    auto update(int p,matrix m){
        update(1,1,n,p,m);
    }
    auto query(int l,int r){
        return query(1,1,n,l,r);
    }
    segment(int _n):n(_n),tr(_n<<2){}
};
constexpr auto qpow(lint a,lint b){
    lint res=1;
    while(b){
        if(b&1) (res*=a)%=MOD;
        (a*=a)%=MOD;b>>=1;
    }
    return res;
}
constexpr auto inv(lint a){
    return qpow(a,MOD-2);
}
vector<VI> gr;
VI siz,fx,top,bottom,dfn,h;
vector<lint> ft,ff,cft,cff;
vector<array<lint,2>> dx;
auto dfssz(int u,int f=0)->int{
    siz[u]=1;h[u]=h[f]+1;fx[u]=f;
    for(auto&i:gr[u]) if(i!=f) siz[u]+=dfssz(i,u);
    return siz[u];
}
auto dfsch(int u,int&cnt,int utop=-1,int f=0)->void{
    if(utop<0) utop=u;
    dfn[u]=++cnt;top[u]=utop;bottom[utop]=u;
    if(f) gr[u].erase(find(gr[u].begin(),gr[u].end(),f));
    sort(gr[u].begin(),gr[u].end(),[](int u,int v){
        return siz[u]>siz[v];
    });
    if(!gr[u].empty()){
        dfsch(gr[u][0],cnt,utop,u);
        dx[u][0]=(dx[gr[u][0]][0]+dx[gr[u][0]][1])%MOD;
        dx[u][1]=dx[gr[u][0]][0];
    }
    cir(p,1,(int)(gr[u].size())){
        auto&i=gr[u][p];
        dfsch(i,cnt,-1,u);
        (dx[u][0]*=(dx[i][0]+dx[i][1]))%=MOD;
        (dx[u][1]*=dx[i][0])%=MOD;
        (ff[u]*=dx[i][0])%=MOD;
        (ft[u]*=(dx[i][0]+dx[i][1]))%=MOD;
    }
}
auto getsgu(int u,segment&sg){
    matrix bsc;bsc[0][0]=1;
    auto r=(sg.query(dfn[u],dfn[bottom[top[u]]])*bsc);
    return vector<lint>({r[0][0],r[1][0]});
}
auto update(int u,segment&sg,matrix a,bool rebuild=false){
    const auto fr=u;
    while(fx[u=top[u]]){
        auto w=getsgu(u,sg);
        (ff[fx[u]]*=inv(w[0]))%=MOD;
        (ft[fx[u]]*=inv(w[0]+w[1]))%=MOD;
        u=fx[u];
    }
    u=fr;
#if defined(__DEBUG__)
    clog<<fr<<":\n";
    clog<<"from:\n";
    auto g=sg.query(dfn[u],dfn[u]);
    cir(i,0,2){
        cir(j,0,2) clog<<g[i][j]<<' ';
        clog<<'\n';
    }
    clog<<"to\n";
    cir(i,0,2){
        cir(j,0,2) clog<<a[i][j]<<' ';
        clog<<'\n';
    }
    clog<<fmt::format<lint>("Now: ff[1]={},ft[1]={},ans(2,0)={},ans(2,1)={}",{ff[1],ft[1],(lint)(getsgu(2,sg)[0]),(lint)(getsgu(2,sg)[1])})<<'\n';
    clog<<'\n';
#endif
    sg.update(dfn[u],a);
    while(fx[u=top[u]]){
        if(!rebuild){
            auto w=getsgu(u,sg);
            (ff[fx[u]]*=w[0])%=MOD;
            (ft[fx[u]]*=(w[0]+w[1]))%=MOD;
        }else{
            ff[fx[u]]=cff[fx[u]];
            ft[fx[u]]=cft[fx[u]];
        }
        u=fx[u];
        matrix ins;ins[0][0]=ins[0][1]=ft[u];
        ins[1][0]=ff[u];
        sg.update(dfn[u],ins);
    }
}
auto query(segment&sg,int u=1){
    const auto w=getsgu(u,sg);
    return (w[0]+w[1])%MOD;
}
auto init(int n){
    gr.resize(n+1);siz.resize(n+1);fx.resize(n+1);
    top.resize(n+1);bottom.resize(n+1);h.resize(n+1);
    dfn.resize(n+1);ft.resize(n+1,1);ff.resize(n+1,1);
    dx.resize(n+1,array<lint,2>({1,1}));
}
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n,m;cin>>n>>m;init(n);
    dsu ds(n+1);
    vector<pair<int,int>> us;
    unordered_set<int> nds;
    cir(i,0,m){
        int u,v;cin>>u>>v;
        if(ds.findset(u)==ds.findset(v)){
            us.push_back({u,v});
            nds.insert(u);nds.insert(v);
        }else{
            gr[u].push_back(v);gr[v].push_back(u);
            ds.merge(u,v);
        }
    }
    [](){int c=0;dfssz(1);dfsch(1,c);}();
    segment sg(n);
    cir(i,1,n+1){
        matrix ins;ins[1][0]=ff[i];
        ins[0][0]=ins[0][1]=ft[i];
        sg.update(dfn[i],ins);
    }
    cff=ff;cft=ft;
    VI nx(nds.begin(),nds.end());
    lint ans=0;
    int cnts=0;
    cir(s,0,(1<<us.size())) [&](){
        unordered_set<int> nl;
        cir(i,0,(int)(us.size())) if(s&(1<<i)){
            nl.insert(us[i].first);
            nl.insert(us[i].second);
        }
        VI upd(nl.begin(),nl.end());
        sort(upd.begin(),upd.end(),[](int u,int v){
            return h[u]>h[v];
        });
        for(auto&u:upd){
            matrix ins;ins[0][0]=ins[0][1]=0;
            ins[1][0]=ff[u];
            update(u,sg,ins);
        }
        auto ansi=query(sg);
        (ans+=MOD+(((__builtin_popcount(s)&1)?-1:1)*ansi))%=MOD;
        for(auto&u:upd){
            matrix ins;
            ins[0][0]=ins[0][1]=cft[u];
            ins[1][0]=cff[u];
            update(u,sg,ins,true);
        }
    }();
    cout<<ans<<'\n';
    return 0;
}
