#include"testlib.h"
#include<bits/stdc++.h>
using namespace std;
static constexpr auto eps=1e-6;
int main(int argc,char*argv[]){
    registerTestlibCmd(argc,argv);
    const auto jans=ans.readDouble();
    const auto pans=ouf.readDouble();
    if(fabs(pans-jans)>eps) quitf(_wa,">_< your answer: %.10lf, jury's answer: %.10lf.\n",pans,jans);
    else quitf(_ok,"orz ^v^");
    return 0;
}
