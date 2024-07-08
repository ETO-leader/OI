#pragma GCC optimize("Ofast")
#pragma GCC target("avx,avx2,sse,sse2,sse3,ssse3,sse4,mmx")
#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
constexpr int _inf=1e9+7;
static const int cks=114;
mt19937 rnd(time(NULL));
int rndrng(int l,int r){
    return l+(rnd()%(r-l+1));
}
struct qry{int l,r,k,id;};
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n,q;cin>>n>>q;vector<int> a(n);
    for(auto&i:a) cin>>i;
    vector<qry> qs(q);
    [&](){
        int c=0;
        for(auto&[l,r,k,id]:qs){
            cin>>l>>r>>k,id=c++;
            --l;--r;
        }
    }();
    const int sqr=sqrt(n)+1;
    sort(qs.begin(),qs.end(),[&](qry&a,qry&b){
        return a.l/sqr==b.l/sqr?a.r<b.r:a.l<b.l;
    });
    vector<int> cnx(n+1),ans(q,_inf);
    auto ins=[&](int p){++cnx[a[p]];};
    auto del=[&](int p){--cnx[a[p]];};
    int lx=0,rx=-1;
    for(auto&[l,r,k,id]:qs){
        const int usi=(r-l+1)/k;
        while(rx<r) ins(++rx);
        while(lx<l) del(lx++);
        while(rx>r) del(rx--);
        while(lx>l) ins(--lx);
        cir(i,0,cks){
            const int p=rndrng(l,r);
            if(cnx[a[p]]>usi){
                ans[id]=min(ans[id],a[p]);
            }
        }
    }
    for(auto&i:ans){
        cout<<(i==_inf?-1:i)<<'\n';
    }
    return 0;
}
