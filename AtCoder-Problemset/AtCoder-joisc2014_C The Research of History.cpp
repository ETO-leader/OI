#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
struct query{int l,r,id;};
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n,q;cin>>n>>q;vector<int> v(n);
    const int sqr=sqrt(n)+1;
    for(auto&i:v) cin>>i;
    vector<vector<query>> qry(n/sqr+1);
    cir(i,0,q){
        int l,r;cin>>l>>r;--l,--r;
        qry[l/sqr].push_back({l,r,i});
    }
    for(auto&i:qry) sort(i.begin(),i.end(),
        [](query&a,query&b){return a.r<b.r;});
    vector<lint> ans(q);int cnx=0;
    for(auto&i:qry){
        unordered_map<int,lint> cx;
        const int rblock=(++cnx)*sqr-1;
        lint ansi=0;int rx=rblock;
        auto insert=[&](int p,auto&ax){
            cx[v[p]]++;
            ax=max(ax,cx[v[p]]*v[p]);
        };
        for(auto&[l,r,id]:i){
            if(r/sqr==l/sqr){
                cir(i,l,r+1) insert(i,ansi);
                ans[id]=ansi;
                cir(i,l,r+1) cx[v[i]]=0;
                ansi=0;
            }else{
                while(rx<r) insert(++rx,ansi);
                lint ansx=ansi;int lx=rblock+1;
                while(lx>l) insert(--lx,ansx);
                ans[id]=ansx;
                cir(i,l,rblock+1) cx[v[i]]--;
            }
        }
    }
    for(auto&i:ans) cout<<i<<'\n';
    return 0;
}
