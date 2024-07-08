#include<bits/stdc++.h>
#define res(x) (x).resize(n+1)
#define cir(i,a,b) for(int i=a;i<b;++i)
#define rever(x) reverse((x).begin(),(x).end())
using namespace std;
using lint=long long;
struct edge{int v,w;};
vector<vector<edge>> G;
vector<vector<lint>> Mx1,Mx2;
vector<lint> Dia,imp,Siz,Sizr;
void dfs(int u,vector<vector<lint>>&mx,int f=0,bool tag=true){
    mx[u].clear();
    if(tag&&imp[u]) Dia.push_back(u);
    for(auto&i:G[u]) if(i.v!=f)
        dfs(i.v,mx,u,tag),mx[u].push_back(mx[i.v][0]+i.w);
    while(mx[u].size()<2) mx[u].push_back(0);
    sort(mx[u].begin(),mx[u].end(),greater<lint>());
}
int build_n(int u){
    imp[u]=true;
    for(auto&i:G[u]) if(Mx1[i.v][0]+i.w==Mx1[u][0])
        return build_n(i.v);
    return u;
}
map<pair<int,int>,lint> Es;
auto build_f(int n,bool rev){
    if(rev) rever(Dia);
    vector<lint> resx;
    cir(i,0,n-1){
        resx.push_back((resx.empty()?
            0:resx.back())+Es[{Dia[i],Dia[i+1]}]);
    }
    if(rev) rever(Dia);
    return resx;
}
int build(int n){
    dfs(1,Mx1);lint rtx=0,mx=0;
    cir(i,1,n+1) mx=max(mx,Mx1[i][0]+Mx1[i][1]);
    cir(i,1,n+1) if(Mx1[i][0]+Mx1[i][1]==mx){rtx=i;break;}
    int x1=false,x2=false,rt=0;imp[rtx]=true;
    for(auto&i:G[rtx]){
        if(!x1&&Mx1[rtx][0]==Mx1[i.v][0]+i.w)
            x1=true,rt=build_n(i.v);
        else if(!x2&&Mx1[rtx][1]==Mx1[i.v][0]+i.w)
            x2=true,rt=build_n(i.v);
    }
    imp[rt]=true;
    dfs(rt,Mx1);Siz=build_f(Dia.size(),false);
    Sizr=build_f(Dia.size(),true);Siz.insert(Siz.begin(),0);
    Sizr.insert(Sizr.begin(),0);
    dfs(Dia.back(),Mx2,0,false);
    return rt;
}
void scan_graph(istream&is){
    int u,v,w;is>>u>>v>>w;Es[{u,v}]=w;Es[{v,u}]=w;
    G[u].push_back({v,w});G[v].push_back({u,w});
}
vector<lint> init(int n,vector<lint>&siz,
    vector<vector<lint>> mx,bool rev){
    vector<lint> D(n);
    if(rev) rever(Dia);
    cir(i,1,n){
        D[i]=max(D[i-1],mx[Dia[i-1]][1]+siz[i-1]);
    }
    if(rev) rever(Dia),rever(D);
    return D;
}
const lint _inf=1e18+7;
lint run(int n){
    lint ans=Siz.back();
    auto x1=init(Siz.size(),Siz,Mx1,false),
        x2=init(Siz.size(),Sizr,Mx2,true);
    cir(i,0,n-1){
        auto Gx=upper_bound(Siz.begin(),Siz.end(),x1[i+1]/2+(x1[i+1]&1));
        auto Gk=upper_bound(Sizr.begin(),Sizr.end(),x2[i]/2+(x2[i]&1));
        auto gx1=Gx,gk1=Gk;
        if(gx1!=Siz.begin()) --gx1;
        if(gk1!=Sizr.begin()) --gk1;
        auto xf=x1[i+1],xs=x2[i];
        ans=min(ans,max({min(max(xf-*Gx,*Gx),max(xf-*gx1,*gx1))+
            min(max(xs-*Gk,*Gk),max(xs-*gk1,*gk1))+Es[{Dia[i],Dia[i+1]}],xf,xs}));
    }
    return ans;
}
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n;cin>>n;res(G);res(Mx1);
    res(imp);res(Siz);res(Mx2);
    cir(i,0,n-1) scan_graph(cin);
    build(n);
    cout<<run(Siz.size())<<'\n';
    return 0;
}