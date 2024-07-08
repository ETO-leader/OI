#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
using VI=vector<int>;
const int _inf=1e9+7;
vector<VI> up,G;
VI hvs,siz,fx;
int findhvs(int u,int errn=-1){
    const int n=G.size()-1;
    int res=0,rw=-1;
    for(auto&i:G[u]) if(i!=errn){
        if(rw<siz[i]) rw=siz[i],res=i;
    }
    return res;
}
int lg2;
void recalc(int u,int hs){
    up[u][0]=hs;hvs[u]=hs;
    cir(i,1,lg2) up[u][i]=up[up[u][i-1]][i-1];
}
int init(int u,int f=0){
    siz[u]=1;fx[u]=f;
    for(auto&i:G[u]) if(i!=f) siz[u]+=init(i,u);
    //cout<<u<<":"<<findhvs(u,f)<<'\n'<<flush;
    recalc(u,findhvs(u,f));
    return siz[u];
}
bool successful(int u,int w){
    const int n=G.size()-1;
    const int wx=w;
    for(auto&i:G[u]) if(i!=fx[u]){
        if(siz[i]>wx/2) return false;
        w-=siz[i];
    }
    return !((--w)>wx/2);
}
int jump(int u){
    int res=u;
    for(int i=lg2-1;~i;--i)
        if(siz[u]-siz[up[res][i]]<=siz[u]/2)
            res=up[res][i];
    return res;
}
void breakline(int u,int v){
    const int n=G.size()-1;
    siz[u]=n-siz[v];fx[u]=v;
    recalc(u,findhvs(u,v));
}
void dfs(int u,lint&ans,int f=0){
    for(auto&i:G[u]) if(i!=f){
        const auto lup=up[u];
        const auto lf=fx[u],lsiz=siz[u];
        breakline(u,i);
        const int ju=jump(u),jv=jump(i);
        ans+=ju+jv;
        if((ju!=u)&&successful(fx[ju],siz[u]))
            ans+=fx[ju];
        if((jv!=i)&&successful(fx[jv],siz[i]))
            ans+=fx[jv];
        dfs(i,ans,u);
        up[u]=lup;fx[u]=lf;siz[u]=lsiz;
    }
}
void resize_all(int n){
    G.clear();fx.clear();
    siz.clear();hvs.clear();
    lg2=log2(n)+2;
    if(up.empty()) up.assign(n+1,VI(lg2));
    G.resize(n+1);
    siz.resize(n+1);fx.resize(n+1);hvs.resize(n+1);
    siz[0]=-_inf;
}
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    //freopen("centroid.in","r",stdin);
    //freopen("centroid.out","w",stdout);
    int T;cin>>T;
    while(T--){
        int n;lint ans=0;cin>>n;
        resize_all(n);
        cir(i,0,n-1){
            int u,v;cin>>u>>v;
            G[u].push_back(v);G[v].push_back(u);
        }
        //init :: segmentation fault
        init(1);dfs(1,ans);
        cout<<ans<<'\n';
    }
    return 0;
}