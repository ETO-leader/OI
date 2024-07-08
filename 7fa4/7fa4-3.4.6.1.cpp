#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
using VL=vector<lint>;
istream&operator>>(istream&is,VL&v){
    for(auto&i:v) is>>i;
    return is;
}
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n;cin>>n;VL a(n),b(n);
    cin>>a>>b;const int _sz=(1<<n);
    vector<VL> D(n,VL(_sz));
    D[0][0]=b[0]*a[0];
    cir(i,0,n-1) cir(s,0,_sz) if(s<(1<<(i+1))){
        lint c1=D[i][s]+b[i+1-__builtin_popcount(s)]*a[i+1];
        lint c2=D[i][s],sx=s;
        while(sx){
            auto cx=i+1-__builtin_popcount(sx);
            auto cl=(31-__builtin_clz(sx));
            D[i+1][sx]=max(D[i+1][sx],c1);
            D[i+1][sx+(1<<(i+1))]=max(D[i+1][sx+(1<<(i+1))],c2);
            c1+=(b[cx+1]*a[cl]);
            c2+=(b[cx]*a[cl]);
            sx-=(1<<cl);
        }
        D[i+1][sx]=max(D[i+1][sx],c1);
        D[i+1][sx+(1<<(i+1))]=max(D[i+1][sx+(1<<(i+1))],c2);
    }
    cout<<D[n-1][0]<<'\n';
    return 0;
}
