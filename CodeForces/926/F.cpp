#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
using VI=vector<lint>;
static constexpr auto MOD=998244353;
class solver{
private:
    constexpr auto qpow(lint a,lint b){
        lint res=1;
        while(b){
            if(b&1) (res*=a)%=MOD;
            (a*=a)%=MOD;b>>=1;
        }
        return res;
    }
    constexpr auto inv(lint a){
        return qpow(a,MOD-2);
    }
    constexpr auto C(lint n,lint m){
        lint res=1;
        cir(i,0,m) (res*=n)%=MOD,--n;
        cir(i,0,m) (res*=inv(i+1))%=MOD;
        return res;
    }
    VI lx,ls,rs,w;
    auto dfs(int u){
        if(u<0) return;
        dfs(ls[u]);
        lx.push_back(w[u]);
        dfs(rs[u]);
    }
public:
    solver(int n,int c):ls(n+1),rs(n+1),w(n+1){
        cir(i,1,n+1) cin>>ls[i]>>rs[i]>>w[i];
        dfs(1);
        lx.push_back(c);
        int las=1,cnt=0;
        lint ans=1;
        for(auto&i:lx){
            if(i<0){
                ++cnt;
            }else{
                (ans*=C(i-las+cnt,cnt))%=MOD;
                cnt=0;las=i;
            }
        }
        cout<<ans<<'\n';
    }
};
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int T;cin>>T;
    while(T--) [](){
        int n,c;cin>>n>>c;
        solver solve(n,c);
    }();
    return 0;
}
