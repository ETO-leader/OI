#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
using VI=vector<lint>;
struct edge{int v,id;lint w;};
struct msg{
    string s;int id;
    msg(string sx):s(sx),id(-1){}
};
vector<vector<edge>> G;
VI stc,stw,vis,cirn;
basic_string<lint> lst,lstw;
pair<int,lint> dfs(int u,int rt=-1,int f=0){
    auto res=pair(u,(lint)(0));vis[u]=1;
    for(auto&[v,id,w]:G[u]) if(v!=f){
        if(cirn[v]&&v!=rt) continue;
        auto dx=dfs(v,rt,u);
        dx.second+=w;
        if(dx.second>res.second){
            res=dx;
        }
    }
    return res;
}
void findcir(int u,int fid=-1){
    stc.push_back(u);
    vis[u]=-1;
    for(auto&[v,id,w]:G[u]) if(id!=fid){
        stw.push_back(w);
        try{
            if(vis[v]<0){
                throw (string)("circle");
            }
            findcir(v,id);
            stw.pop_back();
        }catch(string){
            lst.clear();lstw.clear();
            int ltp=-1;
            while(ltp!=v){
                lst.push_back(ltp=stc.back());
                stc.pop_back();
                lstw.push_back(stw.back());
                stw.pop_back();
                cirn[ltp]=true;
            }
            stc.clear();stw.clear();
            throw msg("succeed");
        }
    }
    vis[u]=1;stc.pop_back();
}
auto solve(int u){
    try{
        findcir(u);
        return (lint)(0);
    }catch(msg){}
    lint res=0;
    basic_string<lint> sizs;
    for(auto&i:lst){
        auto[p,w]=dfs(i,i);
        sizs.push_back(w);
        res=max(res,dfs(p,i).second);
    }
    const int sz=lst.size();
    lst+=lst;lstw+=lstw;sizs+=sizs;
    VI dist(sz<<1);
    cir(i,0,sz<<1){
        dist[i]=(i?dist[i-1]:0)+lstw[i];
    }
    auto dst=[&](int l,int r){
        return dist[r]-dist[l];
    };
    [&](){
        deque<int> q;
        cir(i,0,sz<<1){
            while((!q.empty())&&i-q.front()>sz-1)
                q.pop_front();
            lint ins=0;
            if(!q.empty()){
                ins=sizs[i]+sizs[q.front()]
                    +dst(q.front(),i);
            }else{
                ins=sizs[i];
            }
            res=max(res,ins);
            while((!q.empty())&&sizs[q.back()]+
                dst(q.back(),i)<sizs[i])
                q.pop_back();
            q.push_back(i);
        }
    }();
    return res;
}
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n;cin>>n;G.resize(n+1);
    vis.resize(n+1);cirn.resize(n+1);
    cir(i,1,n+1){
        int f,w;cin>>f>>w;
        G[f].push_back({i,i,w});
        G[i].push_back({f,i,w});
    }
    lint ans=0;
    cir(i,1,n+1) if(!vis[i]) ans+=solve(i);
    cout<<ans<<'\n';
    return 0;
}
