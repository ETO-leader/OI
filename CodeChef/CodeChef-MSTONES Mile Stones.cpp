#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using db=long double;
static constexpr db eps=1e-10L;
static constexpr int rnds=512;
mt19937 rnd(time(NULL));
struct point{db x,y;};
struct line{
    db a,b,c;
    bool online(point p) const{
        return fabs(a*p.x+b*p.y+c)<eps;
    }
    line(point ax,point bx){
        if(fabs(ax.x-bx.x)<eps){
            a=1;b=0;c=-ax.x;
        }else{
            a=(ax.y-bx.y)/(ax.x-bx.x);
            c=ax.y-a*ax.x;b=-1;
        }
    }
};
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int T;cin>>T;
    while(T--){
        int n;cin>>n;
        vector<point> ps(n);
        for(auto&[x,y]:ps) cin>>x>>y;
        int ans=(n+6)/7;
        cir(i,0,rnds){
            int a=rnd()%n,b=rnd()%n,ansi=0;
            if(a==b) continue;
            const line l(ps[a],ps[b]);
            for(auto&i:ps) ansi+=l.online(i);
            ans=max(ans,ansi);
        }
        cout<<ans<<'\n';
    }
    return 0;
}
