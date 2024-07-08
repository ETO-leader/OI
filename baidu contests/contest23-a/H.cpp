#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
using VI=vector<lint>;
mt19937 rnd(time(NULL));
const VI mrp{2,3,5,7,11,13,17,19};
auto qpow(__int128 a,__int128 b,lint mod){
    __int128 res=1;
    while(b){
        if(b&1) (res*=a)%=mod;
        (a*=a)%=mod;b>>=1;
    }
    return res;
}
bool miller_rabin(lint p){
    if(p<2) return false;
    if(p==2||p==3) return true;
    if((!(p%2))||(!(p%3))) return false;
    if(count(mrp.begin(),mrp.end(),p))
        return true;
    lint b=p-1,t=0;
    while(b&1) (b>>=1),(++t);
    for(auto&i:mrp){
        auto r=qpow(i,b,p);
        if(r==1||r==p-1) continue;
        bool isnp=true;
        for(lint j=1;j<=t&&isnp;++j){
            (r*=r)%=p;isnp=(r!=p-1);
        }
        if(isnp) return false;
    }
    return true;
}
lint pollard_rho(lint x){
    lint s=0,t=0,c=rnd()%(x-1)+1,v=1;
    for(lint g=1;;g*=2,s=t,v=1){
        cir(stp,1,g+1){
            t=(t*t+c)%x;v=v*abs(t-s)%x;
            if(!(stp%127)){
                lint d=__gcd(v,x);
                if(d>1) return d;
            }
        }
        lint d=__gcd(v,x);
        if(d>1) return d;
    }
}
void prime_alg(lint x,int&cnx){
    if(x<2) return;
    if(miller_rabin(x))
        return ++cnx,void();
    lint p=x;
    while(p>=x) p=pollard_rho(p);
    while(!(x%p)) x/=p;
    prime_alg(x,cnx);prime_alg(p,cnx);
}
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n;cin>>n;
    bool ans=false;
    int cnx=0;
    cir(i,0,n){
        lint x;cin>>x;
        int ansi=0;
        if(x&1) prime_alg(x,ansi);
        else ansi=1;
        ans^=(ansi&1);
        cnx+=(ansi>1);
    }
    if(cnx==1)
        cout<<"Xiaodu\n";
    else cout<<(ans&1?"Xiaodu":"Duduxiong")<<'\n';
    return 0;
}
