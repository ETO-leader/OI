#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
const int MM=1e5+7;
vector<vector<int>> G;
vector<lint> W(MM),A(MM),v,Mul(MM),Add(MM),vis(MM),Op(MM),D(MM);
vector<int> tops;
const int MOD=998244353;
auto dfs(int u){
    auto &m=Mul[u];
    if(vis[u]) return m;
    vis[u]=true,m=(Op[u]==2?A[u]:1);
    if(Op[u]==3) for(auto&i:G[u]) (m*=dfs(i))%=MOD;
    tops.push_back(u);
    return m;
}
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n,m;cin>>n;v.resize(n+1);
    cir(i,1,n+1) cin>>v[i];Op[0]=3;
    cin>>m;G.resize(m+1);
    cir(i,1,m+1){
        cin>>Op[i];int c,k;
        switch(Op[i]){
            case 1:cin>>W[i]>>A[i];break;
            case 2:cin>>A[i];break;
            default:
                cin>>c;
                while(c--) cin>>k,G[i].push_back(k);
                break;
        }
    }
    int q,k;cin>>q;
    while(q--) cin>>k,G[0].push_back(k);
    dfs(0);D[0]=1;
    reverse(tops.begin(),tops.end());
    for(auto&i:tops){
        if(Op[i]==1){
            (Add[W[i]]+=A[i]*D[i])%=MOD;
        }else{
            for(int j=G[i].size()-1;j+1;--j){
                auto&x=G[i][j];
                (D[x]+=D[i])%=MOD;(D[i]*=Mul[x])%=MOD;
            }
        }
    }
    cir(i,1,n+1) cout<<Mul[i]<<' '<<(Add[i]+D[0]*v[i])%MOD<<' ';
    cout<<endl;
	return 0;
}