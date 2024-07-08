#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using db=long double;
struct Point{
    db x,y;
    db operator+(const Point&P) const{
        return sqrt((x-P.x)*(x-P.x)+(y-P.y)*(y-P.y));
    }
};
vector<vector<db>> Dis;
struct edgeG{int u;db w;};   //For the Graph
struct edgeM{int u,v;db w;}; //For the MST
vector<vector<edgeG>> Gr;
void dfs(int u,int f,db di,vector<int>&visn){
    for(auto&i:visn) Dis[i][u]=Dis[u][i]=max(Dis[i][f],di);
    visn.push_back(u);
    for(auto&i:Gr[u]) if(i.u!=f) dfs(i.u,u,i.w,visn);
}
template<typename T>
struct dsu{
    vector<T> Fa;
    dsu(T _sz):Fa(_sz){iota(Fa.begin(),Fa.end(),0);}
    T findset(T x){return x==Fa[x]?x:(Fa[x]=findset(Fa[x]));}
    void merge(T a,T b){Fa[findset(a)]=findset(b);}
};
db build(int n,vector<edgeM>&G){
    Gr.clear();Dis.clear();
    Gr.resize(n);Dis.assign(n,vector<db>(n));
    sort(G.begin(),G.end(),[](edgeM&e1,edgeM&e2){return e1.w<e2.w;});
    int k=n-1;dsu<int> ds(n);db sz=0;
    for(auto&i:G){
        if(ds.findset(i.u)==ds.findset(i.v)) continue;
        ds.merge(i.u,i.v);sz+=i.w;
        Gr[i.u].push_back({i.v,i.w}),Gr[i.v].push_back({i.u,i.w});
        if(!(--k)) break;
    }
    return sz;
}
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int T;cin>>T;
    while(T--){
        int n;cin>>n;vector<edgeM> G;
        vector<Point> C(n);vector<int> P(n),vn;
        cir(i,0,n){
            cin>>C[i].x>>C[i].y>>P[i];
            cir(j,0,i) G.push_back({i,j,C[i]+C[j]});
        }
        auto mst_sz=build(n,G);
        dfs(0,-1,0,vn);
        db ans=0;
        cir(i,0,n) cir(j,i+1,n) ans=max(ans,(P[i]+P[j])/(mst_sz-Dis[i][j]));
        cout<<fixed<<setprecision(2)<<ans<<endl;
    }
    return 0;
}