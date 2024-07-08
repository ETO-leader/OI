#include<bits/stdc++.h>
#include"testlib.h"
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
int main(int argc,char*argv[]){
    registerGen(argc,argv,1);
    rnd.setSeed(time(NULL));
    int T=1;cout<<T<<'\n';
    int n=atoi(argv[1]),m=atoi(argv[2]);
    cout<<n<<' '<<m<<'\n';
    cir(i,0,n){
        cir(j,0,m) cout<<rnd.next(1,100000000)<<' ';
        cout<<'\n';
    }
}
