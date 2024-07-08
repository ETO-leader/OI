#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
struct query{int l,r,id;};
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n,q;string s;cin>>n>>q>>s;
    const int sqr=sqrt(n)+1;
    for(auto&i:s) i-='a';
    s.insert(s.begin(),-1);
    vector<int> xr(n+1);
    cir(i,1,n+1) xr[i]=xr[i-1]^(1<<s[i]);
    vector<query> qx(q);
    [&](int cnx=0){
        for(auto&[l,r,id]:qx){
            cin>>l>>r;--l;id=cnx++;
        }
        sort(qx.begin(),qx.end(),[&](query&a,query&b){
            return a.l/sqr==b.l/sqr?a.r<b.r:a.l<b.l;});
    }();
    lint ansi=0;
    vector<unsigned short> cnx(1<<26);
    auto insert=[&](int p){
        ansi+=cnx[xr[p]];cnx[xr[p]]++;
        ansi+=[&](){
            lint res=0;
            cir(i,0,26) res+=cnx[xr[p]^(1<<i)];
            return res;
        }();
    };
    auto erase=[&](int p){
        cnx[xr[p]]--;ansi-=cnx[xr[p]];
        ansi-=[&](){
            lint res=0;
            cir(i,0,26) res+=cnx[xr[p]^(1<<i)];
            return res;
        }();
    };
    vector<lint> ans(q);
    int lx=1,rx=0;
    for(auto&[l,r,id]:qx){
        while(rx<r) insert(++rx);
        while(lx<l) erase(lx++);
        while(rx>r) erase(rx--);
        while(lx>l) insert(--lx);
        ans[id]=ansi;
    }
    for(auto&i:ans) cout<<i<<'\n';
    return 0;
}
