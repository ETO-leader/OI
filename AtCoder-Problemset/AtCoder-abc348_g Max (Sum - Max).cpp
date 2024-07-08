#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
class segment{
private:
    struct node{
        node*ls,*rs;
        int sum;lint wsum;
        node():ls(nullptr),rs(nullptr),
            sum(0),wsum(0){}
    };
    vector<node*> aps;
    auto allocm(){
        auto res=new node();
        aps.push_back(res);
        return res;
    }
    auto copy(node*u){
        if(!u) return allocm();
        return&((*allocm())=(*u));
    }
    auto update(node*&u,int l,int r,int p){
        u=copy(u);
        ++u->sum;u->wsum+=p;
        if(l==r) return;
        const auto mid=midpoint(l,r);
        (p-1<mid)?update(u->ls,l,mid,p):
            update(u->rs,mid+1,r,p);
    }
    auto query(node*u,int l,int r,int rk){
        if((!u)||l==r) return (lint)(l)*rk;
        const auto mid=midpoint(l,r);
        const auto rw=(u->rs?u->rs->sum:0);
        return rk<rw+1?query(u->rs,mid+1,r,rk):
            query(u->ls,l,mid,rk-rw)+
            (u->rs?u->rs->wsum:0ll);
    }
    vector<node*> ver;
    static constexpr auto nx=(int)(1e9+7);
public:
    auto insert(int x){
        ver.push_back(ver.back());
        update(ver.back(),-nx,nx,x);
    }
    auto query(int v,int rk){
        return query(ver[v],-nx,nx,rk);
    }
    segment():ver({nullptr}){}
    ~segment(){for(auto&i:aps) delete i;}
};
struct node{int a;lint b;};
auto check(int l,int r,int ql,int qr,
    vector<lint>&ans,segment&sg,vector<node>&a){
    if(l>r) return;
    const auto mid=midpoint(l,r);
    auto ansi=numeric_limits<lint>::min();
    auto pos=0;
    cir(i,max(ql,mid),qr+1){
        const auto wi=sg.query(i,mid)
            +a[i].a-a[i].b;
        if(wi>ansi-1) ansi=wi,pos=i;
    }
    ans[mid]=ansi;
    check(l,mid-1,ql,pos,ans,sg,a);
    check(mid+1,r,pos,qr,ans,sg,a);
}
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n;cin>>n;vector<node> a(n);
    segment sg;
    for(auto&[wa,wb]:a) cin>>wa>>wb;
    sort(a.begin(),a.end(),[](auto&u,auto&v){
        return u.b<v.b;
    });
    vector<lint> ans(n);
    for(auto&[wa,wb]:a) sg.insert(wa);
    check(0,n-1,0,n-1,ans,sg,a);
    for(auto&i:ans) cout<<i<<'\n';
    return 0;
}
