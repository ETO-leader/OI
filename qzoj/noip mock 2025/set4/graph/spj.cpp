#include"testlib.h"

int main(int argc,char*argv[]){
    registerTestlibCmd(argc,argv);
    auto pans=ouf.readInt();
    auto jans=ans.readInt();
    if(pans<jans) quitf(_wa,"oh no!.\n");
    quitf(_ok,"maybe you're correct, jans %d, pans %d.\n", jans, pans);
}
