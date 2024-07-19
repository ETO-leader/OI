#include<bits/stdc++.h>

#if not defined(ONLINE_JUDGE)        // grader interactive

#include"grader.h"

#else                                // IO interactive

#if not defined(__GRADER_H)

#define __GRADER_H 1

extern int getHash(std::string s){
    std::cout<<std::format("? {}",s)<<'\n';
    std::cout.flush();
    int h;std::cin>>h;
    return h;
}

extern void answer(int p,int m){
    std::cout<<std::format("! {} {}",p,m)<<'\n';
    std::cout.flush();
}

extern void attack();

int main(){
    int T;std::cin>>T;
    while(T--) attack();
}

#endif

#endif

#define cir(i,a,b) for(int i=a;i<b;++i)

using namespace std;

static constexpr auto maxlen=50;

extern void attack(){
    const auto p=getHash("aa")-1;
    string str;
    cir(i,0,maxlen) str+='z';
    const auto qx=getHash(str);
    auto cur=__int128_t(1);
    cir(i,0,maxlen){
        cir(j,1,26) if(cur*j>qx){
            str[i]-=j;
            const auto qk=getHash(str);
            const auto m=qk+cur*j-qx;
            return answer(p,m);
        }
        cur*=p;
    }
    answer(p,-1);
}
