#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using db=long double;
static constexpr int maxsiz=1e5+7;
template<const size_t maxmem>
class solution{
private:
//classes, constexpr functions, memery functions, functions
    static constexpr auto α=0.75;
    struct node{
        node*ls,*rs,*lval,*rval;
        uint64_t l,r;size_t siz;
        unordered_set<int> idl;
        auto rank(){return solution::midf(l,r);}
        auto cmp(node*lvalx,node*rvalx){
            return pair(lval->rank(),rval->rank())<
                pair(lvalx->rank(),rvalx->rank());
        }
        auto maintain(){siz=ls->siz+rs->siz+1;}
        auto check(){
            return ls->siz*1.0/siz>α||rs->siz*1.0/siz>α;
        }
        node():ls(nullptr),rs(nullptr),lval(nullptr),
            rval(nullptr),l(0),r(0),siz(1){}
    };
    array<node,maxmem> mem;
    node*null,*root;int cnt,n;
    vector<pair<uint64_t,int>> tr;
    auto allocm(){return&mem[++cnt];}
    auto newnode(uint64_t l,uint64_t r,node*lv,node*rv){
        auto res=allocm();res->ls=res->rs=null;
        res->l=l;res->r=r;res->siz=1;
        res->lval=lv;res->rval=rv;
        return res;
    }
    auto clear(node*u){
        return u->ls=null,u->rs=null,u;
    }
    constexpr auto ls(int u){return u*2;}
    constexpr auto rs(int u){return u*2+1;}
    static constexpr auto midf(auto a,auto b){
        return (a+b)/2;
    }
    vector<node*> rb,nodep;
//balanced tree
    auto rebuild(uint64_t l,uint64_t r,size_t ql,size_t qr){
        if(qr<ql) return null;
        const auto rgm=midf(l,r);
        const auto qmid=midf(ql,qr);
        auto res=rb[qmid];res->l=l;res->r=r;
        for(auto&i:res->idl) update(1,0,n-1,i,res->rank());
        if(l==r) return res;
        if(rgm&&qmid) res->ls=rebuild(l,rgm-1,ql,qmid-1);
        res->rs=rebuild(rgm+1,r,qmid+1,qr);
        return res->maintain(),res;
    }
    auto destroy(node*u){
        if(u==null) return;
        auto lsu=u->ls,rsu=u->rs;
        destroy(lsu);
        rb.push_back(clear(u));
        destroy(rsu);
    }
    auto insert(node*&u,uint64_t l,uint64_t r,node*x,node*y,int id){
        if(u==null) return u=newnode(l,r,x,y),u->idl.insert(id),u;
        if(u->lval==x&&u->rval==y) return u->idl.insert(id),u;
        const auto mid=midf(l,r);
        auto res=u->cmp(x,y)?insert(u->rs,mid+1,r,x,y,id):
            insert(u->ls,l,mid-1,x,y,id);
        u->maintain();
        if(u->check()){
            rb.clear();destroy(u);
            u=rebuild(l,r,0,rb.size()-1);
        }
        return res;
    }
//balanced tree: debug
#ifdef __DEBUG__
    auto print(node*u,int sum){
        string s;
        cir(i,0,sum) s+="    ";
        if(u==null) return clog<<s<<"null\n",void();
        clog<<s<<"range="<<u->l<<','<<u->r<<" rank="<<u->rank()<<" node-list is[";
        int cnt=0;
        for(auto&i:u->idl) clog<<i<<(((++cnt)==u->idl.size())?"":",");
        clog<<"]\n";
        clog<<s<<"ls{\n";
        print(u->ls,sum+1);
        clog<<s<<"}\n";
        clog<<s<<"rs{\n";
        print(u->rs,sum+1);
        clog<<s<<"}\n";
    }
    auto prt(){print(root,0);}
#endif
//segment tree
    auto maintain(int u){
        tr[u]=max(tr[ls(u)],tr[rs(u)]);
    }
    auto update(int u,int l,int r,int p,uint64_t w){
        if(l==r) return tr[u]={w,-p},void();
        const auto mid=midf(l,r);
        p-1<mid?update(ls(u),l,mid,p,w):
            update(rs(u),mid+1,r,p,w);
        maintain(u);
    }
    auto query(int u,int l,int r,int ql,int qr){
        if(ql-1<l&&r-1<qr) return tr[u];
        const auto mid=midf(l,r);
        auto res=pair((uint64_t)(0),-l);
        if(ql-1<mid) res=max(res,query(ls(u),l,mid,ql,qr));
        if(mid<qr) res=max(res,query(rs(u),mid+1,r,ql,qr));
        return res;
    }
public:
    auto copy(int l,int r,int k){
        nodep[k]->idl.erase(k);
        nodep[k]=insert(root,1,numeric_limits<
            int64_t>::max(),nodep[l],nodep[r],k);
        update(1,0,n-1,k,nodep[k]->rank());
#ifdef __DEBUG__
        clog<<l<<' '<<r<<' '<<k<<":\n";
        prt();
        clog<<"\n\n";
#endif
    }
    auto query(int l,int r){
        return -query(1,0,n-1,l,r).second;
    }
    solution(int _n):cnt(0),n(_n),tr(_n<<2){
        null=&mem[0];root=null;
        nodep.resize(_n,nullptr);
        cir(i,0,_n) nodep[i]=insert(root,1,
            numeric_limits<int64_t>::max(),null,null,i);
        cir(i,0,_n) update(1,0,_n-1,i,nodep[i]->rank());
    }
};
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n,q;cin>>n>>q;solution<maxsiz> sol(n);
    cir(i,0,q){
        string s;cin>>s;
        if(s[0]=='C'){
            int l,r,k;cin>>l>>r>>k;
            sol.copy(l-1,r-1,k-1);
        }else{
            int l,r;cin>>l>>r;
            cout<<sol.query(l-1,r-1)+1<<'\n';
        }
    }
    return 0;
}
