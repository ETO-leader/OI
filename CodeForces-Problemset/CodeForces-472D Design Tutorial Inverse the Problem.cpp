#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;                //Bigger size
struct edgeM{int u;lint w;};         //Edge in MST
struct edgeG{int u,v;lint w;};       //Edge in graph. Remember use lambda in sort
vector<vector<edgeM>> M;             //MST
template<typename T>
struct dsu{
    vector<T> Fa;
    dsu(T _sz):Fa(_sz){iota(Fa.begin(),Fa.end(),0);}
    T findset(T x){return x==Fa[x]?x:(Fa[x]=findset(Fa[x]));}
    void merge(T x,T y){Fa[findset(x)]=findset(y);}
};
void build(int n,vector<edgeG>&G){   //build MST
    M.resize(n);
    sort(G.begin(),G.end(),[](edgeG&e1,edgeG&e2){return e1.w<e2.w;});
    int k=n-1;dsu<int> ds(n);
    for(auto&i:G){
        if(ds.findset(i.u)==ds.findset(i.v)) continue;
        ds.merge(i.u,i.v);
        M[i.u].push_back({i.v,i.w});M[i.v].push_back({i.u,i.w});
        if(!(--k)) break;
    }
}
vector<vector<lint>> Dis,Given;
void Fail(){cout<<"NO"<<endl;exit(0);} //Error - Exit
void dfs(int u,int f,lint w,vector<int>&ved){
    //Now Node;Father;Distance of pathern edge;vised node
    for(auto&i:ved){
        Dis[u][i]=Dis[i][u]=Dis[f][i]+w;
        if(Dis[u][i]!=Given[u][i]||Dis[i][u]!=Given[i][u]) Fail();
        //Wrong : Exit
    }
    ved.push_back(u);
    for(auto&i:M[u]) if(i.u!=f) dfs(i.u,u,i.w,ved);
}
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n;cin>>n;Given.assign(n,vector<lint>(n));
    Dis.assign(n,vector<lint>(n));vector<edgeG> Gr;
    cir(i,0,n) cir(j,0,n){
        cin>>Given[i][j];Gr.push_back({i,j,Given[i][j]});
        if((i==j&&Given[i][j])||(i>j&&Given[i][j]!=Given[j][i])
            ||(i!=j&&(!Given[i][j]))) Fail();
    }
    vector<int> ved;
    build(n,Gr);dfs(0,-1,0,ved);
    cout<<"YES"<<endl;
    return 0;
}