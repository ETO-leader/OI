#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
const int MOD=19260817;
const int pr_lss_1k=168;
const vector<int> mrp{
    2,3,5,7,11,13,17,19};
mt19937_64 rnd(time(NULL));
vector<lint> p;
unordered_map<int,int> id;
void initpr(int n){
    vector<bool> isp(n,true);
    cir(i,2,n){
        if(!isp[i]) continue;
        for(int j=i*2;j<n;j+=i) isp[j]=false;
        id[i]=p.size();p.push_back(i);
    }
}
lint qpow(lint a,lint b,int mod=MOD){
    lint res=1;
    while(b){
        if(b&1) (res*=a)%=mod;
        (a*=a)%=mod;b>>=1;
    }
    return res;
}
lint __inv(lint p){return qpow(p,MOD-2);}
vector<lint> inv;
void initinv(int n){
    inv.resize(n);
    cir(i,0,n) inv[i]=__inv(i);
}
struct query{int l,r,idx;};
bool miller_rabin(lint p){
    if(p<2) return false;
    if(p==2||p==3) return true;
    if((!(p%2))||(!(p%3))) return false;
    int b=p-1,t=0;
    while(b&1) (b>>=1),(++t);
    for(auto&i:mrp){
        int r=qpow(i,b,p);
        if(r==1||r==p-1) continue;
        bool isnp=true;
        for(int j=1;j<=t&&isnp;++j){
            (r*=r)%=p;isnp=(r!=p-1);
        }
        if(isnp) return false;
    }
    return true;
}
lint pollard_rho(lint x){
    lint s=0,t=0,c=rnd()%(x-1)+1,v=1;
    for(int g=1;;g*=2,s=t,v=1){
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
void prime_alg(lint x,lint&md){
    if(x<md||x<2) return;
    if(miller_rabin(x))
        return md=max(md,x),void();
    lint p=x;
    while(p>=x) p=pollard_rho(p);
    while(!(x%p)) x/=p;
    prime_alg(x,md);prime_alg(p,md);
}
const int blcs=1e3;
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int x;cin>>x;
    cout<<miller_rabin(x)<<'\n';
    return 0;
}
