#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
static constexpr auto MOD=10007;
static constexpr auto _inf=(int)(1e9+7);
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int n,m,k;cin>>n>>m>>k;
    vector<vector<int>> vw(n,vector<int>(n,-_inf));
    string s;getline(cin,s);
    cir(i,0,m){
        getline(cin,s);
        stringstream uin(s);
        int u,v;
        uin>>u>>v;--u;--v;
        char c;
        if(uin>>c){
            if(tolower(c)==c){
                vw[u][v]=-(c-'a'+1);
            }else{
                vw[u][v]=c-'A'+1;
            }
        }else{
            vw[u][v]=0;
        }
    }
    vector<vector<vector<int>>> f(n,vector<vector<int>>(n,vector<int>(k+1)));
    vector<vector<vector<int>>> g(n,vector<vector<int>>(n,vector<int>(k+1)));
    cir(i,0,n) f[i][i][0]=1;
    cir(u,0,n) cir(v,0,n) if(!vw[u][v]) f[u][v][1]=1; 
    cir(w,0,k+1) cir(u,0,n) cir(v,0,n){
        (g[u][v][w]+=f[u][v][w])%=MOD;
        cir(p,0,n) cir(nw,1,w){
            (g[u][v][w]+=g[u][p][w-nw]*f[p][v][nw])%=MOD;
        }
        if(!g[u][v][w]) continue;
        if(w+1<k) cir(x,0,n) if(vw[x][u]>0) cir(y,0,n) if(vw[v][y]==-vw[x][u]) (f[x][y][w+2]+=g[u][v][w])%=MOD;
    }
    vector<vector<int>> h(n,vector<int>(k+1));
    h[0][0]=1;
    auto ans=0;
    cir(w,0,k) cir(u,0,n) cir(v,0,n){
        if(vw[u][v]>0){
            (h[v][w+1]+=h[u][w])%=MOD;
        }
        cir(nw,1,k-w+1) (h[v][w+nw]+=h[u][w]*f[u][v][nw])%=MOD;
    }
    cir(w,0,k+1) (ans+=h[n-1][w])%=MOD;
    cout<<ans<<'\n';
    return 0;
}
