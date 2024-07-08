#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
const int maxa=2e6+7;
struct query{int l,r,id;};
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n,q,k;cin>>n>>q>>k;
    const int blcsiz=sqrt(n)+1;
    vector<int> v(n),cnx(maxa);
    vector<lint> ans(q);
    for(auto&i:v) cin>>i;
    v.insert(v.begin(),0);
    cir(i,1,n+1) v[i]^=v[i-1];
    vector<query> qx(q);
    [&](int cnx=0){
        for(auto&[l,r,id]:qx){
            cin>>l>>r;id=cnx++;--l;
        }
    }();
    sort(qx.begin(),qx.end(),[&](query&a,query&b){
        return a.l/blcsiz==b.l/blcsiz?
            a.r<b.r:a.l<b.l;});
    lint ansi=0;
    auto chgans=[&](int p,int w){
        if(k||(w<0)) cnx[v[p]]+=w;
        ansi+=w*(cnx[v[p]^k]);
        if((!k)&&(w>0)) cnx[v[p]]+=w;
    };
    int lx=0,rx=-1;
    for(auto&[l,r,id]:qx){
        while(rx<r) chgans(++rx,1);
        while(lx<l) chgans(lx++,-1);
        while(rx>r) chgans(rx--,-1);
        while(lx>l) chgans(--lx,1);
        ans[id]=ansi;
    }
    for(auto&i:ans) cout<<i<<'\n';
    return 0;
}
