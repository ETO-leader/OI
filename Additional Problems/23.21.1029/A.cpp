#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using db=long double;
static constexpr db eps=1e-5;
static const db deg45=acos(-1)/4;
struct point{db x,y;};
void rotate(point&p,db deg){
    auto lstp=p;
    p.x=lstp.x*cos(deg)-lstp.y*sin(deg);
    p.y=lstp.x*sin(deg)+lstp.y*cos(deg);
}
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n;cin>>n;vector<point> ps(n);
    for(auto&[x,y]:ps) cin>>x>>y;
    for(auto&i:ps) rotate(i,deg45);
    sort(ps.begin(),ps.end(),[](point&a,point&b){
        return abs(a.x-b.x)<eps?a.y>b.y:a.x<b.x;
    });
    db nwmax=-1e18;int ans=0;
    for(auto&[x,y]:ps) if(y-eps>nwmax){
        nwmax=y;++ans;
    }
    cout<<ans<<'\n';
    return 0;
}
