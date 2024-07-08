#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using VI=vector<int>;
const int MOD=998244353;
template<typename T>
istream&operator>>(istream&is,vector<T>&v){
    for(auto&i:v) is>>i;
    return is;
}
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n;cin>>n;
    vector<VI> card(n,VI(2)),D(n,VI(2));
    cin>>card;
    D[0][0]=D[0][1]=1;
    cir(i,1,n){
        auto&d=D[i],&c=card[i];
        auto&dl=D[i-1],&cl=card[i-1];
        if(cl[0]!=c[0]) d[0]+=dl[0];
        if(cl[1]!=c[0]) d[0]+=dl[1];
        if(cl[0]!=c[1]) d[1]+=dl[0];
        if(cl[1]!=c[1]) d[1]+=dl[1];
        d[0]%=MOD;d[1]%=MOD;
    }
    cout<<(D[n-1][0]+D[n-1][1])%MOD<<'\n';
    return 0;
}
