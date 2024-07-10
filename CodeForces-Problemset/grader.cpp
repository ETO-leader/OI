#include"testlib.h"
#include<bits/stdc++.h>

#if not defined(__GRADER_CPP)

#define __GRADER_CPP 1

#if defined FILE_LOG
    std::ofstream Info("grader.log");
#else
    #define Info std::clog
#endif

extern void Coins();

std::string col;

static constexpr auto LIMIT=7;

int cntq=0;

extern std::vector<bool> Relation(std::vector<std::pair<int,int>> x){
    ++cntq;
    const int n=x.size();
    std::vector<bool> res(n);
    for(auto c=-1;auto&[a,b]:x){
        --a;--b;
        Info<<"Relation ask:"<<a<<' '<<b<<": Result="<<(col[a]==col[b])<<'\n';
        res[++c]=(col[a]==col[b]);
    }
    return res;
}

extern void Answer(std::vector<int> a,std::vector<int> b,std::vector<int> c){
    if(a.size()+b.size()+c.size()!=col.size()){
        quitf(_wa,"length error.\n");
    }
    std::set<int> ax,bx,cx;
    for(auto&i:a) ax.insert(col[i-1]);
    for(auto&i:b) bx.insert(col[i-1]);
    for(auto&i:c) cx.insert(col[i-1]);
    if(ax.size()>1) quitf(_wa,"wrong answer.\n");
    if(bx.size()>1) quitf(_wa,"wrong answer.\n");
    if(cx.size()>1) quitf(_wa,"wrong answer.\n");
}

extern int CoinCount(){
    return col.size();
}

int main(int argc,char*argv[]){
    // std::ios::sync_with_stdio(false),std::cin.tie(0);
    registerTestlibCmd(argc,argv);
    int T=inf.readInt();
    inf.readEoln();
    std::cerr<<T<<'\n';
    while(T--){
        col=inf.readString();cntq=0;
        std::cerr<<T<<' '<<col<<'\n';
        Coins();
        if(cntq>LIMIT) quitf(_wa,"Too lot queries.\n");
    }
    quitf(_ok,"accepted.\n");
    return 0;
}

#endif