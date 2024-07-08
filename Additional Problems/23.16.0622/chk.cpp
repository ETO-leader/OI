#include"testlib.h"
int main(int argc,char*argv[]){
    registerTestlibCmd(argc,argv);
    if(ouf.readInt()!=ans.readInt())
        quitf(_wa,"Wrong Answer.\n");
    quitf(_ok,"Accepted.\n");
}