#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
template<typename T>
struct dsu{
    vector<T> F;
    dsu(T _n):F(_n){iota(F.begin(),F.end(),0);}
    int findset(T x){return F[x]==x?x:F[x]=findset(F[x]);}
    void merge(T u,T v){F[findset(u)]=findset(v);}
    bool same(T u,T v){return findset(u)==findset(v);}
};
vector<int> mx{-1,0},my{0,-1};
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n,m;cin>>n>>m;
    auto grid=[&n,&m](int x,int y){
        return n>m?x*n+y:y*m+x;};
    vector<string> G(n);dsu<int> ds(max(n,m)*max(n,m));
    cir(i,0,n){
        cin>>G[i];
        cir(j,0,m){
            if(G[i][j]=='#') continue;
            cir(k,0,2){
                int nx=i+mx[k],ny=j+my[k];
                if(nx<0||nx>=n||ny<0||ny>=m) continue;
                if(G[nx][ny]!='#'&&!ds.same(grid(i,j),grid(nx,ny)))
                    ds.merge(grid(i,j),grid(nx,ny));
            }
        }
    }
    int ans=0;
    cir(i,0,n) cir(j,0,m)
        ans+=(G[i][j]!='#'&&ds.findset(grid(i,j))==grid(i,j));
    cout<<ans<<'\n';
    return 0;
}