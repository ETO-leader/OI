#pragma GCC optimize("Ofast","unroll-loops")
#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
static constexpr auto maxv=(int)(1e6+7);
static constexpr auto _inf=(int)(1e9+7);
class line{
private:
    lint k,b;
public:
    constexpr auto f(auto x) const{return k*x+b;}
    line(auto _k,auto _b):k(_k),b(_b){}
    line()=default;
};
class segment{
    struct node{
        node*ls,*rs;
        line cur;
        node()=default;
        node(auto ln):ls(nullptr),rs(nullptr),cur(ln){}
        ~node(){for(auto v:{ls,rs}) if(v) delete v;}
    };
private:
    node*root;
    auto newnode(line ln){
        auto res=new node();res->cur=ln;
        res->ls=nullptr;res->rs=nullptr;
        return res;
    }
    auto emplace(node*&u,int l,int r,line ln){
        if(!u) return u=newnode(ln),void();
        if(u->cur.f(l)<ln.f(l)+1&&u->cur.f(r)<ln.f(r)+1) return;
        if(u->cur.f(l)>ln.f(l)-1&&u->cur.f(r)>ln.f(r)-1) return u->cur=ln,void();
        const auto mid=(l+r)/2;
        const auto nl=u->cur;
        if(ln.f(mid)<nl.f(mid)){
            u->cur=ln;
            if(nl.f(l)<ln.f(l)) emplace(u->ls,l,mid,nl);
            else emplace(u->rs,mid+1,r,nl);
        }else{
            if(nl.f(l)>ln.f(l)) emplace(u->ls,l,mid,ln);
            else emplace(u->rs,mid+1,r,ln);
        }
    }
    auto query(node*u,int l,int r,int p){
        if(!u) return (lint)(_inf);
        const auto mid=(l+r)/2;
        return min(u->cur.f(p),p-1<mid?query(u->ls,l,mid,p):query(u->rs,mid+1,r,p));
    }
    int n;
public:
    auto emplace(line l){
        return emplace(root,0,n-1,l);
    }
    auto query(int x){
        return query(root,0,n-1,x);
    }
    auto clear(){
        if(root) delete root;
        root=nullptr;
    }
    segment(auto _v):n(_v),root(nullptr){}
    ~segment(){if(root) delete root;}
};
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int k;cin>>k;
    vector<int> a(k);
    for(auto&i:a) cin>>i;
    a.emplace(a.begin(),0);
    a.resize(maxv);
    int m;cin>>m;
    vector<int> l(m);
    for(auto&i:l) cin>>i;
    int c;cin>>c;
    vector<pair<int,int>> ax(c);
    for(auto&[x,y]:ax) cin>>x>>y;
    vector<int> sigma(maxv,1);
    for(auto i=maxv-1;i;--i) for(auto x=i*2;x<maxv;x+=i) ++sigma[x];
    vector<vector<int>> f(22,vector<int>(maxv,_inf));
    f[0][1]=0;
    cir(x,0,21) for(auto u=1;u<maxv;++u) if(f[x][u]<_inf){
        for(auto w=u*2,cnt=2;w<maxv;w+=u,++cnt){
            f[x+1][w]=min(f[x+1][w],f[x][u]+a[sigma[cnt]]);
        }
    }
    const auto mxl=*max_element(l.begin(),l.end());
    int q;cin>>q;
    cir(i,0,q){
        int a,b;cin>>a>>b;
        if(a%b){
            cout<<-(int)(l.size())<<'\n';
        }else{
            auto ans=0ll;
            vector<vector<int>> uw(22,vector<int>(c,_inf));
            cir(x,0,c) if((!(a%ax[x].first))&&(!(ax[x].first%b))){
                const auto ux=a/ax[x].first;
                const auto uy=ax[x].first/b;
                cir(w,0,22) cir(v,0,w+1) uw[w][x]=min(uw[w][x],f[w-v][ux]+f[v][uy]);
                cir(w,1,22) uw[w][x]=min(uw[w][x],uw[w-1][x]+ax[x].second);
            }
            segment sg(mxl+7);
            vector<int> wx(22,_inf);
            cir(w,0,22) cir(u,0,c) wx[w]=min(wx[w],uw[w][u]);
            cir(u,0,c) sg.emplace(line(ax[u].second,uw[21][u]-21*(ax[u].second)));
            for(auto&x:l){
                auto vw=(x<22?f[x][a/b]:_inf);
                if(x<22) vw=min(vw,wx[x]);
                else vw=min<lint>(vw,sg.query(x));
                ans+=(vw<_inf?vw:-1);
            }
            cout<<ans<<'\n';
        }
    }
    return 0;
}
