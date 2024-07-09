#include<bits/stdc++.h>
#if not defined(ONLINE_JUDGE)
    std::string Ask(int,int);
#endif
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;

#if not defined(__GRADER_H) && defined(ONLINE_JUDGE)

#define __GRADER_H 1

extern void findTreasure();

string Ask(int x,int y){
    cout<<x<<' '<<y<<'\n';
    cout.flush();
    string res;
    getline(cin,res);
    if(find(res.begin(),res.end(),'!')!=res.end()) exit(0);
    return res;
}

int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    findTreasure();
    return 0;
}

#endif

static constexpr auto maxrng=(int)(1e6);

auto ChkAsk(int x,int y){
    return Ask(min(max(x,0),maxrng),min(max(y,0),maxrng));
}

void findTreasure(){
    Ask(0,0);
    const auto strlf=ChkAsk(1,1);
    const auto strrg=ChkAsk(2,2);
    if(strlf!=strrg){
        cir(dxi,0,4) cir(dyi,0,4){
            ChkAsk(dxi,dyi);
        }
        abort();
    }
    const auto closer=strlf;
    auto xl=0,xr=maxrng,yl=0,yr=maxrng;
    cir(i,0,20){
        if(xl==xr&&yl==yr) break;
        const auto xmid=midpoint(xl,xr);
        const auto ymid=midpoint(yl,yr);
        ChkAsk(xmid,ymid);
        ChkAsk(xmid+1,ymid)==closer?xl=xmid+1:xr=xmid-1;
        ChkAsk(xmid+1,ymid+1)==closer?yl=ymid+1:yr=ymid-1;
    }
    ChkAsk(xl,yl);
    ChkAsk(xl,yl+1);
    ChkAsk(xl+1,yl);
    ChkAsk(xl+1,yl+1);
    abort();
}
