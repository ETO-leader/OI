#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
class dsu{
private:
    vector<int> f;int setsize;
public:
    int findset(int x){
        return f[x]==x?x:(f[x]=findset(f[x]));}
    void merge(int u,int v){
        u=findset(u);v=findset(v);
        setsize-=(u!=v);f[u]=v;}
    int size(){return setsize;}
    dsu(int n):f(n),setsize(n){
        iota(f.begin(),f.end(),0);}
};
const int MOD=998244353;
lint qpow(lint a,lint b){
    lint res=1;
    while(b){
        if(b&1) (res*=a)%=MOD;
        (a*=a)%=MOD;b>>=1;
    }
    return res;
}
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    lint n,m;cin>>n>>m;dsu ds(n);
    vector<int> p(n);
    for(auto&i:p) cin>>i,--i;
    lint ans=0;
    cir(i,0,n){
        if(i) ds.merge(i-1,p[i-1]);
        if(ds.findset(i)==ds.findset(p[i])) continue;
        const lint _sz=ds.size();
        (ans+=(qpow(m,_sz-2)*((m*(m-1)/2)%MOD)))%=MOD;
    }
    cout<<ans<<'\n';
    return 0;
}
