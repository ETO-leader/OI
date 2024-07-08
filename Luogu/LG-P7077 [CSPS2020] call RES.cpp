#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
const int M=1e5+7,MOD=998244353;
vector<lint> Tp(M),Mul(M),Add(M),V(M),P(M),v(M),vis(M),T,D(M);
vector<vector<int>> G;
auto dfs(int u){
    auto&m=Mul[u];
    if(vis[u]) return m;
    vis[u]=true;
    m=(Tp[u]==2?V[u]:1);
    if(Tp[u]==3) for(auto&i:G[u]) (m*=dfs(i))%=MOD;
    T.push_back(u);
    return m;
}
void input(int u){
    cin>>Tp[u];int c,k;
    switch(Tp[u]){
        case 1:cin>>P[u]>>V[u];break;
        case 2:cin>>V[u];break;
        default:
            cin>>c;
            while(c--) cin>>k,G[u].push_back(k);
    }
}
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n,m;cin>>n;
    cir(i,1,n+1) cin>>v[i];
    cin>>m;G.resize(m+1);
    cir(i,1,m+1) input(i);
    int q,x;cin>>q;
    while(q--) cin>>x,G[0].push_back(x);
    Tp[0]=3;D[0]=1;
    dfs(0);reverse(T.begin(),T.end());
    for(auto&i:T){
        if(Tp[i]==1){
            (Add[P[i]]+=V[i]*D[i])%=MOD;
        }else{
            for(int j=G[i].size()-1;j+1;--j){
                auto&g=G[i][j];
                (D[g]+=D[i])%=MOD;(D[i]*=Mul[g])%=MOD;
            }
        }
    }
    cir(i,1,n+1) cout<<(Add[i]+D[0]*v[i])%MOD<<' ';
    cout<<endl;
	return 0;
}