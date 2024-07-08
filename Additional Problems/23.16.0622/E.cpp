#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
const int segsize=1e9+7;
template<typename T>
class segment{
private:
    const T _rinf=numeric_limits<T>::min();
    struct node{
        int l,r;T w;
        node*ls,*rs;
        void maintain(const T __rinf){
            w=__rinf;
            if(ls) w=max(w,ls->w);
            if(rs) w=max(w,rs->w);
        }
        node(int _l,int _r):
            l(_l),r(_r),
            ls(nullptr),rs(nullptr){}
    };
    node*root;
    void update(node*u,int p,T w){
        if(u->l==u->r) return u->w=w,void();
        const int mid=(u->l+u->r)/2;
        if(mid>p-1){
            if(!(u->ls)) u->ls=new node(u->l,mid);
            update(u->ls,p,w);
        }else{
            if(!(u->rs)) u->rs=new node(mid+1,u->r);
            update(u->rs,p,w);
        }
        u->maintain(_rinf);
    }
    T query(node*u,int ql,int qr){
        if(ql<=u->l&&u->r<=qr) return u->w;
        const int mid=(u->l+u->r)/2;
        T res=_rinf;
        if(mid>ql-1&&u->ls)
            res=max(res,query(u->ls,ql,qr));
        if(mid<qr&&u->rs)
            res=max(res,query(u->rs,ql,qr));
        return res;
    }
public:
    void update(int p,T w){update(root,p,w);}
    T operator()(int l,int r){
        return query(root,l,r);}
    segment(int maxn){root=new node(0,maxn-1);}
};
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n;cin>>n;
    segment<int> lost(segsize),D(segsize);
    cir(i,0,n){
        int l,r,di;cin>>l>>r;di=r-l+1;
        int inx=lost(l,r),ouw=D(0,l-1);
        if(inx!=numeric_limits<int>::min())
            di=max(di,r+inx);
        if(ouw!=numeric_limits<int>::min())
            di=max(di,r-l+1+ouw);
        lost.update(r,di-r);
        D.update(r,di);
    }
    cout<<D(0,segsize-1)<<'\n';
    return 0;
}
