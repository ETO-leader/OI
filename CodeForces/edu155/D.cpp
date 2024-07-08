#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=__int128;
using VI=vector<lint>;
istream&operator>>(istream&is,lint&p){
    string s;is>>s;p=0;lint v=1;
    for(auto&i:s) i=='-'?(v*=-1):(p*=10)+=(i-'0');
    return p*=v,is;
}
ostream&operator<<(ostream&os,lint p){
    if(p>9) os<<(p/10);
    return os<<(int)(p%10);
}
static constexpr int MOD=998244353;
static constexpr int lgx=40;
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n;cin>>n;VI a(n);
    for(auto&i:a) cin>>i;
    lint ans=0;
    cir(x,0,lgx){
        VI px(2),cx(2);
        lint tpx=0,cnx=0;
        for(auto&i:a){
            tpx^=(bool)(i&(lint)(1LL<<x));
            ++cx[tpx];px[tpx]+=cnx;
            (ans+=(lint)(1LL<<x)*(cx[tpx^1]*
                cnx-px[tpx^1]))%=MOD;
            if(tpx) (ans+=(lint)(1LL<<x)*(cnx+1))%=MOD;
            ++cnx;
        }
    }
    cout<<ans<<'\n';
    return 0;
}
