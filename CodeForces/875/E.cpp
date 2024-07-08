#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
using ull=unsigned long long;
using VI=vector<int>;
const int MOD=998244353;
const int maxn=3e5+7;
vector<lint> fact;
void init_fact(int n){
    fact.resize(n+1);fact[0]=1;
    cir(i,1,n+1) fact[i]=fact[i-1]*i%MOD;
}
lint qpow(lint a,lint b){
    lint res=1;
    while(b){
        if(b&1) (res*=a)%=MOD;
        (a*=a)%=MOD;b>>=1;
    }
    return res;
}
lint inv(lint p){return qpow(p,MOD-2);}
lint C(int a,int b){
    if(a<b) return 0;
    if((!a)||(!b)) return 1;
    return fact[a]*inv(fact[b])%MOD*inv(fact[a-b])%MOD;
}
lint catalan(int n){
    if(n&1) return 0;
    return C(n,n/2)*inv(n/2+1)%MOD;
}
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    init_fact(maxn);
    int T;cin>>T;
    while(T--){
        int n,k;cin>>n>>k;
        lint ans=1;vector<ull> cx(n+1);
        cir(i,0,k){
            int l,r;cin>>l>>r;--l,--r;
            cx[l]+=qpow(3,i+1);
            cx[r+1]-=qpow(3,i+1);
        }
        unordered_map<ull,int> la;
        cir(i,1,n+1)
            cx[i]+=cx[i-1],la[cx[i]]=i;
        function<lint(int,int,ull)> dfs
        =[&](int l,int r,ull c){
            int len=0;
            cir(i,l,r+1){
                if(cx[i]!=c)
                   dfs(i,la[cx[i]],cx[i]),i=la[cx[i]];
                else ++len;
            }
            return (ans*=catalan(len))%=MOD;
        };
        cout<<dfs(0,n-1,0)<<'\n';
    }
    return 0;
}
