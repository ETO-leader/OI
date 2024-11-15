#include"testlib.h"
#include<bits/stdc++.h>

#if not defined(__GRADER_CPP)

#define __GRADER_CPP 1

#if defined FILE_LOG
    std::ofstream Info("grader.log");
#else
    #define Info std::clog
#endif

using std::cin;

static char*_InitArgv[]={"headfile","inf","ouf","ouf"};

class interaction{
private:
    using lint=long long;
    lint n,a,b,c;
    bool quited;
    int qcount;
public:
    auto casenum(){
        auto T=inf.readInt();quited=false;
        return T;
    }
    auto typescount(){
        n=inf.readLong();
        a=inf.readLong();
        b=inf.readLong();
        c=inf.readLong();
        qcount=0;
        return n;
    }
    auto ask(auto l,auto r){
        if(l>r||r>n) quited=true,quitf(_wa,"invaild query.\n");
        auto res=0ll;++qcount;
        // cerr<<"ask: "<<l<<' '<<r<<" real: "<<a<<' '<<b<<' '<<c<<'\n';
        for(auto x:{a,b,c}) if(l-1<x&&x-1<r) res^=x;
        return res;
    }
    auto answer(auto _a,auto _b,auto _c){
        if(max({_a,_b,_c})>n) quited=true,quitf(_wa,"invaild answer.\n");
        if(min({_a,_b,_c})<1) quited=true,quitf(_wa,"invaild answer.\n");
        if(set{a,b,c}!=set{_a,_b,_c}) quited=true,quitf(_wa,"wrong answer.\n");
        if(qcount>150) quited=true,quitf(_wa,"too many queries (%d).\n",qcount);
        cerr<<"Query Count = "<<qcount<<'\n';
    }
    interaction(){
        registerTestlibCmd(4,_InitArgv);
    }
    ~interaction(){
        if(!quited) quitf(_ok,"accepted.\n");
    }
} interactor;

#endif