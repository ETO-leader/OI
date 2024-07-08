#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
using VI=vector<lint>;
struct query{int l,r,id;};
auto specialpart(string&s,vector<query>&v,int k){
    VI res(v.size()),sum(s.size()),sx(s.size());
    cir(i,1,s.size()){
        sum[i]=sum[i-1]+(!(s[i]%k));
        sx[i]=sx[i-1]+(!(s[i]%k))*i;
    }
    for(auto&[l,r,id]:v){
        --r;
        res[id]=sx[r]-sx[l-1]-(sum[r]-sum[l-1])*(l-1);
    }
    return res;
}
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int p;string s;cin>>p>>s;
    const int n=s.size();
    const int sqr=sqrt(n)+1;
    for(auto&i:s) i-='0';
    s.insert(s.begin(),0);
    VI pre(s.size()+1);
    lint k10=1;
    for(int i=n;~i;--i) ((pre[i]=pre[i+1]+
        (lint)(s[i])*(k10%=p))%=p),(k10*=10);
    unordered_map<int,int> ck;
    cir(i,0,n+2) ck[pre[i]]=0;
    int c=0;for(auto&[a,b]:ck) b=c++;
    VI cnx(ck.size()),idx(n+2);
    cir(i,0,n+2) idx[i]=ck[pre[i]];
    int q;cin>>q;
    VI ans(q);lint ansi=0;
    vector<query> qx(q);
    [&](int cnx=0){
        for(auto&[l,r,id]:qx)
            (cin>>l>>r),(id=cnx++),(r++);
    }();
    sort(qx.begin(),qx.end(),[&](query&a,query&b){
        return a.l/sqr==b.l/sqr?a.r<b.r:a.l<b.l;
    });
    auto chgpos=[&](int px,int w){
        ansi-=cnx[idx[px]]*(cnx[idx[px]]-1)/2;
        cnx[idx[px]]+=w;
        ansi+=cnx[idx[px]]*(cnx[idx[px]]-1)/2;
    };
    int lx=1,rx=0,cnt=0;
    if(p==2||p==5){
        ans=specialpart(s,qx,p);
        goto prt;
    }
    for(auto&[l,r,id]:qx){
        while(rx<r) chgpos(++rx,1);
        while(lx<l) chgpos(lx++,-1);
        while(rx>r) chgpos(rx--,-1);
        while(lx>l) chgpos(--lx,1);
        ans[id]=ansi;++cnt;
    }
    prt:for(auto&i:ans) cout<<i<<'\n';
    return 0;
}
