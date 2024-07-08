#include<bits/stdc++.h>
#define cir(i,a,b) for(auto i=a;i<b;++i)
using namespace std;
ifstream fcin("shortest.in");
ofstream fcout("shortest.out");
class fileio{
public:
    ~fileio(){
        fcin.close();fcout.close();
    }
} use_fileio;
using VI=vector<int>;
using VB=vector<bool>;
static constexpr int _inf=1e9+7;
vector<VI> rg;
VI fs,snx,nxtk;
auto fndcir(int u,VI&vis,VB&oc){
    if(vis[u]==-1) return u;
    if(vis[u]) return -1;
    vis[u]=-1;
    auto d=fndcir(snx[u],vis,oc);
    vis[u]=1;
    if(d<0) return -1;
    else return oc[u]=true,(d==u?-1:d);
}
void dfstr(int u,VB&oc,VB&vis){
    if(oc[u]||vis[u]) return;
    vis[u]=true;
    dfstr(snx[u],oc,vis);
}
int dfs(int u,int&cnx,const int k,VB&oc){
    for(auto&i:rg[u]) if(!oc[i]){
        fs[u]=max(fs[u],dfs(i,cnx,k,oc)-1);
    }
    if(!fs[u]) ++cnx,fs[u]=k-1;
    //clog<<u<<' '<<fs[u]<<'\n';      
    return fs[u];
}
void dfsc(int u,VB&vis,queue<int>&q,
    const int k,int fsum=0){
    if(vis[u]) return;
    vis[u]=true;
    fsum=max(fsum,snx[u]);
    if(!fsum) while(q.size()>k)
        nxtk[q.front()]=u,q.pop();
    q.push(u);
    dfsc(snx[u],vis,q,k,fsum-1);
}
auto jump(int u){
    int res=0;const int lu=u;
    return [&](){
        while(nxtk[u]>-1)
            u=nxtk[u],++res;
        return res+(snx[u]!=lu);
    }();
}
int main(){
    ios::sync_with_stdio(false),fcin.tie(0);
    int n,k,ans=0;fcin>>n>>k;
    snx.resize(n+1);
    rg.resize(n+1);nxtk.resize(n+1,-1);
    cir(i,0,n){
        int u,v;fcin>>u>>v;
        snx[u]=v;
        rg[v].push_back(u);
    }
    //Init Graph
    auto iscir=[&](){
        VI vis(n+1);VB oc(n+1);
        cir(i,1,n+1) fndcir(i,vis,oc);
        return oc;
    }();
    //Build trees and init the array fs
    [&](){
        VB vis(n+1);fs.resize(n+1);
        cir(u,1,n+1) if(!iscir[u]){
            dfstr(u,iscir,vis);
        }
        fs[1]=k;
        cir(u,1,n+1) if(iscir[u]){
            if(rg[u].size()>1){
                dfs(u,ans,k,iscir);
            }
        }
    }();
    //Process Circles
    fcout<<ans+[&](){
        int ansx=0;
        VB vis(n+1);
        cir(u,1,n+1){
            if(iscir[u]&&(!vis[u])&&fs[u]){
                //clog<<u<<":"<<fs.at(u)<<'\n';
                [&](){
                    queue<int> q;
                    dfsc(u,vis,q,k);
                }();
                int ansi=_inf;
                const int fsu=fs[u];
                cir(i,0,fsu){
                    clog<<u<<' '<<jump(u)<<'\n';
                    ansi=min(ansi,jump(u)),u=snx[u];
                }
                ansx+=ansi; 
            }
        }
        //cir(u,1,n+1){
        //    if(iscir[u]&&(!vis[u])&&(!fs[u])){
        //        ++ansx;fs[u]=k-1;
        //        [&](){
        //            queue<int> q;
        //            dfsc(u,vis,q,k);
        //        }();
        //        int ansi=_inf;
        //        const int fsu=fs[u];
        //        cir(i,0,fsu){
        //            //clog<<u<<' '<<jump(u)<<'\n';
        //            ansi=min(ansi,jump(u)),u=snx[u];
        //        }
        //        ansx+=ansi;
        //    }
        //}
        return ansx;
    }()<<'\n';
    return 0;
}
