#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using db=long double;
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    db n,p,l,r;cin>>n>>p>>l>>r;
    db pi=1,exp=1/p;
    cout<<fixed<<setprecision(16)
        <<min<db>(r/exp,n)-
        min<db>((l-1)/exp,n)<<'\n';
    return 0;
}
