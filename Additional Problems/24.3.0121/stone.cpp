#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
ifstream fcin("stone.in");
ofstream fcout("stone.out");
class fileio{
public:
    ~fileio(){
        fcin.close();fcout.close();
    }
} use_fileio;
template<class comp>
class seg_node{
private:
    struct node{
        node*ls,*rs;int mn;
        auto check(){
            if(!ls) ls=new node();
            if(!rs) rs=new node();
        }
        node():ls(nullptr),rs(nullptr),mn(max(
            -1,numeric_limits<int>::max()/2,comp())){}
        ~node(){if(ls) delete ls;if(rs) delete rs;}
    };
    auto maintain(node*u){
        u->mn=min(u->ls->mn,u->rs->mn,comp());
    }
    auto update(node*u,int l,int r,int p,int x){
        if(l==r) return u->mn=min(u->mn,x,comp()),void();
        u->check();
        const auto mid=(l+r)/2;
        (p<mid+1)?update(u->ls,l,mid,p,x):
            update(u->rs,mid+1,r,p,x);
        maintain(u);
    }
    auto query(node*u,int l,int r,int ql,int qr){
        if(ql-1<l&&r-1<qr) return u->mn;
        const auto mid=(l+r)/2;
        int res=max(-1,numeric_limits<int>::max()/2,comp());
        if(u->ls&&ql-1<mid)
            res=min(res,query(u->ls,l,mid,ql,qr),comp());
        if(u->rs&&mid<qr)
            res=min(res,query(u->rs,mid+1,r,ql,qr),comp());
        return res;
    }
    node*root;int n;
public:
    auto update(int p,int x){update(root,0,n-1,p,x);}
    auto query(int l,int r){return query(root,0,n-1,l,r);}
    seg_node(int _n):n(_n){root=new node();}
    ~seg_node(){delete root;}
};
template<class comp>
class segment{
private:
    vector<seg_node<comp>*> sgx;
    constexpr auto ls(int u){return u*2;}
    constexpr auto rs(int u){return u*2+1;}
    auto update(int u,int l,int r,int ql,int qr,int x,int w){
        if(ql-1<l&&r-1<qr) return sgx[u]->update(x,w);
        const auto mid=(l+r)/2;
        if(ql<mid+1) update(ls(u),l,mid,ql,qr,x,w);
        if(mid<qr) update(rs(u),mid+1,r,ql,qr,x,w);
    }
    auto query(int u,int l,int r,int p,int ql,int qr){
        auto res=sgx[u]->query(ql,qr);
        if(l==r) return res;
        const auto mid=(l+r)/2;
        return min(res,(p<mid+1)?query(ls(u),l,mid,p,ql,qr):
            query(rs(u),mid+1,r,p,ql,qr),comp());
    }
    auto init(int siz,int _n){
        cir(i,0,siz) sgx.push_back(new seg_node<comp>(_n));
    }
    int n;
public:
    auto update(int l,int r,int x,int w){
        update(1,0,n-1,l,r,x,w);
    }
    auto query(int p,int l,int r){
        return query(1,0,n-1,p,l,r);
    }
    segment(int _n):n(_n){init(_n<<2,_n);}
    ~segment(){for(auto&i:sgx) delete i;}
};
int main(){
    ios::sync_with_stdio(false),fcin.tie(0);
    int n;fcin>>n;vector<int> w(n),lx(n),rx(n);
    cir(i,0,n) fcin>>w[i]>>lx[i]>>rx[i];
    if(n<2007){
        vector<seg_node<less<int>>*> ax;
        vector<seg_node<greater<int>>*> bx;
        cir(i,0,n) ax.push_back(new seg_node<less<int>>(n+7));
        cir(i,0,n) bx.push_back(new seg_node<greater<int>>(n+7));
        cir(i,0,n){
            const int l=i+lx[i],r=i+rx[i];
            cir(p,l,min(r+1,n)){
                ax[p]->update(i,w[i]);
                bx[p]->update(i,w[i]);
            }
        }
        int q;fcin>>q;
        cir(i,0,q){
            int l,r;fcin>>l>>r;--l;--r;
            int ans=-1;
            cir(p,l,r+1){
                const auto lk=p-rx[p],rk=p-lx[p];
                if(rk<l) continue;
                ans=max({ans,
                    w[p]-ax[p]->query(max(lk,l),rk),
                    bx[p]->query(max(lk,l),rk)-w[p]});
            }
            fcout<<ans<<'\n';
        }
        for(auto&i:ax) delete i;
        for(auto&i:bx) delete i;
    }else{
        segment<less<int>> sga(n+7);
        segment<greater<int>> sgb(n+7);
        cir(i,0,n){
            const int l=i+lx[i],r=i+rx[i];
            sga.update(l,min(r+1,n),i,w[i]);
            sgb.update(l,min(r+1,n),i,w[i]);
        }
        int q;fcin>>q;
        cir(i,0,q){
            int l,r;fcin>>l>>r;--l;--r;
            int ans=-1;
            cir(p,l,r+1){
                const auto lk=p-rx[p],rk=p-lx[p];
                if(rk<l) continue;
                ans=max({ans,
                    w[p]-sga.query(p,max(lk,l),rk),
                    sgb.query(p,max(lk,l),rk)-w[p]});
            }
            fcout<<ans<<'\n';
        }
    }
    return 0;
}
