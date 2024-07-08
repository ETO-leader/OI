#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
struct point{double x,y;};
istream&operator>>(istream&is,point&p){
    return is>>p.x>>p.y;
}
// print a line like y=ax+by+c
inline void outline(double a,double b,double c){
    cout<<'?'<<' '<<a<<' '<<b<<' '<<c<<'\n';
    cout<<flush;
}
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int T;cin>>T;
    while(T--){
        int n;cin>>n;
        vector<double> pxi(n),pyi(n);
        outline(0,1,0);
        // x pos
        for(auto&i:pxi){
            point p;cin>>p;i=p.x;
        }
        // y pos
        outline(1,0,0);
        for(auto&i:pyi){
            point p;cin>>p;i=p.y;
        }
        // points on y=x
        sort(pxi.begin(),pxi.end());
        sort(pyi.begin(),pyi.end());
        outline(-0.001,1,0);
        vector<point> pxy(n);
        for(auto&i:pxy) cin>>i;
        sort(pxy.begin(),pxy.end(),
            [](point&a,point&b){return a.x<b.x;});
        cout<<'!'<<' ';
        cir(i,0,n){
            const double revk=-1000;
            const double lineb=pxy[i].y-pxy[i].x*revk;
            const double __y=revk*pxi[i]+lineb;
            double ansx=1e9,ans=0;
            cir(j,0,n){
                if(fabs(__y-pyi[j])<=ansx)
                    ansx=fabs(__y-pyi[j]),ans=pyi[j];
            }
            cout<<fixed<<' '<<setprecision(10)<<
                pxi[i]<<' '<<ans<<' ';
        }
        cout<<'\n'<<flush;
    }
    return 0;
}
