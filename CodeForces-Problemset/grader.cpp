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
    lint a,b,c;
    int qcount;
public:
    static auto casenum(){
        auto T=inf.readInt();
        return T;
    }
    auto typescount(){
        auto n=inf.readLong();
        a=inf.readLong();
        b=inf.readLong();
        c=inf.readLong();
        qcount=0;
        return n;
    }
    auto ask(auto l,auto r){
        auto res=0ll;++qcount;
        for(auto x:{a,b,c}) if(l-1<x&&x-1<r) res+=x;
        return res;
    }
    auto answer(auto _a,auto _b,auto _c){
        if(set{a,b,c}!=set{_a,_b,_c}) quitf(_wa,"wrong answer.\n");
        if(qcount>150) quitf(_wa,"too many queries.\n");
    }
    interaction(){
        registerTestlibCmd(4,_InitArgv);
    }
    ~interaction(){
        quitf(_ok,"accepted.\n");
    }
} interactor;

#endif