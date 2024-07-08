#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
template<typename T>
struct dsu{
    vector<T> F,siz;
    dsu(T n):F(n),siz(n,1){iota(F.begin(),F.end(),0);}
    T findset(T x){return F[x]==x?x:F[x]=findset(F[x]);}
    void merge(T x,T y){
        x=findset(x),y=findset(y);F[x]=y;siz[y]+=siz[x];
    }
    T set_size(int x){return siz[findset(x)];}
};
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n,m,mx=1,cnt;cin>>n>>m;
    dsu<int> ds(n+1);cnt=n;
    cir(i,0,m){
        int u,v;cin>>u>>v;
        if(ds.findset(u)==ds.findset(v)){
            cout<<cnt<<' '<<mx<<'\n';continue;
        }
        ds.merge(u,v);
        cout<<(--cnt)<<' '<<(mx=max(mx,ds.set_size(u)))<<'\n';
    }
    return 0;
}
