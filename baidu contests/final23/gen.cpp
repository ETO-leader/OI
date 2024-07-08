#pragma GCC optimize("Ofast")
#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
mt19937 rnd(time(NULL));
int main(int argc,char*argv[]){
    ios::sync_with_stdio(false),cin.tie(0);
    int N=atoi(argv[1]),Q=atoi(argv[2]),a=(rnd()%1000+1)*((rnd()&1)?-1:1);
    cout<<N<<' '<<Q<<' '<<a<<'\n';
    cir(i,2,N+1) cout<<rnd()%(i-1)+1<<'\n';
    cir(i,0,Q){
        int tp=(rnd()&1)+1;
        cout<<tp<<' ';
        if(tp==1){
            cout<<rnd()%N+1<<' '<<(int64_t)(rnd()%1000)*((rnd()&1)?-1:1)<<'\n';
        }else{
            cout<<rnd()%N+1<<'\n';
        }
    }
    return 0;
}
