#include<bits/stdc++.h>
#pragma GCC optimize("Ofast")
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using VI=vector<int>;
using VS=vector<short>;
struct query{int l,r,c,id;};
struct state{bool _tag;short p;};
istream&operator>>(istream&is,query&q){
    is>>q.l>>q.r>>q.c;q.l--,q.r--;
    return is;
}
vector<vector<vector<state>>> fr;
void runx(int l,int r,int w,VI&ans){
    const int n=ans.size();
    if(r<l||l<0||r>=n) return;
    auto&[_,p]=fr[l][r][w];
    if(_) return runx(l,r,w-1,ans),void();
    ans[p]=w;
    runx(l,p-1,w,ans);runx(p+1,r,w,ans);
}
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n,m;cin>>n>>m;vector<query> vq(m);
    vector<vector<VI>> D(n,vector<VI>(n,VI(m)));
    vector<vector<VS>> cnx(n,vector<VS>(n,VS(m))),
        fcx(n,vector<VS>(n,VS(m)));
    fr.assign(n,vector<vector<state>>(
        n,vector<state>(m)));
    for(auto&i:vq) cin>>i;
    sort(vq.begin(),vq.end(),
        [](query&a,query&b){return a.c>b.c;});
    [&](){
        int cx=0;
        for(auto&[u,v,w,id]:vq) id=cx,cx++;
    }();
    VI val;
    for(auto&[l,r,w,id]:vq) val.push_back(w);
    cir(i,0,n) cir(j,i,n) for(auto&[l,r,w,id]:vq){
        if(i<=l&&r<=j) cnx[i][j][id]++;
    }
    cir(l,0,n) cir(i,0,n-l){
        const int j=i+l;
        cir(w,0,m){
            auto&d=D[i][j][w];
            if(w) cnx[i][j][w]+=cnx[i][j][w-1],d=D[i][j][w-1];
            fr[i][j][w]._tag=true;
            d=max(d,cnx[i][j][w]*val[w]);
            cir(p,i,j+1){
                int cnxi=cnx[i][j][w];
                if(p>i) cnxi-=cnx[i][p-1][w];
                if(p<j) cnxi-=cnx[p+1][j][w];
                cnxi*=val[w];
                if(p>i) cnxi+=D[i][p-1][w];
                if(p<j) cnxi+=D[p+1][j][w];
                if(cnxi>=d){
                    auto&f=fr[i][j][w];
                    f._tag=false;f.p=p;d=cnxi;
                }
            }
        }
    }
    VI ans(n);
    auto wx=[&](){
        int mx=0,res=0;
        cir(i,0,m){
            if(D[0][n-1][i]>mx) mx=D[0][n-1][i],res=i;
        }
        return res;
    }();
    cout<<*max_element(D[0][n-1].begin(),
        D[0][n-1].end())<<'\n';
    runx(0,n-1,wx,ans);
    for(auto&i:ans) cout<<val[i]<<' ';
    cout<<'\n';
    return 0;
}
