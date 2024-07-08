#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using db=long double;
void prtqry(db x,db y){
    cout<<"? ";
    cout<<fixed<<setprecision(14)<<x<<' '<<y;
    cout<<flush;
}
db boundlu(db rx,db nx,bool tgl){
    db l=0,r=rx*2;
    cir(i,0,70){
        db mid=(l+r)/2;
        prtqry((tgl?mid:nx),(tgl?nx:mid));
        int rd;cin>>rd;
        rd?l=mid:r=mid;
    }
    return l;
}
db boundrd(db rx,db nx,bool tgr){
    db l=-rx*2,r=0;
    cir(i,0,70){
        db mid=(l+r)/2;
        prtqry((tgr?mid:nx),(tgr?nx:mid));
        int rd;cin>>rd;
        rd?r=mid:l=mid;
    }
    return l;
}
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    db r;cin>>r;
    db lx=boundlu(r,0,true);
    db rx=boundrd(r,0,true);
    db xcar=(lx+rx)/2;
    db hx=boundlu(r,xcar,false);
    cout<<"! ";
    cout<<fixed<<setprecision(14)
        <<xcar<<' '<<hx-r<<'\n';
    return 0;
}