#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using VI=vector<int>;
void abort(string str,int exitcode){
    exit(((cout<<str<<'\n'),exitcode));
}
vector<VI> G;
VI s,mtag,L,ans;
int dfs(int u,int f=0){
    VI vx(1);int ew=0;
    for(auto&i:G[u]) if(i!=f){
        const int d=dfs(i,u);
        vx.push_back(d);
        if(ew<d) ew=d,s[u]=i;
    }
    sort(vx.begin(),vx.end(),greater<int>());
    if(f&&vx.size()>1&&vx[1]>1) abort("No",0);
    if((!f)&&vx.size()>2&&vx[2]>1) abort("No",0);
    mtag[u]=vx.front()>0;
    return vx.front()+1;
}
unordered_set<int> lcnt;
void lineup(int u,int f){
    for(auto&i:G[u]) if(i!=f) if(!lcnt.count(i))
        ans.push_back(i);
}
void reid(int pos,bool coltag=true,int f=0){
    const int u=L[pos];
    if(coltag) ans.push_back(u);
    else lineup(u,f);
    if(pos<L.size()-1) reid(pos+1,coltag^1,u);
    if(!coltag) ans.push_back(u);
    else lineup(u,f);
}
VI initline(int u){
    VI res(1,u);int lsu=-1;
    while(s[u]){
        lsu=u;u=s[u];res.push_back(u);
    }
    if(!G[u].empty()) for(auto&i:G[u]) if(i!=lsu){
        res.push_back(i);break;
    }
    return res;
}
void reset(int n){
    G.resize(n+1);s.resize(n+1);mtag.resize(n+1);
}
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n;cin>>n;reset(n);
    cir(i,0,n-1){
        int u,v;cin>>u>>v;
        G[u].push_back(v);G[v].push_back(u);
    }
    int root=1;
    cir(i,1,n+1) if(G[i].size()>1) root=i;
    dfs(root);
    vector<VI> rx;
    for(auto&i:G[root]) if(mtag[i]&&n!=2)
        rx.push_back(initline(i));
    if(!rx.empty()){
        reverse(rx[0].begin(),rx[0].end());
        L=rx[0];
    }
    L.push_back(root);
    if(rx.size()>1) for(auto&i:rx[1]){
        L.push_back(i);
    }else for(auto&i:G[root]) if(!mtag[i]){
        L.push_back(i);break;
    }
    for(auto&i:L) lcnt.insert(i);
    reid(0);
    cout<<"Yes\n";
    for(auto&i:ans) cout<<i<<' ';
    cout<<'\n';
    return 0;
}
