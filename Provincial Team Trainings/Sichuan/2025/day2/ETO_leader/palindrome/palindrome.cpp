#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
ifstream inf("palindrome.in");
ofstream ouf("palindrome.out");
class fileio{
public:
    ~fileio(){
        inf.close();ouf.close();
    }
} use_fileio;
using lint=long long;
static constexpr auto MOD=998244353;
class mathbase{
public:
    const lint qpow(lint a,lint b) const{
        auto res=1ll;
        while(b){
            if(b&1) (res*=a)%=MOD;
            (a*=a)%=MOD;b>>=1;
        }
        return res;
    }
    const lint inv(lint x) const{
        return qpow(x,MOD-2);
    }
} math;
int main(){
    ios::sync_with_stdio(false),inf.tie(nullptr);
    int n,m;inf>>n>>m;vector<int> s(n);
    for(auto&i:s) inf>>i,--i;
    vector<lint> pw(m);
    vector<int> idk(m,-1);
    cir(i,0,n){
        vector<int> apr;
        cir(len,0,n){
            if(i-len<0||i+len>n-1) break;
            const auto u=s[i-len],v=s[i+len];
            if(idk[u]==-1) apr.emplace_back(u);
            if(idk[v]==-1&&u!=v) apr.emplace_back(v);
            if(idk[u]!=-1&&idk[u]!=v) break;
            if(idk[v]!=-1&&idk[v]!=u) break;
            idk[u]=v;idk[v]=u;
            ++pw[m-apr.size()];
        }
        for(auto&x:apr) idk[x]=-1;
    }
    cir(i,0,n){
        vector<int> apr;
        cir(len,0,n){
            if(i-len<0||i+1+len>n-1) break;
            const auto u=s[i-len],v=s[i+1+len];
            if(idk[u]==-1) apr.emplace_back(u);
            if(idk[v]==-1&&u!=v) apr.emplace_back(v);
            if(idk[u]!=-1&&idk[u]!=v) break;
            if(idk[v]!=-1&&idk[v]!=u) break;
            idk[u]=v;idk[v]=u;
            ++pw[m-apr.size()];
        }
        for(auto&x:apr) idk[x]=-1;
    }
    auto ans=0ll;
    cir(i,0,m) (ans+=math.qpow(m,i)*pw[i])%=MOD;
    ouf<<ans<<'\n';
    return 0;
}
