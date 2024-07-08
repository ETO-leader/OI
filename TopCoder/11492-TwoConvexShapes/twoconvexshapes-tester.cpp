#include"twoconvexshapes.h"
#include"testcases.h"
#include<testlib.h>

int main(int argc,char*argv[]){
    registerTestlibCmd(argc,argv);
    for(int i=1;i<TestCaseCount+1;++i){
        auto outputi=0,ansi=0;
        switch(i){
            case 1:outputi=TwoConvexShapes().countWays(TestCase1);break;
            case 2:outputi=TwoConvexShapes().countWays(TestCase2);break;
            case 3:outputi=TwoConvexShapes().countWays(TestCase3);break;
            case 4:outputi=TwoConvexShapes().countWays(TestCase4);break;
            case 5:outputi=TwoConvexShapes().countWays(TestCase5);break;
            case 6:outputi=TwoConvexShapes().countWays(TestCase6);break;
        }
        switch(i){
            case 1:ansi=Answer1;break;
            case 2:ansi=Answer2;break;
            case 3:ansi=Answer3;break;
            case 4:ansi=Answer4;break;
            case 5:ansi=Answer5;break;
            case 6:ansi=Answer6;break;
        }
        if(outputi!=ansi){
            quitf(_wa,"Wrong Answer On test %d. Expected %d, found %d.\n",i,ansi,outputi);
        }
    }
    quitf(_ok,"Accepted.\n");
}
