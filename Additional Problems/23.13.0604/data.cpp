#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
mt19937 rnd(time(NULL));
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    const int N=100000;
    cout<<N<<'\n';
    cir(i,0,N) cout<<rnd()%1000000000+1<<' ';
    cout<<'\n';
    cir(i,0,N) cout<<rnd()%1000000000+1<<' ';
    cout<<'\n';
    return 0;
}
