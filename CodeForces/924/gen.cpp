#include<bits/stdc++.h>
#define cir(i,a,b) for(int64_t i=a;i<b;++i)
using namespace std;
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int T=100;
    mt19937 rndx(time(nullptr));
    cout<<T<<'\n';
    cir(i,0,T){
        auto n=rndx()%100+1,k=rndx()%10+1;
        if(n==k) ++n;
        if(n<k) swap(n,k);
        cout<<n<<' '<<k<<'\n';
    }
    return 0;
}
