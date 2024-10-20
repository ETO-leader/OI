#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
struct edge{int v,eid;};
using VI=vector<int64_t>;
vector<VI> G,T;
VI dfn,low,stc,w,siz;
auto tarjan(int u,int&cnt,int&dcnt,int&scnt,int f=-1)->void{
    dfn[u]=low[u]=++dcnt;++cnt;
    w[u]=-1;stc.push_back(u);
    auto connect=[](int u,int v){
        T[u].push_back(v);T[v].push_back(u);
    };
    for(auto&i:G[u]) if(i!=f){
        if(!dfn[i]){
            tarjan(i,cnt,dcnt,scnt,f);
            low[u]=min(low[u],low[i]);
            if(low[i]>dfn[u]-1){
                connect(++scnt,u);++w[scnt];
                do connect(scnt,stc.back()),++w[scnt];
                while([](){auto b=stc.back();
                    stc.pop_back();return b;}()^i);
            }
        }else{
            low[u]=min(low[u],dfn[i]);
        }
    }
}
auto dfs(int u,auto iscmn,int64_t&ans,int cnt,int f=0)->int{
    siz[u]=iscmn(u);
    for(auto&i:T[u]) if(i!=f){
        auto sz=dfs(i,iscmn,ans,cnt,u);
        ans+=(siz[u]*sz*w[u])*2;
        siz[u]+=sz;
    }
    return ans+=(siz[u]*(cnt-siz[u])*w[u])*2,siz[u];
}
auto init(auto n){
    G.resize(n<<1);T.resize(n<<1);
    dfn.resize(n<<1);low.resize(n<<1);
    w.resize(n<<1);siz.resize(n<<1);
}
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n,m;cin>>n>>m;init(n);
    cir(i,0,m){
        int u,v;cin>>u>>v;
        G[u].push_back(v);G[v].push_back(u);
    }
    cout<<[&](){
        int64_t res=0;int dc=0,sc=n;
        cir(i,1,n+1) if(!dfn[i]){
            int cnt=0;tarjan(i,cnt,dc,sc);
            dfs(i,[&](int u){return u<n+1;},res,cnt);
        }
        return res;
    }()<<'\n';
    return 0;
}
