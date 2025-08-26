#include"testlib.h"
#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;

int main(int argc,char*argv[]){
    registerTestlibCmd(argc,argv);
    auto n=inf.readInt(),m=inf.readInt();
    vector<vector<int>> a(n);
    for(auto&x:a) x=inf.readInts(m);
    auto isok=[&](int l,int r,int u,int d){
        auto ok=true;
        cir(nl,l,r+1) cir(nr,nl+1,r+1) cir(nu,u,d+1) cir(nd,nu+1,d+1){
            ok&=(a[nl][nu]+a[nr][nd])<(a[nl][nd]+a[nr][nu]+1);
        }
        return ok;
    };
    auto ans=0;
    cir(l,0,n) cir(r,l+1,n) cir(u,0,n) cir(d,u+1,n){
        if(isok(l,r,u,d)) ans=max(ans,(r-l+1)*(d-u+1));
    }
    const auto uans=ouf.readInt();
    if(ans!=uans) quitf(_wa,"Expected %d, found %d.\n",ans,uans);
    quitf(_ok,"Accepted.\n");
    return 0;
}

