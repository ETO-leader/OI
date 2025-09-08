#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
#ifndef ONLINE_JUDGE
ifstream inf("aokana.in");
ofstream ouf("aokana.out");
#else
auto&inf(cin);
auto&ouf(cout);
#endif
static constexpr auto _inf=(int)(1e9+7);
static constexpr auto maxv=(int)(1e9+7);
class segment{
private:
    vector<int> tr;
    constexpr auto ls(auto u) const{return u*2;}
    constexpr auto rs(auto u) const{return u*2+1;}
    auto update(int u,int l,int r,int ql,int qr,int w){
        if(ql-1<l&&r-1<qr) return tr[u]=w,void();
        const auto mid=(l+r)/2;
        if(ql-1<mid) update(ls(u),l,mid,ql,qr,w);
        if(mid<qr) update(rs(u),mid+1,r,ql,qr,w);
    }
    auto query(int u,int l,int r,int p){
        if(!u) return _inf;
        if(l==r) return tr[u];
        const auto mid=(l+r)/2;
        return min(
            tr[u],
            p-1<mid?query(ls(u),l,mid,p):query(rs(u),mid+1,r,p)
        );
    }
    const int n;
public:
    auto update(int l,int r,int w){
        update(1,0,n-1,l,r,w);
    }
    auto query(int p){
        return query(1,0,n-1,p);
    }
    segment(int _n):n(_n),tr(_n<<2,_inf){}
};
int main(){
    ios::sync_with_stdio(false),inf.tie(nullptr);
    int n,m;inf>>n>>m;
    vector<tuple<int,int,int>> a(n);
    vector<int> vals;
    for(auto&[l,r,w]:a) inf>>l>>r>>w,vals.emplace_back(w);
    vector<int> q(m);
    for(auto&x:q) inf>>x,vals.emplace_back(x);
    sort(vals.begin(),vals.end());
    vals.erase(unique(vals.begin(),vals.end()),vals.end());
    vector<int> f(n);
    segment sg(n*2);
    for(auto i=n-1;~i;--i){
        auto[l,r,w]=a[i];
        l=lower_bound(vals.begin(),vals.end(),l)-vals.begin();
        r=upper_bound(vals.begin(),vals.end(),r)-vals.begin()-1;
        w=lower_bound(vals.begin(),vals.end(),w)-vals.begin();
        f[i]=w;
        const auto nw=sg.query(w);
        if(nw<_inf) f[i]=f[nw];
        sg.update(l,r,i);
    }
    cir(i,0,m){
        auto x=q[i];
        x=lower_bound(vals.begin(),vals.end(),x)-vals.begin();
        const auto nw=sg.query(x);
        if(nw<_inf) ouf<<vals[f[nw]]<<' ';
        else ouf<<vals[x]<<' ';
    }
    ouf<<'\n';
    return 0;
}
