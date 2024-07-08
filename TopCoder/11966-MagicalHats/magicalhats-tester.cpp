#include"magicalhats.h"
#include<testlib.h>

#define TestCase1 {"H"},{1},1
#define TestCase2 {"HHH","H.H","HH."},{9},1
#define TestCase3 {"HH","HH"},{1,2,3,4},3
#define TestCase4 {"HHH","HHH","H.H"},{13,13,13,13},2
#define TestCase5 {"HHH","HHH","H.H"},{13,13,13,13},3
#define TestCase6 {"H.H.",".H.H","H.H."},{17},6
#define TestCase7 {"HHH","H.H","HHH","H.H","HHH"},{33,337,1007,2403,5601,6003,9999},5
#define TestCase8 {".............",".............",".............",".............",".............",".............",".....H.H.....","......H......",".....H.H.....",".............",".............",".............","............."},{22},3

#define Answer1 1
#define Answer2 9
#define Answer3 6
#define Answer4 13
#define Answer5 26
#define Answer6 -1
#define Answer7 1377
#define Answer8 22

int main(int argc,char*argv[]){
    registerTestlibCmd(argc,argv);
    for(int i=1;i<9;++i){
        auto outputi=0,ansi=0;
        switch(i){
            case 1:outputi=MagicalHats().findMaximumReward(TestCase1);break;
            case 2:outputi=MagicalHats().findMaximumReward(TestCase2);break;
            case 3:outputi=MagicalHats().findMaximumReward(TestCase3);break;
            case 4:outputi=MagicalHats().findMaximumReward(TestCase4);break;
            case 5:outputi=MagicalHats().findMaximumReward(TestCase5);break;
            case 6:outputi=MagicalHats().findMaximumReward(TestCase6);break;
            case 7:outputi=MagicalHats().findMaximumReward(TestCase7);break;
            case 8:outputi=MagicalHats().findMaximumReward(TestCase8);break;
        }
        switch(i){
            case 1:ansi=Answer1;break;
            case 2:ansi=Answer2;break;
            case 3:ansi=Answer3;break;
            case 4:ansi=Answer4;break;
            case 5:ansi=Answer5;break;
            case 6:ansi=Answer6;break;
            case 7:ansi=Answer7;break;
            case 8:ansi=Answer8;break;
        }
        if(outputi!=ansi){
            quitf(_wa,"Wrong Answer On test %d. Expected %d, found %d.\n",i,ansi,outputi);
        }
    }
    quitf(_ok,"Accepted.\n");
}
