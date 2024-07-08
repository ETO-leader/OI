#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
template<typename T>
using vector_t=unordered_map<int,T>;
const int MOD=998244353;
lint qpow(lint a,lint b){
    lint res=1;
    while(b){
        if(b&1) (res*=a)%=MOD;
        (a*=a)%=MOD;(b>>=1);
    }
    return res;
}
lint&chg(lint&d,lint a){
    return (d+=a)%=MOD;
}
vector<vector_t<lint>> D;
vector<vector<int>> G;
void dfs(int u,const int w,int f=0){
    auto&d=D[u];d.clear();
    int ssz=0;
    for(auto&i:G[u]) if(i!=f)
        dfs(i,w,u),++ssz;
    d[w]=d[-1]=1;
    if(!ssz) return;
    for(auto&i:G[u]) if(i!=f){
        vector<pair<int,lint>> usf,cus;
        for(auto&[k,w]:d) usf.push_back({k,w});
        for(auto&[k,w]:D[i]) cus.push_back({k,w});
        d.clear();
        for(auto&[k,uw]:usf) for(auto&[p,cw]:cus){
            const lint rw=uw*cw%MOD;
            if(k<0&&p<0) chg(d[min(k,p-1)],rw);
            else if(k<0&&p>=0) chg(d[(k+p>=0?p-1:k)],rw);
            else if(k>=0&&p<0) chg(d[(k+p>=0?k:p-1)],rw);
            else chg(d[max(k,p-1)],rw);
        }
    }
}
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n;cin>>n;G.resize(n+1);D.resize(n+1);
    cir(i,0,n-1){
        int u,v;cin>>u>>v;
        G[u].push_back(v),G[v].push_back(u);
    }
    lint ans=0;
    cir(i,1,n){
        dfs(1,i);
        for(auto&[k,w]:D[1]) chg(ans,w*(k<0));
    }
    cir(i,0,n) (ans*=qpow(2,MOD-2))%=MOD;
    cout<<ans<<'\n';
    return 0;
}
