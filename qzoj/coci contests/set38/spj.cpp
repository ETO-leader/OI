#include"testlib.h"

int main(int argc,char*argv[]){
    registerTestlibCmd(argc,argv);
    const auto pans=ouf.readDouble();
    const auto jans=ans.readDouble();
    if(fabs(pans-jans)>1e-3) quitf(_wa,"diff = %.8lf\n",fabs(pans-jans));
    quitf(_ok,"diff = %.8lf\n",fabs(pans-jans));
}
