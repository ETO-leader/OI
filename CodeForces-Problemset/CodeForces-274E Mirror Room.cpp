#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using point=pair<int,int>;
constexpr auto x(const point p){
    return p.first;
}
constexpr auto y(const point p){
    return p.second;
}
const vector<int> mx={-1,-1,1,1},my={1,-1,-1,1};
template<const bool isfndf>
auto getnxt(point&ux,int&dir,vector<set<point>>&u,
    vector<set<point>>&d,set<point>&ps,int&swp,const int m){
    auto fd=((dir&1)?d:u)[(dir&1)?
        x(ux)-y(ux)+m+1:x(ux)+y(ux)].lower_bound(ux);
    if(dir<2) fd=prev(fd);
    auto res=0ll;
    if(!isfndf) res+=abs(x(*fd)-x(ux));
    ux.first=x(*fd)-mx[dir];
    ux.second=y(*fd)-my[dir];
    const auto tpx=ps.count({x(ux),y(ux)
        +my[dir]})^ps.count({x(ux)+mx[dir],y(ux)});
    if(!tpx){
        swp=2;(dir+=2)%=4;
    }else if(ps.count({x(ux)+mx[dir],y(ux)})){
        ux.second+=my[dir];dir^=3;
    }else{
        ux.first+=mx[dir];dir^=1;
    }
    return res;
}
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n,m,k;cin>>n>>m>>k;
    vector<set<point>> u(n+m+7),d(n+m+7);
    set<point> ps;
    auto ins=[&](int x,int y){
        u[x+y].insert({x,y});
        d[x-y+m+1].insert({x,y});
        ps.insert({x,y});
    };
    cir(i,0,n+2) ins(i,0),ins(i,m+1);
    cir(i,0,m+2) ins(0,i),ins(n+1,i);
    cir(i,0,k){
        int x,y;cin>>x>>y;
        ins(x,y);
    }
    int sx,sy;string dirs;
    cin>>sx>>sy>>dirs;
    auto dir=[&](){
        unordered_map<string,int> r{{"NE",0},{"NW",1},{"SW",2},{"SE",3}};
        return r[dirs];
    }(),swp=1;
    point ux(sx,sy);
    getnxt<true>(ux,dir,u,d,ps,swp,m);
    const auto sdir=dir;
    sx=x(ux);sy=y(ux);
    auto ans=getnxt<false>(ux,dir,u,d,ps,swp,m);
    while(ux!=point(sx,sy)||dir!=sdir)
        ans+=getnxt<false>(ux,dir,u,d,ps,swp,m);
    cout<<(ans/swp)<<'\n';
    return 0;
}
