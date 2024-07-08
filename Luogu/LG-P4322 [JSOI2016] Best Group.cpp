#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using db=long double;
using VD=vector<db>;
constexpr db _inf=1e18;
vector<vector<int>> G;
vector<VD> D;
vector<int> siz;
VD s,p;
int dfs(int u,db mid,int f=-1){
    int res=1;
    D[u][1]=p[u]-s[u]*mid;
    for(auto&i:G[u]) if(i!=f){
        int d=dfs(i,mid,u);
        for(int w=res;~w;--w){
            cir(x,0,d+1){
                D[u][w+x]=max(D[u][w+x],
                    D[u][w]+D[i][x]);
            }
        }
        res+=d;
    }
    return siz[u]=res;
}
auto chk(db mid,int k){
    dfs(0,mid);
    bool res=(D[0][k+1]>0);
    cir(i,0,D.size()) cir(x,0,siz[i]+1)
        D[i][x]=-_inf; 
    return res;
}
void init(int n){
    G.resize(n+1);s.resize(n+1);
    D.assign(n+1,VD(n+2,-_inf));
    p.resize(n+1);siz.resize(n+1);
}
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int k,n;cin>>k>>n;init(n);
    cir(i,1,n+1){
        int f;cin>>s[i]>>p[i]>>f;
        G[f].push_back(i);
    }
    db l=0,r=1e4+7,ans=-1;
    cir(i,0,64){
        const auto mid=(l+r)/2;
        chk(mid,k)?((l=mid),
            (ans=mid)):(r=mid);
    }
    cout<<fixed<<
        setprecision(3)<<ans<<'\n';
    return 0;
}
