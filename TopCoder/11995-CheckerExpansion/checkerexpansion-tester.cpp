#include<testlib.h>
#include"checkerexpansion.h"

#define TestCase1 1,0,0,4,4
#define TestCase2 5,4,1,3,4
#define TestCase3 1024,1525,512,20,2
#define TestCase4 53,85,6,5,14

#define Answer1 {"....", "....", "....", "A..." }
#define Answer2 {"A..", "...", "B..", ".B." }
#define Answer3 {"B...B...B...........", ".B.A.B.A.B.........." }
#define Answer4 {".....",".....","B....",".B.A.",".....",".....",".....",".....",".....",".....","B....",".B...","..B..",".A.B." }


int main(int argc,char*argv[]){
    registerTestlibCmd(argc,argv);
    for(int i=1;i<9;++i){
        vector<string> outputi,ansi;
        switch(i){
            case 1:outputi=CheckerExpansion().resultAfter(TestCase1);break;
            case 2:outputi=CheckerExpansion().resultAfter(TestCase2);break;
            case 3:outputi=CheckerExpansion().resultAfter(TestCase3);break;
            case 4:outputi=CheckerExpansion().resultAfter(TestCase4);break;
        }
        switch(i){
            case 1:ansi=Answer1;break;
            case 2:ansi=Answer2;break;
            case 3:ansi=Answer3;break;
            case 4:ansi=Answer4;break;
        }
        if(outputi!=ansi){
            quitf(_wa,"Wrong Answer On test %d.\n",i);
        }
    }
    quitf(_ok,"Accepted.\n");
}
