#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using VI=vector<int>;
using lint=long long;
const int MOD=998244353;
struct frac{
    lint p,q;
    frac&operator+=(frac f){
        (p=f.p*q+p*f.q)%=MOD;
        (q*=f.q)%=MOD;
        return *this;
    }
    void reverse(){swap(p,q);}
    frac(lint _p=0,lint _q=1):p(_p),q(_q){}
};
VI siz,sizc,F;
lint inv(lint k){
    lint res=1,p=MOD-2;
    while(p){
        if(p&1) (res*=k)%=MOD;
        (k*=k)%=MOD;(p>>=1);
    }
    return res;
}
ostream&operator<<(ostream&os,frac f){
    os<<f.p*inv(f.q)%MOD;
    return os;
}
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n;cin>>n;sizc.resize(n+1);
    F.resize(n+1);siz.resize(n+1,1);
    cir(i,2,n+1) cin>>F[i];
    for(int i=n;i>1;--i){
        sizc[siz[i]]++;
        siz[F[i]]+=siz[i];
    }
    sizc[siz[1]]++;
    frac ans;
    cir(i,1,n+1) if(sizc[i])
        ans+=frac(sizc[i],i);
    cout<<ans<<'\n';
    return 0;
}
