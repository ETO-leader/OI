#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
#define NAGATIVE {cout<<"YES\n";\
    PutCircle(f,F,n);exit(0);}
using lint=long long;
struct edge{int v;lint w;};
vector<vector<edge>> G;
vector<int> vis,visx,vx;
const lint _inf=1e18+7;
void PutCircle(int u,vector<lint>&F,int n){
    stack<int> st;unordered_set<int> ust;
    st.push(u);u=F[u];
    while(!ust.count(u)) ust.insert(u),st.push(u),u=F[u];
    cout<<u<<' ';
    while(st.top()!=u) cout<<st.top()<<' ',st.pop();
    cout<<u;
}
vector<lint> SPFA(int u){
    vector<lint> vist(G.size()),D(G.size(),_inf),F(G.size());
    int n=G.size()-1;D[u]=0;F[u]=1;
    queue<int> q;q.push(u);
    while(!q.empty()){
        auto f=q.front();q.pop();
        assert(F[f]);
        visx[f]=true;
        if(++vist[f]>n+1) NAGATIVE;
        for(auto&i:G[f]){
            if(D[f]+i.w<D[i.v]&&vist[i.v]<=n+1)
                q.push(i.v),D[i.v]=D[f]+i.w,F[i.v]=f;
        }
    }
    return D;
}
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n,m;cin>>n>>m;visx.resize(n+1);
    G.resize(n+1);vis.resize(n+1);
    cir(i,0,m){
        int u,v,w;cin>>u>>v>>w;
        G[u].push_back({v,w});
    }
    cir(i,1,n+1) if(!visx[i]) SPFA(i);
    cout<<"NO\n";
    return 0;
}