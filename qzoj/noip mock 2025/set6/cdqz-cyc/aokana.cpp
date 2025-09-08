#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
ifstream inf("aokana.in");
ofstream ouf("aokana.out");
static constexpr auto _inf=(int)(1e9+7);
static constexpr auto maxv=(int)(1e9+7);
class segment{
private:
    struct node{
        int ls,rs,cov;
        node():ls(0),rs(0),cov(_inf){}
    };
    vector<node> tr;
    int cnt;
    auto update(int&u,int l,int r,int ql,int qr,int w){
        if(!u) u=++cnt,tr[u]=node();
        if(ql-1<l&&r-1<qr) return tr[u].cov=w,void();
        const auto mid=(l+r)/2;
        if(ql-1<mid) update(tr[u].ls,l,mid,ql,qr,w);
        if(mid<qr) update(tr[u].rs,mid+1,r,ql,qr,w);
    }
    auto query(int u,int l,int r,int p){
        if(!u) return _inf;
        if(l==r) return tr[u].cov;
        const auto mid=(l+r)/2;
        return min(
            tr[u].cov,
            p-1<mid?query(tr[u].ls,l,mid,p):query(tr[u].rs,mid+1,r,p)
        );
    }
    const int n;
    int root;
public:
    auto update(int l,int r,int w){
        update(root,0,n-1,l,r,w);
    }
    auto query(int p){
        return query(root,0,n-1,p);
    }
    segment(int _n,int c):n(_n),root(0),tr(c<<5),cnt(0){}
};
int main(){
    ios::sync_with_stdio(false),inf.tie(nullptr);
    int n,m;inf>>n>>m;
    vector<tuple<int,int,int>> a(n);
    for(auto&[l,r,w]:a) inf>>l>>r>>w;
    vector<int> f(n);
    segment sg(maxv,n);
    for(auto i=n-1;~i;--i){
        const auto[l,r,w]=a[i];
        f[i]=w;
        const auto nw=sg.query(w);
        if(nw<_inf) f[i]=f[nw];
        sg.update(l,r,i);
    }
    cir(i,0,m){
        int x;inf>>x;
        const auto nw=sg.query(x);
        if(nw<_inf) ouf<<f[nw]<<' ';
        else ouf<<x<<' ';
    }
    ouf<<'\n';
    return 0;
}
