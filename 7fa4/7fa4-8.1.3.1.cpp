#include<bits/stdc++.h>
#include<bits/extc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace __gnu_pbds;
using namespace std;
template<typename _Ty,class comp=less<_Ty>>
using rbt=tree<_Ty,null_type,comp,rb_tree_tag,
    tree_order_statistics_node_update>;
static constexpr size_t maxsiz=5e5+7;
template<size_t maxmem>
class segment{
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
    segment(int _n):a(_n),n(_n),init(true){
        null=&mem[0];root=newnode();
    }
};
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n,q;cin>>n>>q;segment<maxsiz> sg(n);
    cir(i,0,n){
        int x;cin>>x;sg.update(i,x);
    }
    sg.inited();
    cir(i,0,q){
        int op;cin>>op;
        if(op==1){
            int l,r,k;cin>>l>>r>>k;--l;--r;
            cout<<sg.order_of_key(l,r,k)+1<<'\n';
        }else if(op==2){
            int l,r;size_t k;cin>>l>>r>>k;--l;--r;
            cout<<sg.find_by_order(l,r,k-1)<<'\n';
        }else if(op==3){
            int p,w;cin>>p>>w;--p;
            sg.update(p,w);
        }else if(op==4){
            int l,r,k;cin>>l>>r>>k;--l;--r;
            cout<<sg.getprefix(l,r,k)<<'\n';
        }else{
            int l,r,k;cin>>l>>r>>k;--l;--r;
            cout<<sg.getsuffix(l,r,k)<<'\n';
        }
    }
    return 0;
}
