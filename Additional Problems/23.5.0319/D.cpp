#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=(a);i<(b);++i)
using namespace std;
using db=long double;
struct point{
    db x,y;
    point(db _x=0,db _y=0):x(_x),y(_y){}
    db operator()(const point&p) const{
        return sqrt((x-p.x)*(x-p.x)+(y-p.y)*(y-p.y));
    }
};
const db _inf=1e18+7;
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n,m;cin>>n>>m;vector<point> plc;
    ++n;plc.push_back(point(0,0));
    cir(i,0,n+m-1){
        db x,y;cin>>x>>y;
        plc.push_back(point(x,y));
    }
    const int _sz=1<<(n+m);
    vector<vector<db>> D(n+m,vector<db>(_sz,_inf));
    D[0][1]=0;
    auto add_count=[&n,&m](int s){
        int cnx=0;
        cir(i,n,n+m) cnx+=!!(s&(1<<i));
        return (db)(1<<cnx);
    };
    cir(s,1,_sz) cir(i,0,n+m) if(s&(1<<i)){
        cir(j,0,n+m) if(s&(1<<j)&&(j!=i))
            D[i][s]=min(D[i][s],D[j][s-(1<<i)]+
                plc[i](plc[j])/add_count(s-(1<<i)));
    }
    db ans=_inf;
    const int full=(1<<n)-1;
    cir(s,0,1<<m) cir(i,0,n+m) if(i&(full+(s<<n)))
        ans=min(ans,D[i][full+(s<<n)]+
            plc[i](plc[0])/add_count(full+(s<<n)));
    cout<<fixed<<setprecision(15)<<ans<<'\n';
    return 0;
}
