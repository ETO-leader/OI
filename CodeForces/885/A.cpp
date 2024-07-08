#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
struct point{
    int x,y;
    auto distance(const point&p) const{
        return abs(x-p.x)+abs(y-p.y);
    }
    point(int _x=0,int _y=0):x(_x),y(_y){}
};
istream&operator>>(istream&is,point&p){
    return is>>p.x>>p.y;
}
auto slv(int x,int y,int k){
    bool res=false;
    const point vika(x,y);
    cir(i,0,k){
        point p;cin>>p;
        res|=(!(vika.distance(p)&1));
    }
    return res;
}
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int T;cin>>T;
    while(T--){
        int n,m,k,x,y;cin>>n>>m>>k>>x>>y;
        cout<<(slv(x,y,k)?"NO\n":"YES\n");
    }
    return 0;
}
