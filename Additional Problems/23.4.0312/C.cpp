#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using __int=__int128_t;
istream&operator>>(istream&is,__int&p){
    string s;is>>s;p=0;__int v=1;
    for(auto&i:s) i=='-'?(v*=-1):(p*=10)+=(i-'0');
    return p*=v,is;
}
ostream&operator<<(ostream&os,__int p){
    if(p<0) os<<'-',p=-p;
    if(p>9) os<<(p/10);
    return os<<(int)(p%10);
}
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n;cin>>n;
    __int npos=0,ans=0,adpos=0,apos=0;
    cir(i,0,n){
        __int ad;cin>>ad;
        apos+=ad;adpos=max(adpos,apos);
        ans=max(ans,npos+adpos);npos+=apos;
    }
    cout<<ans<<'\n';
    return 0;
}
