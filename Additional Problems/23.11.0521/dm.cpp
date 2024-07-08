#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    cout<<1<<'\n'<<20<<'\n';
    mt19937 rnd(time(NULL));
    cir(i,0,20) cout<<rnd()%21<<' ';
    cout<<'\n';
    return 0;
}
