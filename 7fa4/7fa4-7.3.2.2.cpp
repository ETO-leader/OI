#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
using db=double;
using VF=vector<db>;
const int _inf=1e9+7;
const db _inf_f=1e15+7;
struct edge{int len,v;lint w;bool deled;};
vector<vector<edge>> T,G;
void to_binary(int u,int f=0){
    vector<edge> sl;
    for(auto&[l,v,w,d]:G[u]) if(v!=f){
        to_binary(v,u),sl.push_back({l,v,w,false});
    }
    int ndid=u;
    while(sl.size()>2){
        auto bk=sl.back();
        T[ndid].push_back({1,bk.v,bk.w,bk.deled});
        T[bk.v].push_back({1,ndid,bk.w,bk.deled});
        T[ndid].push_back({0,(int)(T.size()),0LL,false});
        T.push_back(vector<edge>(0));
        T.back().push_back({0,ndid,0LL,false});
        sl.pop_back();ndid=T.size()-1;
    }
    if(!sl.empty()){
        auto b=sl.back();
        T[ndid].push_back(b);
        T[b.v].push_back({b.len,ndid,b.w,b.deled});
    }
    if(!sl.empty()) sl.pop_back();
    if(!sl.empty()){
        auto b=sl.back();
        T[ndid].push_back(b);
        T[b.v].push_back({b.len,ndid,b.w,b.deled});
    }
}
int dfssz(int u,int f=0){
    int res=1;
    for(auto&[l,v,w,d]:T[u]) if(v!=f&&(!d))
        res+=dfssz(v,u);
    return res;
}
struct edge_t{int len,u,v;lint w;};
lint findegde(int u,int sz,edge_t&e,int&w,int f=0){
    lint res=1;
    for(auto&[l,v,wi,d]:T[u]) if(v!=f&&(!d)){
        lint esz=findegde(v,sz,e,w,u);
        if(w>max(esz,sz-esz)){
            w=max(esz,sz-esz);e={l,u,v,wi};    
        }
        res+=esz;
    }
    return res;
}
void gethw(int u,VF&mx,int l=0,lint w=0,int f=0){
    mx[l]=max<db>(mx[l],w);
    for(auto&[lx,v,wx,d]:T[u]) if(v!=f&&(!d)){
        gethw(v,mx,l+lx,w+wx,u);
    }
}
void filx(int u,int vx,bool p){
    for(auto&[l,v,w,d]:T[u]) if(v==vx) d=p;
}
struct qnode{int p;db w;};
void treebound(int u,int l,int r,lint&cnx,db&mid){
    int sz=dfssz(u);
    if(sz<=l||cnx) return;
    int w=_inf;edge_t e;
    findegde(u,sz,e,w);
    filx(e.u,e.v,true);filx(e.v,e.u,true);
    treebound(e.u,l,r,cnx,mid);
    if(cnx){
        filx(e.u,e.v,false);filx(e.v,e.u,false);
        return;
    }
    treebound(e.v,l,r,cnx,mid);
    if(cnx){
        filx(e.u,e.v,false);filx(e.v,e.u,false);
        return;
    }
    VF m1(sz+1,-_inf_f),m2(sz+1,-_inf_f);
    gethw(e.u,m1);gethw(e.v,m2);
    cir(i,0,m1.size()) m1[i]-=i*mid;
    cir(i,0,m2.size()) m2[i]-=i*mid;
    deque<qnode> dq;
    l-=e.len;r-=e.len;
    for(int i=min(r,sz);i>l-1&&(~i);--i){
        while((!dq.empty())&&dq.back().w<=m2[i])
            dq.pop_back();
        dq.push_back({i,m2[i]});
    }
    cir(i,0,m1.size()){
        if(i<=l){
            while((!dq.empty())&&dq.back().w<m2[l-i])
                dq.pop_back();
            dq.push_back({l-i,m2[l-i]});
        }
        while((!dq.empty())&&dq.front().p+i>r)
            dq.pop_front();
        if(dq.empty()) continue;
        cnx+=(dq.front().w+m1[i]+e.w-e.len*mid)>=0;
    }
    filx(e.u,e.v,false);filx(e.v,e.u,false);
}
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n,lx,rx;cin>>n>>lx>>rx;
    G.resize(n+1);T.resize(n+1);
    lint mx=0;
    cir(i,0,n-1){
        int u,v;lint w;cin>>u>>v>>w;
        G[u].push_back({1,v,w,false});
        G[v].push_back({1,u,w,false});
        mx=max(mx,w);
    }
    to_binary(1);
    db l=0,r=mx,ans=0;
    cir(i,0,40){
        auto mid=(l+r)/2;lint cnx=0;
        treebound(1,lx,rx,cnx,mid);
        cnx?((l=mid),(ans=mid)):(r=mid);
    }
    cout<<fixed<<setprecision(3)<<ans<<'\n';
    return 0;
}
