#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
//线段树要修改为区间操作
class segment{
private:
    struct node{
        int mn,arg;lint x,argx;
    };
    constexpr auto ls(int x){return x*2;}
    constexpr auto rs(int x){return x*2+1;}
    vector<node> tr;
    auto maintain(int u){
        if(tr[ls(u)].mn<tr[rs(u)].mn)
            tr[u].x=tr[ls(u)].x;
        else if(tr[ls(u)].mn>tr[rs(u)].mn)
            tr[u].x=tr[rs(u)].x;
        else tr[u].x=tr[ls(u)].x+tr[rs(u)].x;
        tr[u].mn=min(tr[ls(u)].mn,tr[rs(u)].mn);
    }
    auto update(int u,int l,int r,int ql,int qr,int arg,auto f){
        if(l==r) return f(u,arg);
        const auto mid=(l+r)/2;
        if(ql-1<mid) update(ls(u),l,mid,ql,qr,arg,f);
        if(mid<qr) update(rs(u),mid+1,r,ql,qr,arg,f);
        maintain(u);
    }
    int n;
public:
    function<void(int,int)> feature=[&](int u,int x){
        tr[u].mn+=x;
    };
    function<void(int,int)> Σsum=[&](int u,int x){
        tr[u].x+=x;
    };
    auto update(int l,int r,int arg,auto f){
        return update(1,1,n,l,r,arg,f);
    }
    auto Δ(){return tr[1];}
    segment(int _n):tr(_n<<2){}
};
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n,m;cin>>n>>m;map<int,int> pos;
    vector<pair<int,int>> es(n-1);
    for(auto&[u,v]:es) cin>>u>>v;
    cir(i,0,n){
        int x;cin>>x;pos[x]=i;
    }
    vector<int> a(n+1);
    cir(i,1,n+1) a[i]=pos[i];
    segment sgs(n);
    auto insedge=[&](int u,int v){
        //All black
        sgs.update(0,min(a[u],a[v])-1,1,sgs.feature);
        //One Node White
        sgs.update(min(a[u],a[v]),max(a[u],a[v])-1,1,sgs.Σsum);
    };
    auto deledge=[&](int u,int v){
        //All black
        sgs.update(0,min(a[u],a[v])-1,-1,sgs.feature);
        //One Node White
        sgs.update(min(a[u],a[v]),max(a[u],a[v])-1,-1,sgs.Σsum);
    };
    for(auto&[u,v]:es) insedge(u,v);
    cout<<sgs.Δ().x<<'\n';
    cir(i,0,m){
        int u,v,x,y;cin>>u>>v>>x>>y;
        deledge(u,v);insedge(x,y);
        cout<<sgs.Δ().x<<'\n';
    }
    return 0;
}
