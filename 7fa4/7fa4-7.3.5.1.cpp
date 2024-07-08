#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using VI=vector<int>;
using lint=long long;
const int _inf=1e9+7;
struct edge{int v,w;};
vector<vector<edge>> G,T;
vector<VI> up,upw;int ht;
VI hx,tin,tout;
void dfs(int u,int&cnx,int f=0,int wx=0){
    up[u][0]=f;upw[u][0]=wx;
    hx[u]=hx[f]+1;tin[u]=++cnx;
    cir(i,1,ht){
        int upx=up[u][i-1];
        up[u][i]=up[upx][i-1];
        upw[u][i]=min(upw[u][i-1],upw[upx][i-1]);
    }
    for(auto&[v,w]:G[u])
        if(v!=f) dfs(v,cnx,u,w);
    tout[u]=cnx;
}
int lca(int u,int v){
    if(u==v) return u;
    if(hx[u]<hx[v]) swap(u,v);
    cir(i,0,ht) if((1<<i)&(hx[u]-hx[v])) u=up[u][i];
    if(u==v) return u;
    for(int i=ht-1;~i;--i) if(up[u][i]!=up[v][i])
        u=up[u][i],v=up[v][i];
    return up[u][0];
}
bool isancestor(int u,int v){
    return tin[u]<=tin[v]&&tout[v]<=tout[u];
}
int distance(int u,int v){
    assert(hx[u]>hx[v]);
    int res=_inf;
    for(int i=ht-1;~i;--i){
        if(isancestor(v,up[u][i]))
            res=min(res,upw[u][i]),u=up[u][i];
    }
    return res;
}
lint redfs(int u,VI&impx,int f=0){
    lint res=0;
    if(impx[u]) return _inf;
    for(auto&[v,w]:T[u])
        res+=min<lint>(w,redfs(v,impx,u));
    return res;
}
void resize_all(int n){
    G.resize(n+1);T.resize(n+1);
    tin.resize(n+1);tout.resize(n+1);
    hx.resize(n+1);ht=log2(n)+2;
    up.assign(n+1,VI(ht));
    upw.assign(n+1,VI(ht));
}
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n;cin>>n;resize_all(n);
    cir(i,0,n-1){
        int u,v,w;cin>>u>>v>>w;
        G[u].push_back({v,w});
        G[v].push_back({u,w});
    }
    [&](){int cnx=0;dfs(1,cnx);}();
    int m;cin>>m;VI fx(n+1),apx(n+1),impx(n+1);
    cir(i,0,m){
        int k;cin>>k;VI nd(k),imp;
        for(auto&i:nd) cin>>i,impx[i]=true;
        if(k==1){
            cout<<distance(nd[0],1)<<'\n';
            continue;
        }
        sort(nd.begin(),nd.end(),
            [&](int a,int b){return tin[a]<tin[b];});
        imp=nd;
        int ux=[&](){
            stack<int> st;
            int res=-1,hres=_inf;
            [&](){
                const int l=lca(nd[0],nd[1]);
                res=l,hres=hx[l];
                if(l!=nd[0]) fx[nd[0]]=l;
                st.push(l);st.push(nd[1]);
                imp.push_back(l);
            }();
            cir(i,1,k-1){
                const int l=lca(nd[i],nd[i+1]);
                imp.push_back(l);
                if(hx[l]<hres) hres=hx[l],res=l;
                int tp=-1;
                while((!st.empty())&&
                    (!isancestor(st.top(),l))){
                    tp=st.top();st.pop();
                    if(st.empty()) break;
                    if(st.top()!=tp) fx[tp]=st.top();
                }
                if(tp!=-1&&tp!=l) fx[tp]=l;
                st.push(l);st.push(nd[i+1]);
            }
            while(!st.empty()){
                auto tp=st.top();st.pop();
                if(st.empty()) break;
                if(st.top()!=tp) fx[tp]=st.top();
            }
            return res;
        }();
        if(ux!=1) imp.push_back(1),fx[ux]=1;
        for(auto&i:imp){
            if(apx[i]) continue;
            apx[i]=true;
            if(fx[i]){
                T[fx[i]].push_back({i,distance(i,fx[i])});
            }
        }
        cout<<redfs(1,impx)<<'\n';
        for(auto&i:imp) fx[i]=apx[i]=0,T[i].clear();
        for(auto&i:nd) impx[i]=false;
    }
    return 0;
}
