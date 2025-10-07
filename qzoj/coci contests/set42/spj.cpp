#include"testlib.h"
#include<bits/stdc++.h>
#define cir(i,a,b) for(auto i=a;i<b;++i)
using namespace std;
auto operator*(complex<double> a,auto b){
    return complex<double>(a.real()*b,a.imag()*b);
}
auto operator/(complex<double> a,auto b){
    return complex<double>(a.real()/b,a.imag()/b);
}
int main(int argc,char*argv[]){
    registerTestlibCmd(argc,argv);
    const auto n=inf.readInt(1,400);
    vector<complex<double>> a;
    cir(i,0,n){
        const auto u=inf.readInt(-10,10);
        const auto v=inf.readInt(-10,10);
        a.emplace_back(u,v);
    }
    int c=ouf.readInt(-1,2500);
    if(c<0) quitf(_ok,"probability no solution.\n");
    cir(i,0,c){
        const auto u=ouf.readInt(1,n)-1;
        const auto v=ouf.readInt(1,n)-1;
        const auto w=ouf.readInt(1,n)-1;
        vector<int> ps{u,v,w};
        sort(ps.begin(),ps.end());
        for(auto&x:ps) clog<<a[x]<<' ';
        clog<<"--> ";
        a[w]=a[w]+(((a[u]+a[v])/2)-a[w])*2;
        for(auto&x:ps) clog<<a[x]<<' ';
        clog<<'\n';
    }
    for(auto&u:a){
        if(u.real()<0||u.imag()<0) quitf(_wa,"wrong answer: point (%.3lf, %.3lf) is invalid.\n",u.real(),u.imag());
    }
    // for(auto&u:a) clog<<u<<' ';
    // clog<<'\n';
    quitf(_ok,"correct answer, T = %d.\n",c);
}

