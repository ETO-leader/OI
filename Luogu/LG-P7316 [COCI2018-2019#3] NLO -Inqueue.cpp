#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
class segment{
private:
    struct node{
        node*ls,*rs;lint val;
        auto create(){
            if(!ls) ls=new node();
            if(!rs) rs=new node();
        }
        node():ls(nullptr),rs(nullptr),val(0){}
        ~node(){
            if(ls) delete ls;
            if(rs) delete rs;
        }
    };
    node*root;
    auto push_down(node*u){
        if((u->ls)||(u->rs)) return;
        u->create();
        u->ls->val=u->val;
        u->rs->val=u->val;
        u->val=0;
    }
    auto update(node*u,int l,int r,int ql,int qr,lint x){
        if(ql-1<l&&r-1<qr){
            if(u->ls) delete u->ls;
            if(u->rs) delete u->rs;
            u->ls=nullptr;u->rs=nullptr;
            return u->val=x,void();
        }
        push_down(u);
        const auto mid=(l+r)/2;
        if(ql-1<mid) update(u->ls,l,mid,ql,qr,x);
        if(mid<qr) update(u->rs,mid+1,r,ql,qr,x);
    }
    auto calc(node*u,int l,int r) const{
        assert(u);
        if((!u->ls)&&(!u->rs)) return u->val*(r-l+1);
        const auto mid=(l+r)/2;
        return calc(u->ls,l,mid)+calc(u->rs,mid+1,r);
    }
    int n;
public:
    auto update(int l,int r,lint x){
        if(!root) root=new node();
        update(root,0,n-1,l,r,x);
    }
    auto calc(){
        if(!root) return (lint)(0);
        return calc(root,0,n-1);
    }
    segment(int _n):n(_n),root(nullptr){}
    ~segment(){delete root;}
};
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n,m,k;cin>>n>>m>>k;
    vector<segment> sgk(m,segment(n));
    cir(i,0,k){
        int x,y,r;cin>>x>>y>>r;--x;--y;
        cir(p,y-r,y+r+1){
            const auto d=abs(p-y);
            const auto lx=(int)(sqrtl(r*r-d*d));
            sgk[p].update(x-lx,x+lx,i+1);
        }
    }
    auto ans=1ll*n*m*k;
    for(auto&sg:sgk) ans-=sg.calc();
    cout<<ans<<'\n';
    return 0;
}