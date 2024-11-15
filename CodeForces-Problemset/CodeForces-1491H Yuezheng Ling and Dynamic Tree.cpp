#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
class blocks{
public:
    vector<pair<int,int>> blx;
    vector<lint> a,updc,b,delta,bid;
    const int sqr;
    auto init(const auto n){
        blx.emplace_back(0,0);
        for(auto i=1;i<n;i+=sqr) blx.emplace_back(i,min(i+sqr,n)-1);
        for(auto c=-1;auto&[l,r]:blx){
            ++c;
            cir(i,l,r+1) bid[i]=c;
        }
    }
    auto ax(int u){
        return max<lint>(0,a[u]-delta[bid[u]]);
    }
    auto bx(int u){
        // if(delta[bid[u]]) assert(ax(u)<blx[bid[u]].first);
        return ax(u)<blx[bid[u]].first?ax(u):b[ax(u)];
    }
    auto updateblc(int bid,int x){
        if(updc[bid]>sqr) return delta[bid]+=x,void();
        updc[bid]+=x;
        const auto[l,r]=blx[bid];
        cir(i,l,r+1) a[i]=max<lint>(0,a[i]-x),b[i]=bx(i);
    }
    auto updatenode(int l,int r,int x){
        cir(i,l,r+1) a[i]=max<lint>(0,a[i]-x),b[i]=bx(i);
    }
    auto inita(auto ai){
        a=ai;
        cir(i,0,(int)(ai.size())){
            const auto[l,r]=blx[bid[i]];
            b[i]=bx(i);
        }
    }
public:
    auto update(int l,int r,int x){
        const auto bl=bid[l],br=bid[r];
        if(bl==br){
            updatenode(l,r,x);
            return updatenode(r+1,blx[br].second,0);
        }
        updatenode(blx[bl].first,l-1,0);
        updatenode(l,blx[bl].second,x);
        updatenode(blx[br].first,r,x);
        updatenode(r+1,blx[br].second,0);
        cir(i,bl+1,br) updateblc(i,x);
    }
    auto lca(int u,int v){
        while(u!=v){
            if(bx(u)==bx(v)){
                if(u>v) u=ax(u);
                else v=ax(v);
            }else{
                if(u>v) u=bx(u);
                else v=bx(v);
            }
        }
        return u;
    }
    blocks(int _n,auto ax):a(_n),updc(_n),b(_n),delta(_n),bid(_n),sqr(sqrt(_n)){
        init(_n);inita(vector<lint>(ax.begin(),ax.end()));
    }
};
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int n,q;cin>>n>>q;vector<int> a(n-1);
    for(auto&i:a) cin>>i,--i;
    a.insert(a.begin(),0);
    blocks bx(n,a);
    cir(i,0,q){
        int op;cin>>op;
        if(op==1){
            int l,r,x;cin>>l>>r>>x;--l;--r;
            bx.update(l,r,x);
        }else{
            int u,v;cin>>u>>v;--u;--v;
            println("{}",bx.lca(u,v)+1);
        }
    }
    return 0;
}
