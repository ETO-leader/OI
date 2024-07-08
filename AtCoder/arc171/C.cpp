#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
using VI=vector<lint>;
static constexpr auto MOD=998244353;
vector<VI> gr;
vector<array<lint,2>> f;
auto dfs(int u,int fr=0)->void{
    vector<array<lint,2>> fx(gr[u].size()+1);
    int cnt=(bool)(fr);
    fx[0][0]=1;fx[1][1]=(bool)(fr);
    for(auto&i:gr[u]) if(i!=fr){
        dfs(i,u);++cnt;
        const auto lf=fx;
        fill(fx.begin(),fx.end(),
            array<lint,2>({0,0}));
        cir(x,0,cnt+1){
            (fx[x][0]+=lf[x][0]*f[i][0])%=MOD;
            (fx[x][1]+=lf[x][1]*f[i][0])%=MOD;
            if(x){
                (fx[x][0]+=lf[x-1][0]*x*f[i][1])%=MOD;
                (fx[x][1]+=lf[x-1][1]*x*f[i][1])%=MOD;
            }
        }
    }
    for(auto&x:fx){
        (f[u][0]+=x[0])%=MOD;
        (f[u][1]+=x[1])%=MOD;
    }
}
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n;cin>>n;gr.resize(n+1);f.resize(n+1);
    cir(i,0,n-1){
        int u,v;cin>>u>>v;
        gr[u].push_back(v);gr[v].push_back(u);
    }
    dfs(1);
    cout<<f[1][0]<<'\n';
    return 0;
}
