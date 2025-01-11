#include"testlib.h"
#include<bits/stdc++.h>
using namespace std;

static const int _AND = 0;
static const int _OR = 1;
static const int _XOR = 2;
static const int _NOT = 3;

vector<string> op;

auto fmt(vector<int> x){
    string res;
    for(auto&i:x) res+=format("{} ",i);
    return res;
}

auto compute(int H,int W,int _x1,int _y1,int _x2,int _y2){
    auto pos=[&](auto x,auto y){
        return x*W+y;
    };
    vector<int> Storage(1000000);
    Storage[pos(_x1,_y1)]=1;
    Storage[pos(_x2,_y2)]=1;
    auto cnt=H*W;
    for(auto&L:op){
        stringstream str(L);
        int x,k;str>>x>>k;
        vector<int> q(k);
        auto w=-1;
        for(auto&w:q) str>>w;
        if(x==_AND){
            auto x=1;
            vector<int> qw;
            for(auto&i:q) x&=Storage[i],qw.emplace_back(Storage[i]);
            Storage[cnt]=x;
            cerr<<"AND: "<<fmt(qw)<<": RESULT = "<<Storage[cnt]<<'\n';
        }else if(x==_OR){
            auto x=0;
            vector<int> qw;
            for(auto&i:q) x|=Storage[i],qw.emplace_back(Storage[i]);
            Storage[cnt]=x;
            cerr<<"OR: "<<fmt(qw)<<": RESULT = "<<Storage[cnt]<<'\n';
        }else if(x==_XOR){
            auto x=0;
            vector<int> qw;
            for(auto&i:q) x^=Storage[i],qw.emplace_back(Storage[i]);
            Storage[cnt]=x;
            cerr<<"XOR: "<<fmt(qw)<<": RESULT = "<<Storage[cnt]<<'\n';
        }else{
            vector<int> qw{Storage[q[0]]};
            Storage[cnt]=!Storage[q[0]];
            cerr<<"NOT: "<<fmt(qw)<<": RESULT = "<<Storage[cnt]<<'\n';
        }
        ++cnt;
    }
    return Storage[cnt-1];
}

int main(int argc,char*argv[]){
    registerTestlibCmd(argc,argv);
    auto H=inf.readInt();
    auto W=inf.readInt();
    auto K=inf.readInt();
    ouf.readLine();
    const auto str=ouf.readLine();
    int x;stringstream __sstream(str);
    __sstream>>x;
    for(auto i=0;i<x;++i){
        op.emplace_back(ouf.readLine());
    }
    int c;
    auto cnt=0;
    while(true){
        ++cnt;
        c=inf.readInt();
        if(c==-1) break;
        const auto _x1=c,_y1=inf.readInt(),_x2=inf.readInt(),_y2=inf.readInt();
        const auto _result=(abs(_x1-_x2)+abs(_y1-_y2))==K;
        const auto _u_result=compute(H,W,_x1,_y1,_x2,_y2);
        if(_result!=_u_result) quitf(_wa,"Expect %d, found %d. [Case: %d]\n",(int)(_result),(int)(_u_result),cnt);
    }
    quitf(_ok,"accepted.\n");
}
