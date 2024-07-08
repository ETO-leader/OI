#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using db=long double;
struct edgeM{int u;db w;};
struct edgeG{
    int u,v;db w;
    bool operator<(const edgeG&eG) const{
        return w<eG.w;
    }
};
vector<vector<edgeM>> Gr;
vector<vector<db>> Dis;
struct dsu{
    vector<int> Fa;
    dsu(int _sz):Fa(_sz){iota(Fa.begin(),Fa.end(),0);}
    int findset(int x){return Fa[x]==x?x:(Fa[x]=findset(Fa[x]));}
    void merge(int x,int y){Fa[findset(x)]=findset(y);}
};
void dfs(int u,int f,db dx,vector<int>&ved){
    for(auto&i:ved) Dis[u][i]=Dis[i][u]=max(Dis[i][f],dx);
    ved.push_back(u);
    for(auto&i:Gr[u]) if(i.u!=f) dfs(i.u,u,i.w,ved);
}
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int T;cin>>T;
    while(T--){
        int n;cin>>n;Gr.clear();
        vector<edgeG> G;Gr.resize(n);
        dsu ds(n);vector<int> xi(n),yi(n),p(n);
        Dis.assign(n,vector<db>(n));
        auto squ=[](db x){return x*x;};
        cir(i,0,n){
            cin>>xi[i]>>yi[i]>>p[i];
            cir(j,0,i) G.push_back({i,j,sqrt(
                squ(xi[i]-xi[j])+squ(yi[i]-yi[j]))});
        }
        sort(G.begin(),G.end());int k=n-1;
        db mst_sz=0;
        for(auto&i:G){
            if(ds.findset(i.u)==ds.findset(i.v)) continue;
            ds.merge(i.u,i.v);mst_sz+=i.w;
            Gr[i.u].push_back({i.v,i.w}),Gr[i.v].push_back({i.u,i.w});
            if(!(--k)) break;
        }
        vector<int> vec;dfs(0,-1,0,vec);
        db ans=0;
        cir(i,0,n) cir(j,i+1,n) ans=max(ans,(p[i]+p[j])/(mst_sz-Dis[i][j]));
        cout<<fixed<<setprecision(2)<<ans<<endl;
    }
    return 0;
}