#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
//线段树:区间加，区间最值(min/max)
template<typename T=lint,class comp=less<T>
    ,const T _inf=(T)(1e18+7)>
class segment{
private:
    vector<T> tag,mx,v;
    void push_down(int u){
        auto ls=u*2,rs=u*2+1;
        mx[ls]+=tag[u];mx[rs]+=tag[u];
        tag[ls]+=tag[u];tag[rs]+=tag[u];
        tag[u]=0;
    }
    void push_up(int u){
        auto ls=u*2,rs=u*2+1;
        mx[u]=min(mx[ls],mx[rs],comp());
    }
    void build(int u,int l,int r){
        if(l==r){mx[u]=v[l];return;}
        int ls=u*2,rs=u*2+1,mid=(l+r)/2;
        build(ls,l,mid);build(rs,mid+1,r);
        push_up(u);
    }
    void update(int u,int l,int r,int ql,int qr,T v){
        if(ql<=l&&r<=qr){
            tag[u]+=v;mx[u]+=v;return;
        }
        push_down(u);
        auto ls=u*2,rs=u*2+1,mid=(l+r)/2;
        if(mid>=ql) update(ls,l,mid,ql,qr,v);
        if(qr>mid) update(rs,mid+1,r,ql,qr,v);
        push_up(u);
    }
    T quary(int u,int l,int r,int ql,int qr){
        if(ql<=l&&r<=qr) return mx[u];
        push_down(u);
        T res=min<T>(0,_inf,comp());
        auto ls=u*2,rs=u*2+1,mid=(l+r)/2;
        if(mid>=ql)
            res=min(res,quary(ls,l,mid,ql,qr),comp());
        if(qr>mid)
            res=min(res,quary(rs,mid+1,r,ql,qr),comp());
        push_up(u);
        return res;
    }
    int n;
public:
    segment(vector<T>&vx):n(vx.size()){
        v=vx;
        mx.resize(n*4);tag.resize(n*4);
        build(1,1,n-1);}
    void update(int l,int r,T v){
        if(l<=r) update(1,1,n,l,r,v);
    }
    T operator()(int l,int r){
        return quary(1,1,n,l,r);
    }
};
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n,k;cin>>n>>k;vector<lint> v(n+1);
    cir(i,1,n+1) cin>>v[i];
    vector<lint> vx(n+1);
    vector<segment<lint,greater<lint>,0>> segs(
        k+1,segment<lint,greater<lint>,0>(vx));
    vector<vector<lint>> D(
        n+1,vector<lint>(k+1));
    map<int,int> aps;
    lint ans=0;
    cir(i,1,n+1){
        int l=1;
        if(aps.count(v[i])) l=aps[v[i]];
        aps[v[i]]=i;
        D[i][1]=aps.size();
        segs[1].update(i,i,D[i][1]);
        ans=max<lint>(ans,aps.size());
        segs[1].update(l,i-1,1);
        cir(j,2,k+1){
            segs[j].update(l,i-1,1);
            D[i][j]=segs[j-1](1,i);
            segs[j].update(i,i,D[i][j]);
            ans=max(D[i][j],ans);
        }
    }
    cout<<ans<<'\n';
    return 0;
}
