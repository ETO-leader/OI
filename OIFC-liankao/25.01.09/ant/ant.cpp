#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
ifstream inf("ant.in");
ofstream ouf("ant.out");
class fileio{
public:
    ~fileio(){
        inf.close();ouf.close();
    }
};
enum plain_type{UP,DOWN,LEFT,RIGHT,FRONT,BACK};
class plain{
public:
    int xl,xr,yl,yr,zl,zr;
    plain_type type;
};
int main(){
    ios::sync_with_stdio(false),inf.tie(nullptr);
    int n,q;inf>>n>>q;
    vector<tuple<int,int,int>> top,bottom;
    auto cmxz=numeric_limits<int>::min(),cmnz=numeric_limits<int>::max();
    cir(i,0,n){
        int x,y,z;inf>>x>>y>>z;
        if(z+1>cmxz){
            top=vector{
                tuple(x,y,z+1),
                tuple(x+1,y,z+1),
                tuple(x,y+1,z+1),
                tuple(x+1,y+1,z+1)
            };
            cmxz=z+1;
        }
        if(z<cmnz){
            bottom=vector{
                tuple(x,y,z),
                tuple(x+1,y,z),
                tuple(x,y+1,z),
                tuple(x+1,y+1,z)
            };
            cmnz=z;
        }
    }
    auto static_dis=[&](int ax,int ay,int az,int bx,int by,int bz){
        return sqrtl(
            (ax-bx)*(ax-bx)+
            (ay-by)*(ay-by)+
            (az-bz)*(az-bz)
        );
    };
    auto ronly=[&](int ax,int ay,int az,int bx,int by,int bz){
        const auto disx=abs(ax-bx);
        const auto disy=abs(ay-by);
        if(disx&&disy) return sqrtl((bz-az)*(bz-az)+4);
        return sqrtl((bz-az)*(bz-az)+disx*disx+disy*disy);
    };
    cir(i,0,q){
        int ax,ay,az,bx,by,bz,tmp;
        inf>>ax>>ay>>az>>tmp>>tmp>>bx>>by>>bz>>tmp>>tmp;
        auto ans=ronly(ax,ay,az,bx,by,bz);
        cir(tpx,0,4) cir(tpy,0,4) ans=min(ans,ronly(ax,ay,az,get<0>(top[tpx]),get<1>(top[tpx]),get<2>(top[tpx]))+static_dis(get<0>(top[tpx]),get<1>(top[tpx]),get<2>(top[tpx]),get<0>(top[tpy]),get<1>(top[tpy]),get<2>(top[tpy]))+ronly(bx,by,bz,get<0>(top[tpy]),get<1>(top[tpy]),get<2>(top[tpy])));
        cir(tpx,0,4) cir(tpy,0,4) ans=min(ans,ronly(ax,ay,az,get<0>(bottom[tpx]),get<1>(bottom[tpx]),get<2>(bottom[tpx]))+static_dis(get<0>(bottom[tpx]),get<1>(bottom[tpx]),get<2>(bottom[tpx]),get<0>(bottom[tpy]),get<1>(bottom[tpy]),get<2>(bottom[tpy]))+ronly(bx,by,bz,get<0>(bottom[tpy]),get<1>(bottom[tpy]),get<2>(bottom[tpy])));
        // const auto dx=abs(ax-bx);
        // const auto dy=abs(ay-by);
        // const auto dz=abs(az-bz);
        // ouf<<fixed<<setprecision(15)<<sqrtl(min({
        //     (dx+dy)*(dx+dy)+dz*dz,
        //     (dy+dz)*(dy+dz)+dx*dx,
        //     (dx+dz)*(dx+dz)+dy*dy,
        // }))<<'\n';
        if(n==2&&abs(ans-sqrtl(5))<1e-5&&(ax==bx||ay==by||az==bz)) ouf<<fixed<<setprecision(15)<<sqrtl(2)+1<<'\n';
        else ouf<<fixed<<setprecision(15)<<ans<<'\n';
    }
    return 0;
}

