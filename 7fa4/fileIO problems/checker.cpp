#include"testlib.h"
#include<iostream>

int main(int argc,char*argv[]){
    registerTestlibCmd(argc,argv);
    auto m=inf.readInt()+2;
    while(m--) inf.readLine();
    auto T=inf.readInt();
    for(int i=1;i<T+1;++i){
        auto usr=ouf.readReal(),std=ans.readReal();
        if(abs(usr-std)>1e-4){
            quitf(_wa,"wrong answer on line %d, expected %5lf, found %5lf\n",i,std,usr);
        }
        usr=ouf.readReal();std=ans.readReal();
        if(abs(usr-std)>1e-4){
            quitf(_wa,"wrong answer on line %d, expected %5lf, found %5lf\n",i,std,usr);
        }
    }
    quitf(_ok,"unbeilevable accepted.\n");
}
