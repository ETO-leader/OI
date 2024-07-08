#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
const int MOD=998244353;
lint pow2(int p){
    lint r=1,x=2;
    while(p){
        if(p&1) (r*=x)%=MOD;
        (x*=x)%=MOD;p>>=1;
    }
    return r;
}
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int T;cin>>T;
    while(T--){
        int n,m;cin>>n>>m;
        vector<vector<int>> G(n+1);
        vector<int> col(n+1),vis(n+1);
        cir(i,0,m){
            int u,v;cin>>u>>v;
            G[u].push_back(v);G[v].push_back(u);
        }
        cout<<[&](){
            int cnx=0,siz=0;
            function<bool(int,int)> f=[&](int u,int c){
                col[u]=c;vis[u]=true;++siz;
                for(auto&i:G[u]){
                    if(vis[i]&&col[i]!=(c^1)||(!vis[i]
                        &&(!f(i,c^1)))) return false;
                }
                cnx+=(c==1);
                return true;
            };
            lint res=1;
            cir(i,1,n+1) if(!vis[i]){
                cnx=0,siz=0;
                if(!f(i,0)) return 0LL;
                (res*=(pow2(cnx)+pow2(siz-cnx)))%=MOD;
            }
            return res;
        }()<<'\n';
    }
    return 0;
}
