#include"testlib.h"
#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
int main(int argc,char*argv[]){
    registerTestlibCmd(argc,argv);
    const auto n=inf.readInt(),m=inf.readInt();
    const auto a=inf.readInts(n,0);
    const auto x=inf.readLongs(n,0);
    const auto b=inf.readInts(m,0);
    const auto y=inf.readLongs(m,0);
    auto ans=0ll;
    cir(al,0,n) cir(ar,al-1,n) cir(bl,0,m) cir(br,bl-1,m){
        unordered_set<int> cnt;
        cir(i,al,ar+1) cnt.emplace(a[i]);
        cir(i,bl,br+1) cnt.emplace(b[i]);
        if((int)(cnt.size())!=((ar-al+1)+(br-bl+1))) continue;
        auto ansi=0ll;
        cir(i,al,ar+1) ansi+=x[i];
        cir(i,bl,br+1) ansi+=y[i];
        ans=max(ans,ansi);
    }
    const auto usr=ouf.readLong();
    if(usr<ans) quitf(_wa,"Your answer is wrong [1]. Expected %lld, found %lld.\n",ans,usr);
    auto al=ouf.readInt(0,n);
    auto ar=ouf.readInt(al,n);
    auto bl=ouf.readInt(0,m);
    auto br=ouf.readInt(bl,m);
    if((!al)&&ar) quitf(_wa,"wrong format.\n");
    if((!bl)&&br) quitf(_wa,"wrong format.\n");
    unordered_set<int> cnt;
    if(!al) --ar;
    if(!bl) --br;
    --al;--ar;--bl;--br;
    cir(i,al,ar+1) cnt.emplace(a[i]);
    cir(i,bl,br+1) cnt.emplace(b[i]);
    if((int)(cnt.size())!=((ar-al+1)+(br-bl+1))) quitf(_wa,"wrong range.\n");
    auto ansi=0ll;
    cir(i,al,ar+1) ansi+=x[i];
    cir(i,bl,br+1) ansi+=y[i];
    if(ansi!=usr) quitf(_wa,"Your answer is wrong [2].\n");
    if(ansi>ans) quitf(_fail,"!!! :(\n");
    quitf(_ok,"accepted.\n");
}
