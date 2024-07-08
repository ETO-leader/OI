#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
ifstream fcin("preprocessor.in");
ofstream fcout("preprocessor.out");
class fileio{
public:
    ~fileio(){
        fcin.close();fcout.close();
    }
} set_fileio;
using lint=long long;
using VI=vector<lint>;
lint C(lint a,lint b,lint p){
    auto frc=[](lint x){
        lint res=1;
        cir(i,1,x+1) res*=i;
        return res;
    }(b);
    lint res=1;
    cir(i,a-b+1,a+1){
        auto g=gcd(frc,1ll*i);
        (res*=(i/g))%=p;
        frc/=g;
    }
    return res;
}
void error(){
    cout<<"0\n";exit(0);
}
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n;lint s,t,p;fcin>>n>>s>>t>>p;
    VI a(n),b(n);
    cir(i,0,n){
        int p;fcin>>a[i]>>b[i]>>p;
        s-=p;t-=p;a[i]=(a[i]-p+1)/2;
        b[i]=(b[i]-p)/2;
        if(a[i]>b[i]) error();
    }
    s=(s+1)/2;t/=2;
    auto calc=[&](int st,lint x){
        cir(i,0,n) if(st&(1<<i))
            x-=b[i]+1-a[i];
        if(x<0) return (lint)(0);
        return C(x+n,n,p);
    };
    auto solve=[&](lint up){
        lint ans=0;
        for(auto&i:a) up-=i;
        cir(i,0,(1<<n)){
            const auto stx=(
                __builtin_popcount(i)&1)?-1:1;
            ((ans+=stx*calc(i,up))+=p)%=p;
        }
        return ans;
    };
    fcout<<(solve(t)-solve(s-1)+p)%p<<'\n';
    return 0;
}
