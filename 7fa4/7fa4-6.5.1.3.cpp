#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
struct line{
    lint k,b;
    auto operator()(const lint x) const{
        return k*x+b;
    }
    line():k(0),b(0){}
    line(lint _k,lint _b):k(_k),b(_b){}
};
class segment{
private:
    struct node{
        node*ls,*rs;line f;
        node():ls(nullptr),rs(nullptr){}
        ~node(){
            if(ls) delete ls;
            if(rs) delete rs;
        }
    };
    auto insert(node*&u,int l,int r,line f){
        if(!u) return u=new node(),u->f=f,void();
        if(f(l)<u->f(l)&&f(r)<u->f(r)) return;
        if(u->f(l)<f(l)&&u->f(r)<f(r)){
            u->f=f;return;
        }
        const auto mid=(l+r)/2;
        if(f(mid)<u->f(mid)){
            if(u->f.k<f.k) insert(u->ls,l,mid,f);
            else insert(u->rs,mid+1,r,f);
        }else{
            auto lf=u->f;u->f=f;
            if(lf.k<f.k) insert(u->ls,l,mid,lf);
            else insert(u->rs,mid+1,r,f);
        }
    }
    auto query(node*u,int l,int r,int p){
        if(!u) return (lint)(0);
        const auto mid=(l+r)/2;
        return max(u->f(p),(p-1<mid)?
            query(u->ls,l,mid,p):query(u->rs,mid+1,r,p));
    }
    node*root;int n;
public:
    auto insert(line f){
        insert(root,0,n-1,f);
    }
    auto query(int p){
        return query(root,0,n-1,p);
    }
    segment(int _n):n(_n),root(nullptr){}
    ~segment(){if(root) delete root;}
};
struct arm{lint a,d;};
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    lint n,attack;cin>>n>>attack;
    vector<arm> emy;
    cir(i,0,n){
        lint a,d;cin>>a>>d;
        emy.push_back({a,(d+attack-1)/attack});
    }
    sort(emy.begin(),emy.end(),[](arm&a,arm&b){
        return a.d*b.a<b.d*a.a;
    });
    vector<lint> prex,sufx(n);
    lint bfans=0,pre=0;
    for(auto&[a,d]:emy)
        bfans+=a*((prex.push_back((pre+=d)-1),pre)-1);
    for(int i=n-1;~i;--i)
        sufx[i]=(i==n-1?(lint)(0):sufx[i+1])+emy[i].a;
    vector<lint> vx(n);
    cir(i,0,n) vx[i]=prex[i]*emy[i].a;
    cir(i,0,n) vx[i]+=(i+1<n?sufx[i+1]:(lint)(0))*emy[i].d;
    segment sg(n);
    lint ans=0;
    cir(i,0,n){
        ans=max(ans,vx[i]+sg.query(emy[i].a));
        sg.insert(line(-emy[i].d,vx[i]));
    }
    cout<<bfans-ans<<'\n';
    return 0;
}
