#include"testlib.h"
#include<bits/stdc++.h>

#if not defined(__GRADER_CPP)

#define __GRADER_CPP 1

#if defined FILE_LOG
    std::ofstream Info("grader.log");
#else
    #define Info std::clog
#endif



int main(int argc,char*argv[]){
    registerTestlibCmd(argc,argv);
    return 0;
}

#endif