#include"testlib.h"
#include<set>
int main(int argc,char*argv[]){
    registerValidation(argc,argv);
    auto n=inf.readInt(2,1000,"n");
    std::set<int> a;
    for(int i=0;i<n;++i){
        auto w=inf.readInt(1,1000000000,"a_i");
        ensuref((!a.count(w)),"There cannot be same elements.\n");
        a.insert(w);
    }
}

