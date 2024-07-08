#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
struct query{int l,r,id;};
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n;cin>>n;vector<int> v(n);
    const int sqr=sqrt(n)+1;
    unordered_map<int,int> um;
    for(auto&i:v) cin>>i,um[i]=-1;
    [&](int c=0){for(auto&[a,b]:um) b=c++;}();
    for(auto&i:v) i=um[i];
    int q;cin>>q;
    vector<vector<query>> qry((n/sqr)+1);
    cir(i,0,q){
        int l,r;cin>>l>>r;--l,--r;
        qry[l/sqr].push_back({l,r,i});
    }
    for(auto&i:qry) sort(i.begin(),i.end(),
        [](query&a,query&b){return a.r<b.r;});
    vector<int> ans(q);int cnx=0;
    for(auto&i:qry){
        vector<int> lf(um.size()),nw(um.size());
        const int rblock=(++cnx)*sqr-1;
        int rx=rblock,ansi=0;
        auto insert=[&](int p){
            nw[v[p]]=p+1;
            if(!lf[v[p]]) lf[v[p]]=p+1;
            ansi=max(ansi,p+1-lf[v[p]]);
        };
        for(auto&[l,r,id]:i){
            //In the same block
            if(r/sqr==l/sqr){
                vector<int> vx;
                cir(i,l,r+1){
                    if(!lf[v[i]]) lf[v[i]]=i+1;
                    ansi=max(ansi,i+1-lf[v[i]]);
                    vx.push_back(v[i]);
                }
                for(auto&i:vx) lf[i]=false;
                ans[id]=ansi;ansi=0;
            //Not same block
            }else{
                while(rx<r) insert(++rx);
                int ansx=ansi,lx=rblock+1;
                vector<int> vx;
                while(lx>l) [&](int p){
                    if(nw[v[p]])
                        ansx=max(ansx,nw[v[p]]-p-1);
                    else nw[v[p]]=p+1,vx.push_back(v[p]);
                }(--lx);
                for(auto&i:vx) nw[i]=false;
                ans[id]=ansx;
            }
        }
    }
    for(auto&i:ans) cout<<i<<'\n';
    return 0;
}
