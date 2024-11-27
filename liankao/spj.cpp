#include"testlib.h"
#include<vector>
#define cir(i,a,b) for(int i=a;i<b;++i)
using std::vector;

int main(int argc,char*argv[]){
    registerTestlibCmd(argc,argv);
    auto T=inf.readInt(1,100);
    while(T--) []{
        const auto l=inf.readLong(0,10000000000000000ll);
        const auto n=ouf.readInt(1,30);
        vector<vector<int>> a(n,vector<int>(n));
        for(auto&x:a) for(auto&i:x) i=ouf.readInt(0,1);
        if((!a[0][0])||(!a[n-1][n-1])) quitf(_wa,"not passable.\n");
        vector<vector<long long>> f(n,vector<long long>(n));
        f[0][0]=1;
        cir(i,0,n) cir(j,0,n) if(a[i][j]) f[i][j]+=(i?f[i-1][j]:0)+(j?f[i][j-1]:0);
        if(f[n-1][n-1]!=l) quitf(_wa,"your ways: %lld, jury's answer = %lld\n");
    }();
    quitf(_ok,"orz");
}

