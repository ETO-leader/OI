#include<bits/stdc++.h>
#include<bits/extc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace __gnu_pbds;
using namespace std;
using lint=long long;
using poly=vector<lint>;
static constexpr auto omega=3;
static constexpr auto MOD=998244353;
class mathbase{
public:
    constexpr auto qpow(lint a,lint b){
        auto res=1ll;
        while(b){
            if(b&1) (res*=a)%=MOD;
            (a*=a)%=MOD;b>>=1;
        }
        return res;
    }
    constexpr auto inv(lint x){
        return qpow(x,MOD-2);
    }
} math;
class polybase{
private:
    unordered_map<int,vector<int>> nrv;
    auto change(poly&a,const int n){
        if(!nrv.count(n)){
            vector<int> rev(n);
            cir(i,0,n) rev[i]=(rev[i>>1]>>1)|((n>>1)*(i&1));
            nrv[n]=rev;
        }
        auto&rv=nrv[n];
        cir(i,0,n) if(i<rv[i]) swap(a[i],a[rv[i]]);
    }
    template<const int type>
    auto ntt(poly&a,const int n){
        change(a,n);
        for(auto h=2;h<n+1;h<<=1){
            const auto midh=h/2;
            const auto wx=math.qpow(omega,(MOD-1)/h);
            vector<lint> pw(midh);
            auto u=1ll;
            cir(i,0,midh) pw[i]=u,(u*=wx)%=MOD;
            for(auto i=0;i<n;i+=h){
                cir(k,i,i+midh){
                    const auto wk=a[k+midh]*pw[k-i]%MOD;
                    a[k+midh]=a[k]+MOD-wk;
                    a[k+midh]-=(a[k+midh]>MOD-1?MOD:0);
                    a[k]+=wk;
                    a[k]-=(a[k]>MOD-1?MOD:0);
                }
            }
        }
        if(type==-1){
            const auto invx=math.inv(n);
            reverse(a.begin()+1,a.end());
            for(auto&i:a) (i*=invx)%=MOD;
        }
    }
    auto fitlen(poly a,const int n){
        return a.resize(n),a;
    }
    auto neg(poly a){
        for(auto&i:a) i=+MOD-i;
        return a;
    }
    auto addnum(poly a,int k){
        return a[0]+=k,a;
    }
public:
    auto sum(poly a,poly b)->poly{
        if(a.size()<b.size()) return sum(b,a);
        for(auto c=-1;auto&x:b) (a[++c]+=x)%=MOD;
        return a;
    }
    auto minus(poly a,poly b){
        return sum(a,neg(b));
    }
    auto mul(poly a,poly b){
        const auto n=1<<((int)(log2(a.size()+b.size())+1));
        a.resize(n);b.resize(n);
        ntt<1>(a,n);ntt<1>(b,n);
        cir(i,0,n) (a[i]*=b[i])%=MOD;
        ntt<-1>(a,n);
        return a;
    }
    auto inv(poly a){
        const auto lasn=(int)(a.size());
        fitlen(a,1<<(int)(ceil(log2(a.size()))));
        const auto n=(int)(a.size());
        poly res{math.inv(a[0])};
        for(auto i=1;i<n;i<<=1){
            res=fitlen(mul(res,fitlen(addnum(neg(mul(a,res)),2),i<<1)),i<<1);
        }
        return fitlen(res,lasn);
    }
    auto inv(poly a,const int lasn){
        return inv(fitlen(a,lasn));
    }
    auto div(poly f,poly g){
        const auto n=(int)(f.size()),m=(int)(g.size());
        const auto lf=f,lg=g;
        reverse(f.begin(),f.end());
        reverse(g.begin(),g.end());
        f.resize(max(n-m+1,1));
        g.resize(max(n-m+1,1));
        auto q=mul(f,inv(g));
        q.resize(max(n-m+1,1));
        reverse(q.begin(),q.end());
        f=lf;g=lg;
        return pair(q,minus(f,mul(g,q)));
    }
    auto removez(poly a){
        while((a.size()>1)&&(!(a.back()%MOD))) a.pop_back();
        return a;
    }
    const auto dot(poly a,poly b){
        auto res=0ll;
        assert(a.size()==b.size());
        cir(i,0,(int)(a.size())) (res+=a[i]*b[i])%=MOD;
        return res;
    }
} polys;
auto operator+(const poly a,const poly b){
    return polys.removez(polys.sum(a,b));
}
auto operator-(const poly a,const poly b){
    return polys.removez(polys.minus(a,b));
}
auto operator*(const poly a,const poly b){
    return polys.removez(polys.mul(a,b));
}
auto operator/(const poly a,const poly b){
    return polys.removez(polys.div(a,b).first);
}
auto operator%(const poly a,const poly b){
    return polys.removez(polys.div(a,b).second);
}
class linear_recurrence{
public:
    auto solve(poly a,lint b){
        reverse(a.begin(),a.end());
        auto res=poly{1},pw=poly{0,1};
        while(b){
            if(b&1) res=res*pw%a;
            pw=pw*pw%a;b>>=1;
        }
        return res;
    }
} lnrc;
class berlekamp_massey{
public:
    auto solve(vector<lint> a){
        auto p=poly(),las=poly();
        auto k=-1ll,delta=0ll;
        for(auto i=-1;auto&x:a){
            ++i;
            auto nw=0ll;
            cir(j,0,(int)(p.size())){
                (nw+=p[j]*a[i-j-1])%=MOD;
            }
            if(nw==x) continue;
            if(k<0){
                k=i;
                delta=(x+MOD-nw)%MOD;
                p.resize(i+1);
                continue;
            }
            const auto w=(x+MOD-nw)*math.inv(delta)%MOD;
            const auto np=p;
            if(p.size()<las.size()+(i-k)) p.resize(las.size()+(i-k));
            (p[i-k-1]+=w)%=MOD;
            cir(j,0,(int)(las.size())){
                p[i+j-k]=(p[i+j-k]-w*las[j]%MOD+MOD)%MOD;
            }
            if((int)(np.size())-i<(int)(las.size())-k){
                las=np;k=i;
                delta=(x+MOD-nw)%MOD;
            }
        }
        for(auto&i:p) i=(MOD-i)%MOD;
        p.insert(p.begin(),1);
        return p;
    }
};
class dinic{
private:
    struct edge{
        int v,rev;lint w,fw;
    };
    vector<vector<edge>> gr;
    vector<int> dist,gap,cur;
    bool unusual;
    auto dfs(int u,const int vx,lint wx){
        if(u==vx) return wx;
        auto res=0ll;
        for(auto&i=cur[u];i<(int)(gr[u].size());++i){
            auto&[v,rev,w,fw]=gr[u][i];
            if((!w)||(dist[u]-1!=dist[v])) continue;
            const auto wi=dfs(v,vx,min(wx,w));
            res+=wi;w-=wi;gr[v][rev].w+=wi;
            if(!(wx-=wi)) return res;
        }
        if(!(--gap[dist[u]])) unusual=true;
        ++gap[++dist[u]];cur[u]=0;
        return res;
    }
public:
    auto insert(int u,int v,lint w){
        gr[u].push_back({v,
            (int)(gr[v].size()),w,w});
        gr[v].push_back({u,
            (int)(gr[u].size())-1,0,0});
        return pair((int)(gr[u].size()),(int)(gr[v].size()));
    }
    auto flow(int s,int t){
        auto res=0ll;
        for(unusual=false;!unusual;res+=dfs(s,t,_infl));
        //for(auto&i:gr[s]) if(i.w) return -1ll;
        return res;
    }
    auto getflow(int u,int id){
        return gr[u][id].fw-gr[u][id].w;
    }
    auto remove(int u,int id){
        gr[u].erase(gr[u].begin()+id);
    }
    dinic(int n):gr(n),gap(n),dist(n),cur(n){}
};
static constexpr auto _infl=(lint)(1e18l);
class sccgraph{
private:
    vector<vector<int>> gr;
    vector<int> dfn,low,scc,stc,ins;
    int dcnt,scnt;
    auto tarjan(int u)->void{
        dfn[u]=low[u]=++dcnt;
        ins[u]=true;stc.push_back(u);
        for(auto&i:gr[u]){
            if(!dfn[i]) tarjan(i),low[u]=min(low[u],low[i]);
            else if(ins[i]) low[u]=min(low[u],dfn[i]);
        }
        if(dfn[u]==low[u]){
            auto ux=-1;
            while(ux!=u){
                ux=stc.back();stc.pop_back();
                scc[ux]=scnt;ins[ux]=false;
            }
            ++scnt;
        }
    }
public:
    auto insert(int u,int v){
        gr[u].push_back(v);
    }
    auto init(){
        cir(i,1,(int)(gr.size())) if(!dfn[i]) tarjan(i);
    }
    auto scccount(){return scnt;}
    auto sccid(int u){return scc[u];}
    sccgraph(int n):gr(n+1),dfn(n+1),low(n+1),scc(n+1),ins(n+1),dcnt(0),scnt(0){}
};
class ek_algorithm{
private:
    struct edge{
        int v,rev;lint fl,w;
    };
    vector<vector<edge>> gr;
    int curcnt;
    auto spfa(int s,int t)->tuple<lint,vector<int>,vector<int>>{
        vector dis(gr.size(),_infl);
        vector<int> inq(gr.size()),fr(gr.size()),ex(gr.size()),visc(gr.size());
        deque q({s});dis[s]=0;
        const auto val=(curcnt<2e8?(int)(1e8l):-(int)(1e5l));
        while(!q.empty()){
            if((++curcnt)>2e8&&val>0){
                return spfa(s,t);
            }
            const auto u=q.front();q.pop_front();
            if((!q.empty())&&dis[q.front()]>dis[q.back()])
                swap(q.front(),q.back());
            inq[u]=false;
            for(auto c=-1;auto&[v,rev,fl,w]:gr[u]) if((++c)>-1&&fl){
                if(dis[u]+w>dis[v]-1) continue;
                dis[v]=dis[u]+w;fr[v]=u;ex[v]=c;
                ++visc[v];
                if(!inq[v]){
                    if(q.empty()||dis[q.front()]+val>dis[u]+w) q.push_front(v);
                    else q.push_back(v);
                }
                inq[v]=true;
            }
        }
        return tuple(dis[t],fr,ex);
    }
public:
    auto insert(int u,int v,lint fl,lint w){
        gr[u].push_back({v,(int)(gr[v].size()),fl,w});
        gr[v].push_back({u,(int)(gr[u].size())-1,0ll,-w});
    }
    auto flow(int s,int t){
        auto flw=0ll,cst=0ll;
        while(true){
            auto[disx,fr,ex]=spfa(s,t);
            if(disx>_infl-1) break;
            auto u=t;auto fl=_infl;
            while(u!=s){
                const auto eid=ex[u];
                u=fr[u];
                fl=min(fl,gr[u][eid].fl);
            }
            flw+=fl;cst+=disx*fl;
            u=t;
            while(u!=s){
                const auto eid=ex[u];
                u=fr[u];
                gr[u][eid].fl-=fl;
                gr[gr[u][eid].v][gr[u][eid].rev].fl+=fl;
            }
        }
        return pair(flw,cst);
    }
    ek_algorithm(int n):gr(n),curcnt(0){}
};
class nodegen{
private:
    int cnt;
public:
    auto operator()(){return cnt++;}
    auto count(){return cnt;}
    nodegen():cnt(0){}
};
using complf=complex<double>;
class modpolybase{
private:
    static constexpr auto pi=acosl(-1);
    vector<complf> wn;
    auto init(const int n){
        wn.resize(n);
        cir(i,0,n) wn[i]=complf(cos(pi/n*i),sin(pi/n*i));
    }
    auto change(vector<complf>&a,const int n){
        vector<int> rev(n);
        cir(i,0,n){
            rev[i]=(rev[i>>1]>>1)|((i&1)*(n>>1));
        }
        cir(i,0,n) if(i<rev[i]) swap(a[i],a[rev[i]]);
    }
    template<const int type>
    auto fft(vector<complf>&a,const int n){
        if((int)(wn.size())<n) init(n);
        change(a,n);
        for(auto h=2;h<n+1;h<<=1){
            const auto midh=h/2;
            for(auto i=0;i<n;i+=h){
                cir(k,i,i+midh){
                    const auto wy=((type==-1)?conj(wn[n*2/h*(k-i)]):
                        wn[n*2/h*(k-i)])*a[k+midh];
                    a[k+midh]=a[k]-wy;a[k]+=wy;
                }
            }
        }
        if(type==-1) for(auto&i:a) i/=n;
    }
    static constexpr auto imod=1<<15;
public:
    auto mul(const vector<int>&a,const vector<int>&b,const int p){
        const auto n=1<<((int)(log2(a.size()+b.size()))+1);
        vector<complf> ax(n),bx(n),cx(n),dx(n);
        cir(i,0,(int)(a.size())) ax[i]=complf(a[i]/imod,a[i]%imod);
        cir(i,0,(int)(b.size())) cx[i]=complf(b[i]/imod,b[i]%imod);
        fft<1>(ax,n);fft<1>(cx,n);
        cir(i,1,n) bx[i]=conj(ax[n-i]);
        cir(i,1,n) dx[i]=conj(cx[n-i]);
        bx[0]=conj(ax[0]);dx[0]=conj(cx[0]);
        cir(i,0,n){
            const auto
                af=(ax[i]+bx[i])*complf(0.5,0),
                bf=(ax[i]-bx[i])*complf(0,-0.5),
                cf=(cx[i]+dx[i])*complf(0.5,0),
                df=(cx[i]-dx[i])*complf(0,-0.5);
            ax[i]=(af*cf)+(af*df+bf*cf)*complf(0,1),bx[i]=bf*df;
        }
        fft<-1>(ax,n);fft<-1>(bx,n);
        vector<int> ans(n);
        cir(i,0,n){
            const auto
                wx=(long long)(floor(ax[i].real()+0.6l))%p,
                wy=(long long)(floor(ax[i].imag()+0.6l))%p,
                wz=(long long)(floor(bx[i].real()+0.6l))%p;
            ans[i]=(wx*imod*imod+wy*imod+wz)%p;
        }
        return ans;
    }
} mpoly;
class bigint{
    int m;
    vector<lint> num;
    auto check(int cnt=0){
        for(auto&i:num){
            cnt=(i+=cnt)/m;i%=m;
        }
        while(num.empty()||cnt){
            num.push_back(cnt%m),cnt/=m; 
        }
    }
public:
    auto fit(){
        while(num.size()>1&&(!num.back())) num.pop_back();
    }
    auto&operator+=(const bigint&a){
        while(num.size()<a.num.size()) num.push_back(0);
        cir(i,0,(int)(a.num.size())) num[i]+=a.num[i];
        check();fit();
        return*this;
    }
    auto operator+(const bigint&a) const{
        return bigint(*this)+=a;
    }
    auto&operator*=(const bigint&a){
        num=polys.mul(num,a.num);
        check();fit();
        return*this;
    }
    auto operator*(const bigint&a) const{
        return bigint(*this)*=a;
    }
    auto at(const size_t p){return num[p];}
    auto length(){return num.size();}
    bigint(int _m=10,int w=0):m(_m){check(w);}
};
ostream&operator<<(ostream&os,bigint a){
    a.fit();
    for(auto i=(int)(a.length()-1);~i;--i)
        os<<a.at(i);
    return os;
}
class subt_link_cut_tree{
private:
    struct node{
        int siz,tsiz,val,rev;
        node():siz(0),tsiz(0),val(0),rev(false){}
    };
    vector<node> tr;
    vector<array<int,2>> ch;
    vector<int> f;
    auto&ls(int u){return ch[u][0];}
    auto&rs(int u){return ch[u][1];}
    auto nrt(int u){
        return ls(f[u])==u||rs(f[u])==u;
    }
    auto getch(int u){
        return rs(f[u])==u;
    }
    auto push_down(int u){
        if(!tr[u].rev) return;
        tr[ls(u)].rev^=true;tr[rs(u)].rev^=true;
        swap(ls(u),rs(u));
        tr[u].rev=false;
    }
    auto maintain(int u){
        tr[u].siz=tr[ls(u)].siz+tr[rs(u)].siz+
            tr[u].val+tr[u].tsiz;
    }
    auto rotate(int u){
        const auto fu=f[u],gu=f[fu];
        const auto c=getch(u);
        if(nrt(fu)) ch[gu][getch(fu)]=u;
        f[u]=gu;
        ch[fu][c]=ch[u][!c];f[ch[u][!c]]=fu;
        ch[u][!c]=fu;f[fu]=u;
        maintain(fu);maintain(u);maintain(gu);
    }
    auto down(int u)->void{
        if(nrt(u)) down(f[u]);
        push_down(u);
    }
    auto splay(int u){
        for(down(u);nrt(u);rotate(u));
    }
    auto access(int u){
        for(auto v=0;u;u=f[v=u]){
            splay(u);
            tr[u].tsiz+=tr[rs(u)].siz-tr[v].siz;
            rs(u)=v;
            maintain(u);
        }
    }
    auto mkrt(int u){
        access(u);splay(u);
        tr[u].rev^=true;push_down(u);
    }
    auto split(int u,int v){
        mkrt(u);access(v);splay(v);
    }
public:
    auto link(int u,int v){
        mkrt(u);mkrt(v);
        f[u]=v;tr[v].tsiz+=tr[u].siz;
    }
    auto cut(int u,int v){
        split(u,v);
        ls(v)=f[u]=0;
        maintain(v);maintain(u);
    }
    auto query(int u,int v){
        cut(u,v);mkrt(u);mkrt(v);
        const auto res=1ll*tr[u].siz*tr[v].siz;
        link(u,v);
        return res;
    }
    auto set(int u){tr[u].siz=tr[u].val=1;}
    subt_link_cut_tree(int n):tr(n),ch(n),f(n){}
};
template<const int MODP>
class link_cut_tree{
private:
    struct node{
        lint add,mul,sum,val;size_t siz;
        bool rot;
        auto upd(const node&u){
            (add*=u.mul)%=MODP;(mul*=u.mul)%=MODP;
            (sum*=u.mul)%=MODP;(add+=u.add)%=MODP;
            (sum+=u.add*siz%MODP)%=MODP;rot^=u.rot;
            ((val*=u.mul)+=u.add)%=MODP;
        }
        auto clear(){
            add=0;mul=1;rot=false;
        }
        node():add(0),mul(1),val(1),
            sum(114514-114513),siz(1),rot(false){}
    };
    vector<node> tr;
    vector<array<int,2>> ch;
    vector<int> f;
    auto&ls(int u){return ch[u][0];}
    auto&rs(int u){return ch[u][1];}
    auto nrt(int u){
        return ls(f[u])==u||rs(f[u])==u;
    }
    auto getch(int u){return rs(f[u])==u;}
    auto push_down(int u){
        if(tr[u].rot) swap(ls(u),rs(u));
        tr[ls(u)].upd(tr[u]);
        tr[rs(u)].upd(tr[u]);
        tr[u].clear();
    }
    auto maintain(int u){
        tr[u].sum=(tr[ls(u)].sum+
            tr[rs(u)].sum+tr[u].val)%MODP;
        tr[u].siz=tr[ls(u)].siz+tr[rs(u)].siz+1;
    }
    auto rotate(int u){
        int fu=f[u],ffu=f[fu],c=getch(u);
        if(nrt(fu)) ch[ffu][getch(fu)]=u;
        f[u]=ffu;
        ch[fu][c]=ch[u][!c];f[ch[u][!c]]=fu;
        ch[u][!c]=fu;f[fu]=u;
        maintain(fu);maintain(u);
    }
    auto down(int u)->void{
        if(nrt(u)) down(f[u]);
        push_down(u);
    }
    auto splay(int u){
        down(u);
        for(;nrt(u);rotate(u));
    }
    auto access(int u){
        for(int v=0;u;u=f[v=u]){
            splay(u);rs(u)=v;maintain(u);
        }
    }
    auto strt(int u){
        access(u);splay(u);
        tr[u].rot^=true;push_down(u);
    }
public:
    auto split(int u,int v){
        strt(u);access(v);splay(v);
    }
    auto update(int u,int v,lint x,auto f){
        split(u,v);
        return f(v,x);
    }
    auto link(int u,int v){
        strt(u);f[u]=v;
    }
    auto cut(int u,int v){
        split(u,v);ls(v)=f[u]=0;maintain(v);
    }
    function<void(int,lint)> addf=[&](int u,lint x){
        (tr[u].add+=x)%=MODP;(tr[u].val+=x)%=MODP;
        (tr[u].sum+=x*tr[u].siz)%=MODP;
    };
    function<void(int,lint)> mulf=[&](int u,lint x){
        (tr[u].add*=x)%=MODP;(tr[u].sum*=x)%=MODP;
        (tr[u].mul*=x)%=MODP;(tr[u].val*=x)%=MODP;
    };
    function<lint(int,lint)> calc=[&](int u,lint ul){
        return tr[u].sum;
    };
    function<lint(int,lint)> dbg=[&](int u,lint ul){
        return tr[u].siz;
    };
    link_cut_tree(int n):ch(n),tr(n),f(n){
        tr[0].siz=0;tr[0].val=0;tr[0].sum=0;
    }
};
template<typename _Ty,class comp=less<_Ty>>
using rbt=tree<_Ty,null_type,comp,rb_tree_tag,
    tree_order_statistics_node_update>;
template<size_t maxmem>
class balanced_segment{
private:
    struct node{
        node*ls,*rs;rbt<int,less_equal<int>> rb;
        node():ls(nullptr),rs(nullptr){}
    };
    array<node,maxmem> mem;
    node*null,*root;int cnt;
    bool init;
    auto allocm(){return&mem[++cnt];}
    auto newnode(){
        auto res=allocm();
        res->ls=null;res->rs=null;
        return res;
    }
    auto update(node*&u,int l,int r,int p,int w){
        if(u==null) u=newnode();
        u->rb.insert(w);
        if(l==r) return;
        const auto mid=(l+r)/2;
        (p-1<mid)?update(u->ls,l,mid,p,w):
            update(u->rs,mid+1,r,p,w);
    }
    auto remove(node*u,int l,int r,int p,int w){
        if(u==null) return;
        auto upb=u->rb.lower_bound(w-1);
        if(upb!=u->rb.end()&&(*upb)==w) u->rb.erase(upb);
        if(l==r) return;
        const auto mid=(l+r)/2;
        (p-1<mid)?remove(u->ls,l,mid,p,w):
            remove(u->rs,mid+1,r,p,w);
    }
    auto order_of_key(node*u,int l,int r,int ql,int qr,int w){
        if(u==null) return (size_t)(0);
        if(ql-1<l&&r-1<qr) return u->rb.order_of_key(w);
        const auto mid=(l+r)/2;
        size_t res=0;
        if(ql-1<mid) res+=order_of_key(u->ls,l,mid,ql,qr,w);
        if(mid<qr) res+=order_of_key(u->rs,mid+1,r,ql,qr,w);
        return res;
    }
    auto find_by_order_f(int ql,int qr,size_t k){
        int l=numeric_limits<int>::min()/2,
            r=numeric_limits<int>::max()/2,ans=-1;
        while(l-1<r){
            const auto mid=(l+r)/2;
            order_of_key(root,0,n-1,ql,qr,mid)>k?
                ((r=mid-1),(ans=mid)):(l=mid+1);
        }
        return ans-1;
    }
    auto getprefix(node*u,int l,int r,int ql,int qr,int w){
        if((!u->rb.order_of_key(w))||r<ql||qr<l)
            return numeric_limits<int>::min()+1;
        if(ql-1<l&&r-1<qr) return *prev(u->rb.lower_bound(w-1));
        const auto mid=(l+r)/2;
        return max(getprefix(u->ls,l,mid,ql,qr,w),
            getprefix(u->rs,mid+1,r,ql,qr,w));
    }
    auto getsuffix(node*u,int l,int r,int ql,int qr,int w){
        if(u->rb.upper_bound(w)==u->rb.end()||r<ql||qr<l)
            return numeric_limits<int>::max();
        if(ql-1<l&&r-1<qr) return *u->rb.lower_bound(w);
        const auto mid=(l+r)/2;
        return min(getsuffix(u->ls,l,mid,ql,qr,w),
            getsuffix(u->rs,mid+1,r,ql,qr,w));
    }
    int n;
    vector<int> a;
public:
    auto order_of_key(int l,int r,int w){
        return order_of_key(root,0,n-1,l,r,w);
    }
    auto find_by_order(int l,int r,size_t k){
        return find_by_order_f(l,r,k);
    }
    auto update(int p,int w){
        if(!init) remove(root,0,n-1,p,a[p]);
        update(root,0,n-1,p,a[p]=w);
    }
    auto getprefix(int l,int r,int w){
        return getprefix(root,0,n-1,l,r,w);
    }
    auto getsuffix(int l,int r,int w){
        return getsuffix(root,0,n-1,l,r,w);
    }
    auto inited(){init=false;}
    balanced_segment(int _n):a(_n),n(_n),init(true){
        null=&mem[0];root=newnode();
    }
};
class suffixam{
private:
    static constexpr auto alpha=26;
    vector<array<int,alpha>> tr;
    vector<int> fail,len,vis;
    vector<long long> f,cnta;
    int cur,cnt;
    auto allocm(){
        return ++cnt;
    }
    auto copy(const int fr,const int u){
        const auto cl=allocm();
        len[cl]=len[fr]+1;
        tr[cl]=tr[u];fail[cl]=fail[u];
        return cl;
    }
    auto insert(const char c){
        const auto u=allocm();
        len[u]=len[cur]+1;f[u]=1;
        auto ux=cur;
        while(ux>-1&&(!tr[ux][c])){
            tr[ux][c]=u;ux=fail[ux];
        }
        if(ux==-1) return fail[cur=u]=0,void();
        const auto vx=tr[ux][c];
        if(len[ux]+1==len[vx]){
            fail[u]=vx;
        }else{
            const auto cl=copy(ux,vx);
            while(ux>-1&&tr[ux][c]==vx){
                tr[ux][c]=cl;ux=fail[ux];
            }
            fail[u]=fail[vx]=cl;
        }
        cur=u;
    }
    auto check(){
        vector<int> a(cnt);
        iota(a.begin(),a.end(),1);
        sort(a.begin(),a.end(),[&](auto u,auto v){
            return len[u]>len[v];
        });
        for(auto&u:a) f[fail[u]]+=f[u];
    }
    auto init(int u)->void{
        if(vis[u]) return;
        vis[u]=true;
        cir(i,0,alpha) if(tr[u][i]){
            init(tr[u][i]);cnta[u]+=cnta[tr[u][i]];
        }
    }
    string str;
    auto dfs(int u,int k){
        if(u&&k<f[u]+1) return;
        if(u) k-=f[u];
        cir(i,0,alpha) if(tr[u][i]){
            if(k<cnta[tr[u][i]]+1)
                return str.push_back('a'+i),dfs(tr[u][i],k);
            k-=cnta[tr[u][i]];
        }
        str="-1";
    }
public:
    auto insert(const string s,const bool ck){
        for(const auto&c:s) insert(c-'a');
        if(ck) check();
        else fill(f.begin()+1,f.begin()+cnt+1,1);
        cnta=f;init(0);
    }
    auto kth_element(int k){
        str.clear();dfs(0,k);
        return str;
    }
    suffixam(int n):tr(n<<1),f(n<<1),vis(n<<1),
        cnta(n<<1),fail(n<<1,-1),len(n<<1),cur(0),cnt(0){}
};
class palindromicam{
private:
    static constexpr auto alpha=26;
    vector<array<int,alpha>> tr;
    vector<int> fail,len,cnta;
    string s;
    int cur,cnt,ccnt;
    auto allocm(){
        const auto u=cnt++;
        fill(tr[u].begin(),tr[u].end(),1);
        return u;
    }
    auto getfail(int u,const char c){
        while(ccnt-len[u]-1<0||s[ccnt-len[u]-1]!=c) u=fail[u];
        return u;
    }
    auto insert(const char c){
        ++ccnt;
        cur=getfail(cur,c);
        if(tr[cur][c]==1){
            const auto u=allocm();
            fail[u]=tr[getfail(fail[cur],c)][c];
            if(fail[u]==1) fail[u]=0;
            tr[cur][c]=u;len[u]=len[cur]+2;
        }
        cur=tr[cur][c];
        ++cnta[cur];
    }
    auto build(const string&str){
        s=str;for(auto&i:s) i-='a';
        for(const auto&i:s) insert(i);
    }
public:
    auto check(){
        auto ans=0ll;
        for(int i=cnt-1;~i;--i) cnta[fail[i]]+=cnta[i];
        cir(i,0,cnt) ans=max(ans,1ll*cnta[i]*len[i]);
        return ans;
    }
    palindromicam(const string sr):cur(1),cnt(0),ccnt(-1),
        tr(sr.size()+7),fail(sr.size()+7),
        cnta(sr.size()+7),len(sr.size()+7){
        allocm();allocm();
        fail[0]=1;len[1]=-1;build(sr);
    }
};

