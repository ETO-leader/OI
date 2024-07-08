#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
static constexpr auto maxw=(1<<14)-1;
struct qry{int l,r,id;};
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n,m,k;cin>>n>>m>>k;
    const auto sqr=(int)(ceil(n/sqrt(m)));
    vector<int> a(n);
    for(auto&i:a) cin>>i;
    vector<qry> qx(m);
    for(auto c=0;auto&[l,r,id]:qx) cin>>l>>r,id=c++;
    sort(qx.begin(),qx.end(),[&](qry&a,qry&b){
        return a.l/sqr==b.l/sqr?a.r<b.r:a.l<b.l;
    });
    vector<int> ux;
    cir(i,0,maxw+1) if(__builtin_popcount(i)==k)
        ux.push_back(i);
    vector<unordered_map<int,int>> qw(n);
    // Init
    [&](){
        auto l=0,r=-1;
        auto ins=[&](int p){
            if(l) qw[l-1].insert({a[p],0});
            qw[r].insert({a[p],0});
        };
        auto rmv=[&](int p){
            if(l) qw[l-1].insert({a[p],0});
            qw[r].insert({a[p],0});
        };
        for(auto&[ql,qr,id]:qx){
            while(r<qr) ins(++r);
            while(l>ql) ins(--l);
            while(r>qr) rmv(r--);
            while(l<ql) rmv(l--);
        }
    }();
    [&](){
        vector<int> cw(maxw+1);
        cir(i,0,n){
            if(!k) for(auto&[x,y]:qw[i]) y=cw[x]; 
            for(auto&w:ux) ++cw[a[i]^w];
            if(k) for(auto&[x,y]:qw[i]) y=cw[x];
        }
    }();
    vector<lint> ans(m);
    [&](){
        auto l=0,r=-1;auto ansi=0ll;
        auto ins=[&](int p){
            
        };
        auto rmv=[&](int p){

        };
        for(auto&[ql,qr,id]:qx){
            while(r<qr) ins(++r);
            while(l>ql) ins(--l);
            while(r>qr) rmv(r--);
            while(l<ql) rmv(l--);
        }
    }();
    return 0;
}
