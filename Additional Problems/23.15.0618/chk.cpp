#include"testlib.h"
#define cir(i,a,b) for(int i=a;i<b;++i)
int main(int argc,char*argv[]){
    registerTestlibCmd(argc,argv);
    int N=inf.readInt(),M=inf.readInt();
    int x=0,r;
    cir(i,0,N) r=inf.readInt();
    cir(i,0,M){
        r=inf.readInt();
        if(r==3){
            ++x;
            r=inf.readInt();
            r=inf.readInt();
        }else{
            r=inf.readInt();
            r=inf.readInt();
            r=inf.readInt();
        }
    }
    while(x--){
        if(ouf.readInt()!=ans.readInt())
            quitf(_wa,"Wrong Answer.\n");
    }
    quitf(_ok,"Accepted\n");
}
