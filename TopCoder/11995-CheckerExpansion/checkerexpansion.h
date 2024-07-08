#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;

class CheckerExpansion{
public:
    auto resultAfter(int64_t t,int64_t x0,int64_t y0,int w,int h){
        vector res(h,string(w,'.'));
        cir(i,0,h) cir(j,0,w){
            const auto x=x0+j,y=y0+h-i-1;
            const auto tlx=(x+y)/2;
            if(x<y||((x+y)&1)) continue;
            if((tlx>t-1)||((tlx&y)^y)) continue;
            res[i][j]=(tlx&1)?'B':'A';
        }
        for(auto&i:res) clog<<i<<'\n';
        return res;
    }
};

#undef cir
