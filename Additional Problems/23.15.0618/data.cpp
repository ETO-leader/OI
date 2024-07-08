#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
mt19937 rnd(time(NULL));
int rndint(int mx){
    return rnd()%mx+1;
}
//499996 500000
const int N=499996,M=500000,MX=(1<<30);
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    cout<<N<<' '<<M<<'\n';
    cir(i,0,N) cout<<rndint(MX)<<' ';
    cout<<'\n';
    cir(i,0,M){
        int op=rndint(3),l=rndint(N),r=rndint(N);
        if(l>r) swap(l,r);
        cout<<op<<' '<<l<<' '<<r;
        if(op!=3) cout<<' '<<rndint(MX);
        cout<<'\n';
    }
}
