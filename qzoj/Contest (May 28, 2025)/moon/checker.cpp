#include"testlib.h"
#include<set>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
int main(int argc,char*argv[]){
    registerTestlibCmd(argc,argv);
    const auto n=inf.readInt(),m=inf.readInt();
    set<int> cx,cy;
    vector<vector<int>> a(m);
    const auto d=inf.readInts(m,0);
    cir(i,0,m){
        a[i]=inf.readInts(d[i],0);
    }
    auto sgn=ouf.readInt();
    if(sgn==-1) quitf(_wa,"answer is always exist under given constraints.\n");
    const auto ncx=sgn,ncy=ouf.readInt();
    set<int> ap;
    cir(i,0,ncx){
        const auto u=ouf.readInt();
        if(ap.count(u)) quitf(_wa,"same element.\n");
        ap.emplace(u);
        for(auto&x:a[u-1]) cx.emplace(x);
    }
    cir(i,0,ncy){
        const auto u=ouf.readInt();
        if(ap.count(u)) quitf(_wa,"same element.\n");
        ap.emplace(u);
        for(auto&x:a[u-1]) cy.emplace(x);
    }
    for(auto&i:cx) clog<<i<<' ';
    clog<<'\n';
    for(auto&i:cy) clog<<i<<' ';
    clog<<'\n';
    if(cx!=cy) quitf(_wa,"set not same.\n");
    quitf(_ok,"accepted.\n");
    return 0;
}
