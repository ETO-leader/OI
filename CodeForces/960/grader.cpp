#include"testlib.h"
#include<iostream>
#include<fstream>
#include<vector>

class check{
private:
    template<typename _Ty>
    using vector=std::vector<_Ty>;
    vector<vector<int>> gr;
    vector<int> dfn,rdfn,fx;
    int cnt;
    auto dfs(int u,int h=0,int f=1)->void{
        dfn[u]=++cnt;fx[u]=f;
        for(auto&i:gr[u]) if(i!=f) dfs(i,h+1,u);
        rdfn[u]=cnt;
    }
public:
    auto insert(int u,int v){
        gr[u].push_back(v);
        gr[v].push_back(u);
    }
    auto init(){dfs(1);}
    auto isancestor(int u,int v){
        return dfn[u]<dfn[v]+1&&rdfn[v]<rdfn[u]+1;
    }
    auto move(int&u){u=fx[u];}
    check(int n):gr(n+1),dfn(n+1),rdfn(n+1),fx(n+1),cnt(0){}
    check()=default;
};

int pos,count;
check chk;
bool passed;

extern int checkml(int u){
    std::cerr<<std::format("call checkml function, node={}",u)<<'\n';
    ++count;
    if(chk.isancestor(u,pos)) return true;
    chk.move(pos);
    return false;
}

extern void answer(int u){
    if(u!=pos) quitf(_wa,"wrong answer.\n");
    passed=true;
}

extern std::vector<std::pair<int,int>> init(){
    int n=inf.readInt();pos=inf.readInt();passed=false;
    std::vector<std::pair<int,int>> es(n-1);
    for(auto&[a,b]:es) a=inf.readInt(),b=inf.readInt();
    chk=check(n);
    for(auto&[u,v]:es) chk.insert(u,v);
    chk.init();count=0;
    return es;
}

void findit();

int main(int argc,char*argv[]){
    registerTestlibCmd(argc,argv);
    int T=inf.readInt();
    int Limit=inf.readInt();
    while(T--){
        findit();
        if(count>Limit) quitf(_wa,"too many queries.\n");
        if(!passed) quitf(_wa,"why don't you call the `answer` function?\n");
    }
    quitf(_ok,"accepted.\n");
}
