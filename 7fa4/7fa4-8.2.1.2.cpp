#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=__int128_t;
istream&operator>>(istream&is,lint&x){
    x=0;string s;is>>s;
    for(auto&i:s) (x*=10)+=(i-'0');
    return is;
}
ostream&operator<<(ostream&os,lint x){
    if(x<0) os<<'-',x=-x;
    if(x>9) os<<(x/10);
    return os<<(int)(x%10);
}
class calculator{
public:
    static constexpr auto fx(lint a,lint b,lint c,lint n){
        if(!n) return b/c;
        if(!a) return ((b/c)*(n+1));
        if(a>c-1||b>c-1){
            return fx(a%c,b%c,c,n)+(a/c)*n*(n+1)/2+(b/c)*(n+1);
        }
        const auto m=(a*n+b)/c;
        return n*m-fx(c,c-b-1,a,m-1);
    }
};
class segment{
private:
    struct node{
        node*ls,*rs;
        lint w,a,m,upt,sum;
        auto upd(lint _w,lint _a,lint _m,int len){
            w=_w;a=_a;m=_m;upt=true;
            sum=(_w*2+_a*(len-1))*len/2-calculator::fx(_a,_w,_m,len-1)*_m;
        }
        node():ls(nullptr),rs(nullptr),w(0),a(0),m(0),upt(false),sum(0){}
        ~node(){
            for(auto ch:{ls,rs}) if(ch) delete ch;
        }
    };
    node*root;
    auto push_down(node*u,int l,int r){
        if(!u->upt) return;
        const auto mid=(l+r)/2;
        const auto lenl=mid-l+1,lenr=r-mid;
        if(!u->ls) u->ls=new node();
        if(!u->rs) u->rs=new node();
        u->ls->upd(u->w,u->a,u->m,lenl);
        u->rs->upd(u->w+lenl*u->a,u->a,u->m,lenr);
        u->upt=false;
    }
    auto maintain(node*u){
        u->sum=u->ls->sum+u->rs->sum;
    }
    auto update(node*&u,int l,int r,int ql,int qr,lint w,lint a,lint m){
        if(!u) u=new node();
        if(r<ql||qr<l) return;
        if(ql-1<l&&r-1<qr) return u->upd(w,a,m,r-l+1);
        push_down(u,l,r);
        const auto mid=(l+r)/2;
        const auto rw=w+max<lint>((mid-max(ql,l)+1)*a,0);
        update(u->ls,l,mid,ql,qr,w,a,m);
        update(u->rs,mid+1,r,ql,qr,rw,a,m);
        maintain(u);
    }
    auto query(node*u,int l,int r,int ql,int qr){
        if((!u)||r<ql||qr<l) return (lint)(0);
        if(ql-1<l&&r-1<qr) return u->sum;
        push_down(u,l,r);
        const auto mid=(l+r)/2;
        return query(u->ls,l,mid,ql,qr)+query(u->rs,mid+1,r,ql,qr);
    }
    int n;
public:
    auto update(int l,int r,lint w,lint a,lint m){
        update(root,0,n-1,l,r,w,a,m);
    }
    auto query(int l,int r){
        return query(root,0,n-1,l,r);
    }
    segment(int _n):n(_n),root(nullptr){}
    ~segment(){if(root) delete root;}
};
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n,q;cin>>n>>q;segment sg(n+7);
    cir(i,0,q){
        int op;cin>>op;
        if(op==1){
            int l,r,a,b;cin>>l>>r>>a>>b;
            sg.update(l,r,a,a,b);
        }else{
            int l,r;cin>>l>>r;
            cout<<sg.query(l,r)<<'\n';
        }
    }
    return 0;
}
