#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
using VI=vector<lint>;
static constexpr int MOD=1e9+7;
lint qpow(lint a,lint b){
    lint res=1;
    while(b){
        if(b&1) (res*=a)%=MOD;
        (a*=a)%=MOD;b>>=1;
    }
    return res;
}
lint inv(lint p){return qpow(p,MOD-2);}
class graph{
private:
    vector<VI> G,rg;
    VI vis,siz,pri,nodel;
    void fndcir(int u,auto&c,int f=-1){
        vis[u]=true;
        for(auto&i:G[u]){
            if(!vis[i]) fndcir(i,c,u);
            else if(i!=f) c={u,i};
        }
    }
    void build(int u,auto&c,int f=-1){
        for(auto&i:G[u]){
            if(i!=f&&i!=c.first){
                pri[i]=u;build(i,c,u);
            }
        }
    }
    int dfssz(int u,int f=0){
        for(auto&i:G[u]) if(i!=f)
            siz[u]+=dfssz(i,u);
        return siz[u];
    }
    void clear(){}
    lint getansc(auto&c){
        auto&[u,v]=c;
        build(u,c,v);
        VI ind(G.size());
        for(auto&x:nodel) for(auto&i:G[x]){
            if(i<pri[x]) 
        }
    }
public:
    lint join(){

    }
};
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n;cin>>n;
    auto lfn=[&](int u){return u;};
    auto dwn=[&](int u){return u+n;};
    cir(i,0,n*2){
        int x,y;cin>>x>>y;
        G[lfn(x)].push_back(dwn(y));
        G[dwn(y)].push_back(lfn(x));
    }
    try{
        
    }catch(int x){
        
    }
    return 0;
}
