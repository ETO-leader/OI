#pragma GCC optimize(3)
#pragma GCC target("avx")
#pragma GCC optimize("Ofast")
#pragma GCC optimize("inline")
#pragma GCC optimize("-fgcse")
#pragma GCC optimize("-fgcse-lm")
#pragma GCC optimize("-fipa-sra")
#pragma GCC optimize("-ftree-pre")
#pragma GCC optimize("-ftree-vrp")
#pragma GCC optimize("-fpeephole2")
#pragma GCC optimize("-ffast-math")
#pragma GCC optimize("-fsched-spec")
#pragma GCC optimize("unroll-loops")
#pragma GCC optimize("-falign-jumps")
#pragma GCC optimize("-falign-loops")
#pragma GCC optimize("-falign-labels")
#pragma GCC optimize("-fdevirtualize")
#pragma GCC optimize("-fcaller-saves")
#pragma GCC optimize("-fcrossjumping")
#pragma GCC optimize("-fthread-jumps")
#pragma GCC optimize("-funroll-loops")
#pragma GCC optimize("-fwhole-program")
#pragma GCC optimize("-freorder-blocks")
#pragma GCC optimize("-fschedule-insns")
#pragma GCC optimize("inline-functions")
#pragma GCC optimize("-ftree-tail-merge")
#pragma GCC optimize("-fschedule-insns2")
#pragma GCC optimize("-fstrict-aliasing")
#pragma GCC optimize("-fstrict-overflow")
#pragma GCC optimize("-falign-functions")
#pragma GCC optimize("-fcse-skip-blocks")
#pragma GCC optimize("-fcse-follow-jumps")
#pragma GCC optimize("-fsched-interblock")
#pragma GCC optimize("-fpartial-inlining")
#pragma GCC optimize("no-stack-protector")
#pragma GCC optimize("-freorder-functions")
#pragma GCC optimize("-findirect-inlining")
#pragma GCC optimize("-fhoist-adjacent-loads")
#pragma GCC optimize("-frerun-cse-after-loop")
#pragma GCC optimize("inline-small-functions")
#pragma GCC optimize("-finline-small-functions")
#pragma GCC optimize("-ftree-switch-conversion")
#pragma GCC optimize("-foptimize-sibling-calls")
#pragma GCC optimize("-fexpensive-optimizations")
#pragma GCC optimize("-funsafe-loop-optimizations")
#pragma GCC optimize("inline-functions-called-once")
#pragma GCC optimize("-fdelete-null-pointer-checks")
#include<bits/stdc++.h>
#include<bits/extc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace __gnu_pbds;
using namespace std;
template<typename _Ty,class comp=less<_Ty>>
using rbt=tree<_Ty,null_type,comp,rb_tree_tag,
    tree_order_statistics_node_update>;
static constexpr size_t maxsiz=2e5+7;
template<size_t maxmem>
class bst{
private:
    struct node{
        node*ls,*rs;
        unsigned w,rk;rbt<int,less_equal<int>> tr;
        auto maintain(){
            rk=ls->rk+rs->rk+1;
        }
        node():ls(nullptr),rs(nullptr),w(0),rk(0){}
    };
    static constexpr auto alpha=0.74f;
    array<node,maxmem> mem;
    node*null,*root;unsigned cnt;
    auto clear(node*u){
        u->tr.clear();u->tr.insert(u->w);
        u->rk=1;u->ls=null;u->rs=null;
    }
    auto allocm(){return&mem[++cnt];}
    auto newnode(unsigned _w){
        auto res=allocm();res->ls=res->rs=null;
        res->w=_w;res->rk=1;res->tr.insert(_w);
        return res;
    }
    vector<node*> nds;
    auto destroy(node*u){
        if(u==null) return;
        const auto lsu=u->ls,rsu=u->rs;
        destroy(lsu);
        nds.push_back((clear(u),u));
        destroy(rsu);
    }
    auto maintain(node*u){
        u->maintain();
        for(const auto&i:u->ls->tr) u->tr.insert(i);
        for(const auto&i:u->rs->tr) u->tr.insert(i);
    }
    auto rebuild(size_t l,size_t r){
        if(r<l) return null;
        if(l==r) return nds[l];
        const auto mid=(l+r)/2;
        auto res=nds[mid];
        if(mid) res->ls=rebuild(l,mid-1);
        res->rs=rebuild(mid+1,r);
        maintain(res);
        return res;
    }
    auto check(node*u){
        const auto sizx=u->rk*alpha;
        return u->ls->rk>sizx||u->rs->rk>sizx;
    }
    auto rebuild(node*u){
        nds.clear();destroy(u);
        return rebuild(0,nds.size()-1);
    }
    auto insert(node*&u,int k,unsigned w,bool checked=false){
        if(u==null) return u=newnode(w);
        if((!checked)&&check(u)){
            checked=true;u=rebuild(u);
        }
        u->tr.insert(w);
        auto res=(u->ls->rk<k?
            insert(u->rs,k-u->ls->rk-1,w,checked):
            insert(u->ls,k,w,checked));
        u->maintain();
        return res;
    }
    auto update(node*u,int k,int fr,unsigned nw){
        if(u==null) return;
        u->tr.erase(u->tr.lower_bound(fr-1));
        u->tr.insert(nw);
        if(u->ls->rk+1==k) return u->w=nw,void();
        u->ls->rk<k?update(u->rs,k-u->ls->rk-1,fr,nw):
            update(u->ls,k,fr,nw);
    }
    auto order_of_key(node*u,int k,unsigned w){
        if(u==null||k<0) return (size_t)(0);
        if(u->rk<k+1) return u->tr.order_of_key(w);
        auto res=(u->w<w)*(u->ls->rk<k);
        return res+order_of_key(u->ls,k,w)+
            order_of_key(u->rs,k-u->ls->rk-1,w);
    }
    auto rnks(unsigned l,unsigned r,unsigned w){
        return order_of_key(root,r,w)-
            order_of_key(root,l-1,w);
    }
    unsigned numeric_min,numeric_max;
    vector<unsigned> arr;
public:
    using iterator=node*;
    auto find_by_order(unsigned ql,unsigned qr,unsigned k){
        auto l=numeric_min,r=numeric_max,ans=0u;
        while(l<r+1){
            const auto mid=(l+r)/2;
            rnks(ql,qr,mid)+1>k?
                ((r=mid-1),(ans=mid)):(l=mid+1);
        }
        return ans-1;
    }
    auto insert(unsigned k,unsigned w){
        arr.insert(arr.begin()+k,w);
        return insert(root,k,w);
    }
    auto update(unsigned k,unsigned w){
        update(root,k,arr[k-1],w);
        arr[k-1]=w;
    }
    bst(int _numeric_min=numeric_limits<unsigned>::min()/2,
        int _numeric_max=numeric_limits<unsigned>::max()/2):
        numeric_min(_numeric_min),numeric_max(_numeric_max){
        arr.reserve(100000);
        cnt=0;null=&mem[0];root=null;
    }
};
namespace flash_man{
static char buf[5000000], *p1 = buf, *p2 = buf, obuf[5000000], *p3 = obuf;
struct Quick_IO_Suf { ~Quick_IO_Suf() { fwrite(obuf, p3 - obuf, 1, stdout); } } quick_io_suf;
#define getchar() p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, 5000000, stdin), p1 == p2) ? EOF : *p1++
#define putchar(x) (p3 - obuf < 5000000) ? (*p3 ++= x) : (fwrite(obuf, p3 - obuf, 1, stdout), p3 = obuf, *p3 ++= x)
namespace Quick_IO {
static char cc[20];
template <typename type> void read(type &x) {
	x = 0;
	char c = getchar();
	while (c < '0' || c > '9') {
		c = getchar();
	}
	while (c >= '0' && c <= '9') {
		x = x * 10 + (c ^ 48);
		c = getchar();
	}
}
template <typename type> inline void write(type x, char c) {
	if (x == 0) putchar(48);
	int len = 0;
	while (x) {
		cc[len++] = x % 10 + '0';
		x /= 10;
	}
	while (len--) putchar(cc[len]);
	putchar(c);
}
}
using namespace Quick_IO;
}
using namespace flash_man;
int main(){
    //ios::sync_with_stdio(false),cin.tie(0);
    int n;read(n);bst<maxsiz> tr(0,70007);
    cir(i,0,n){
        int x;read(x);tr.insert(i,x);
    }
    int q;read(q);int lastans=0;
    cir(i,0,q){
        string op(1,' ');
        while(!isalpha(op[0])) op[0]=getchar();
        if(op[0]=='Q'){
            unsigned l,r,k;read(l);read(r);read(k);
            l^=lastans;r^=lastans;k^=lastans;
            write((lastans=tr.find_by_order(l,r,k)),'\n');
        }else if(op[0]=='M'){
            unsigned x,k;read(x);read(k);
            x^=lastans;k^=lastans;tr.update(x,k);
        }else{
            unsigned x,k;read(x);read(k);
            x^=lastans;k^=lastans;tr.insert(x-1,k);
        }
    }
    return 0;
}
