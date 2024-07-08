#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using db=long double;
db p2(db x){return x*x;}
db dis(db x,db y,db xx,db yy){
    return sqrtl(p2(x-xx)+p2(y-yy));
}
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    db xl1,yl1,xl2,yl2,xp1,yp1,v1,v2;
    cin>>xl1>>yl1>>xl2>>yl2>>xp1>>yp1>>v1>>v2;
    const db dist=dis(xl1,yl1,xl2,yl2);
    auto calc=[&](db disx){
        db as_time=disx/dist;
        return make_pair(xl1+(xl2-xl1)*as_time,yl1+(yl2-yl1)*as_time);
    };
    auto disx=[&](db mid){
        auto c=calc(mid);
        return mid/v1+dis(c.first,c.second,xp1,yp1)/v2;
    };
    db l=0,r=dist;
    cir(i,0,200){
        db lm=l+(r-l)/3,rm=l+(r-l)/3*2;
        disx(lm)<disx(rm)?r=rm:l=lm;
    }
    cout<<disx(l)<<endl;
    return 0;
}
