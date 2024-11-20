#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
static constexpr auto MOD=998244353;
class trie{
private:
    vector<array<int,2>> ch;
    vector<lint> siz;
    vector<lint> pwm;
    static constexpr auto b=42;
    int cnt;
    auto query(int u,int v,lint x,int cur){
        // clog<<u<<' '<<v<<' '<<siz[u]<<' '<<siz[v]<<' '<<cur<<'\n';
        if((!u)&&cur!=b-1) return pwm[siz[v]]+1;
        if((!v)&&cur!=b-1) return pwm[siz[u]]+1;
        if(cur<0) return (u==v?(pwm[siz[u]]+1):(pwm[siz[u]]+1)*(pwm[siz[v]]+1))%MOD;
        const auto xw=(x>>cur)&1;
        // if(xw) clog<<"! "<<cur<<'\n';
        if(u==v){
            if(!xw){
                return (query(ch[u][0],ch[v][0],x,cur-1)
                    +query(ch[u][1],ch[v][1],x,cur-1)+MOD-1)%MOD;
            }else{
                const auto res=(
                    query(ch[u][0],ch[u][1],x,cur-1)
                )%MOD;
                return res;
            }
        }
        if(!xw){
            return (query(ch[u][0],ch[v][0],x,cur-1)
                +query(ch[u][1],ch[v][1],x,cur-1)+MOD-1
                +pwm[siz[ch[u][0]]]*pwm[siz[ch[u][1]]]+
                pwm[siz[ch[v][0]]]*pwm[siz[ch[v][1]]])%MOD;
        }else{
            const auto res=(
                query(ch[u][0],ch[v][1],x,cur-1)*
                query(ch[u][1],ch[v][0],x,cur-1)
            )%MOD;
            return res;
        }
    }
public:
    auto insert(lint x){
        auto u=0;
        for(auto i=b-1;~i;--i){
            const auto w=(x>>i)&1;
            if(!ch[u][w]) ch[u][w]=++cnt;
            u=ch[u][w];++siz[u];
        }
        // clog<<x<<":                   "<<u<<'\n';
    }
    auto check(lint x){
        return (query(0,0,x,b-1)+MOD-1)%MOD;
    }
    trie(int _n):ch(_n*(b+1)),siz(_n*(b+1)),pwm(_n+7),cnt(0){
        pwm[0]=1;
        cir(i,1,_n+7) pwm[i]=(pwm[i-1]<<1)%MOD;
        cir(i,0,_n+7) (pwm[i]+=MOD-1)%=MOD;
    }
};
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int T=1;
    while(T--) []{
        int n;lint x;cin>>n>>x;trie tr(n);
        cir(i,0,n){
            lint w;cin>>w;tr.insert(w);
        }
        // cout<<tr.check(x)<<'\n';
        println("{}",tr.check(x));
    }();
    return 0;
}
