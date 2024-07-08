#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
struct edge{int v,w;};
vector<vector<edge>> G;
vector<vector<int>> Mx,xm;
vector<int> Ans,imp,L,xf;
void dfs(int u,int f=0){
    Mx[u].clear();
    if(imp[u]) L.push_back(u);
    for(auto&i:G[u]) if(i.v!=f)
        dfs(i.v,u),Mx[u].push_back(Mx[i.v][0]+i.w);
    while(Mx[u].size()<2) Mx[u].push_back(0);
    sort(Mx[u].begin(),Mx[u].end(),greater<int>());
}
void dfsx(int u,int rt,int w=0,int f=0){
    if(u!=rt) xf[u]=xm[f][0]-w==xm[u][0]?xm[f][1]+w:xm[f][0]+w;
    if(u!=rt) xm[u].push_back(xf[u]);
    sort(xm[u].begin(),xm[u].end(),greater<int>());
    for(auto&i:G[u]) if(i.v!=f) dfsx(i.v,rt,i.w,u);
}
int init(int u,int f=0){
    imp[u]=true;
    for(auto&i:G[u]) if(i.v!=f){
        if(Mx[i.v][0]==Mx[u][0]-i.w) return init(i.v,u);
    }
    return u;
}
const int _inf=1e9+7;
template<typename T>
auto getpair(T&a,T&b){return make_pair(min(a,b),max(a,b));}
map<pair<int,int>,int> E;
int solve(int s){
    int ans=Mx[L[0]][0],l=0,r=1,cnt=0;
    multiset<int,greater<int>> mx;
    mx.insert(Mx[L[0]][0]);mx.insert(xf[L[0]]);
    mx.insert(Mx[L[r-1]][1]);
    while(r<L.size()){
        mx.erase(mx.find(Mx[L[r-1]][0]));
        mx.insert(Mx[L[r]][0]),mx.insert(Mx[L[r]][1]);
        cnt+=E[getpair(L[r-1],L[r])];
        while(cnt>s){
            if(l+1==L.size()) break;
            mx.erase(mx.find(xf[L[l]]));
            mx.erase(mx.find(Mx[L[l]][1]));
            mx.insert(xf[L[l+1]]);
            cnt-=E[getpair(L[l],L[l+1])];++l;
        }
        ans=min(ans,*mx.begin());
        ++r;
    }
    return ans;
}
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n,s;cin>>n>>s;Mx.resize(n+1);
    G.resize(n+1);Ans.resize(n+1);
    imp.resize(n+1);xf.resize(n+1);
    cir(i,0,n-1){
        int u,v,w;cin>>u>>v>>w;
        G[u].push_back({v,w});G[v].push_back({u,w});
        E[getpair(u,v)]=w;
    }
    dfs(1);int rtx=0,mx=0;
    cir(i,1,n+1) mx=max(mx,Mx[i][0]+Mx[i][1]);
    cir(i,1,n+1) if(Mx[i][0]+Mx[i][1]==mx){rtx=i;break;}
    int x1=false,x2=false,rt=0;imp[rtx]=true;
    for(auto&i:G[rtx]){
        if(!x1&&Mx[rtx][0]==Mx[i.v][0]+i.w)
            x1=true,rt=init(i.v,1);
        else if(!x2&&Mx[rtx][1]==Mx[i.v][0]+i.w)
            x2=true,rt=init(i.v,1);
    }
    dfs(rt);xm=Mx;dfsx(rt,rt);
    cout<<solve(s)<<'\n';
    return 0;
}