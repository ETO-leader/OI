#include<bits/stdc++.h>
#define cir(i,a,b) for(auto i=a;i<b;++i)
using namespace std;
ifstream inf("set.in");
ofstream ouf("set.out");
int main(){
    ios::sync_with_stdio(false),inf.tie(nullptr);
    int n;inf>>n;
    vector<int> vs;
    cir(s,0,(1<<n)) if(__builtin_popcount(s)==(n+1)/2) vs.emplace_back(s);
    const auto ans=(int)(vs.size());
    vector<vector<int>> vn(n);
    cir(i,0,ans){
        cir(p,0,n) if((vs[i]>>p)&1) vn[p].emplace_back(i);
    }
    ouf<<ans<<'\n';
    cir(i,0,n){
        ouf<<vn[i].size()<<' ';
        for(auto&x:vn[i]) ouf<<x+1<<' ';
        ouf<<'\n';
    }
    cir(i,0,ans){
        ouf<<(n+1)/2<<' ';
        cir(p,0,n) if((vs[i]>>p)&1) ouf<<p+1<<' ';
        ouf<<'\n';
    }
    return 0;
}

