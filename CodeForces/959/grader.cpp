#include"testlib.h"
#include<bits/stdc++.h>

int baseP,baseM;

int count;

extern int getHash(std::string s){
    int64_t res=0;++count;
    std::ranges::reverse(s);
    if(count>3) quitf(_wa,"too many queries.\n");
    for(auto&i:s) ((res*=baseP)+=(i-'a'+1))%=baseM;
    return res;
}

extern void answer(int p,int m){
    if(p!=baseP||m!=baseM) quitf(_wa,"not correct. expected p=%d, m=%d, found p=%d, m=%d.\n",baseP,baseM,p,m);
}

extern void attack();

int main(int argc,char*argv[]){
    registerTestlibCmd(argc,argv);
    int T=inf.readInt();
    while(T--){
        baseP=inf.readInt();baseM=inf.readInt();
        count=0;
        attack();
    }
    quitf(_ok,"accepted.\n");
}
