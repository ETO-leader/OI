#include"foxandflowershopdivone.h"
#include<testlib.h>

#define TestCase1 \
{"LLL",\
 "PPP",\
 "LLL"},\
1

#define TestCase2 \
{"LLL",\
 "PPP",\
 "LLL"},\
0

#define TestCase3 \
{"...",\
 "...",\
 "..."},\
3

#define TestCase4 \
{"LLPL.LPP",\
 "PLPPPPLL",\
 "L.P.PLLL",\
 "LPL.PP.L",\
 ".LLL.P.L",\
 "PPLP..PL"},\
2

#define TestCase5 \
{"LLLLLLLLLL",\
 "LLLLLLLLLL",\
 "LLLLLLLLLL",\
 "LLLLLLLLLL",\
 "LLLLLLLLLL"},\
0

#define TestCase6 \
{"LLLP..LLP.PLL.LL..LP",\
 "L.PL.L.LLLL.LPLLPLP.",\
 "PLL.LL.LLL..PL...L..",\
 ".LPPP.PPPLLLLPLP..PP",\
 "LP.P.PPL.L...P.L.LLL",\
 "L..LPLPP.PP...PPPL..",\
 "PP.PLLL.LL...LP..LP.",\
 "PL...P.PPPL..PLP.L..",\
 "P.PPPLPLP.LL.L.LLLPL",\
 "PLLPLLP.LLL.P..P.LPL",\
 "..LLLPLPPPLP.P.LP.LL",\
 "..LP..L..LLPPP.LL.LP",\
 "LPLL.PLLPPLP...LL..P",\
 "LL.....PLL.PLL.P....",\
 "LLL...LPPPPL.PL...PP",\
 ".PLPLLLLP.LPP...L...",\
 "LL...L.LL.LLLPLPPPP.",\
 "PLPLLLL..LP.LLPLLLL.",\
 "PP.PLL..L..LLLPPL..P",\
 ".LLPL.P.PP.P.L.PLPLL"},\
9

#define Answer1 7
#define Answer2 6
#define Answer3 0
#define Answer4 38
#define Answer5 -1
#define Answer6 208

int main(int argc,char*argv[]){
    registerTestlibCmd(argc,argv);
    for(int i=1;i<9;++i){
        auto outputi=0,ansi=0;
        switch(i){
            case 1:outputi=FoxAndFlowerShopDivOne().theMaxFlowers(TestCase1);break;
            case 2:outputi=FoxAndFlowerShopDivOne().theMaxFlowers(TestCase2);break;
            case 3:outputi=FoxAndFlowerShopDivOne().theMaxFlowers(TestCase3);break;
            case 4:outputi=FoxAndFlowerShopDivOne().theMaxFlowers(TestCase4);break;
            case 5:outputi=FoxAndFlowerShopDivOne().theMaxFlowers(TestCase5);break;
            case 6:outputi=FoxAndFlowerShopDivOne().theMaxFlowers(TestCase6);break;
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
