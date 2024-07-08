#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
template<typename T>
class sparsetable{
private:
    vector<vector<T>> st;
    vector<int> lg2;
    int ht;
    void init(const vector<T>&v){
        int n=v.size();ht=log2(n)+2;
        st.assign(ht,vector<T>(n));
        lg2.resize(1<<ht);
        cir(i,0,ht) cir(j,(1<<i),(1<<i+1)) lg2[j]=i;
        cir(i,0,n) st[0][i]=v[i];
        cir(j,1,ht) cir(i,0,(n-(1<<(j-1))))
            st[j][i]=min(st[j-1][i],st[j-1][i+(1<<(j-1))]);
    }
public:
    T operator()(int l,int r) const{
        int lg=lg2[r-l+1];
        return min(st[lg][l],st[lg][r-(1<<lg)+1]);
    }
    sparsetable(){}
    sparsetable(const vector<T>&v){init(v);}
};
template<typename T>
class graph{
private:
    struct edge{int v;T w;};
    vector<vector<edge>> G;
    vector<T> w;vector<int> eur;
    struct nodeqry{
        int h,u;
        bool operator<(const nodeqry&x) const{
            return h<x.h;
        }
    };
    vector<nodeqry> imx;
    sparsetable<nodeqry> st;
public:
    void dfs(int u,int hx=0,T wx=0,int f=0){
        w[u]=wx;eur[u]=imx.size();
        imx.push_back({hx,u});
        for(auto&[v,wi]:G[u]) if(v!=f)
            dfs(v,hx+1,wx+wi,u),imx.push_back({hx,u});
    }
    T distance(int u,int v){
        if(eur[u]>eur[v]) swap(u,v);
        return w[u]+w[v]-w[st(eur[u],eur[v]).u]*2;
    }
    void insert(int u,int v,T w){
        G[u].push_back({v,w});
        G[v].push_back({u,w});
    }
    T operator()(int u,int x){return distance(u,x);}
    void resize(int n){
        G.resize(n);w.resize(n);
        imx.clear();eur.resize(n);
    }
    void restart(){
        dfs(1);
        st=sparsetable<nodeqry>(imx);
    }
};
graph<lint> a,b,c;
vector<int> vis;
int getcld(int u,int n,lint&ans){
    lint mx=-1,p=0;
    cir(i,1,n+1){
        lint wi=a(u,i)+b(u,i)+c(u,i);
        if(vis[i]){ans=max(ans,wi);continue;}
        if(wi>mx) (mx=wi),(p=i);
    }
    ans=max(ans,mx);
    return p;
}
mt19937 rnd(110735);
lint runx(int runt,int n){
    int u=rnd()%n+1;lint res=0;
    cir(i,0,runt){
        if(vis[u=getcld(u,n,res)]) break;
        vis[u]=true;
    }
    return res;
}
void readtree(graph<lint>&x,int n){
    x.resize(n+1);
    cir(i,0,n-1){
        int u,v;lint w;cin>>u>>v>>w;
        x.insert(u,v,w);
    }
    x.restart();
}
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n;cin>>n;readtree(a,n);
    readtree(b,n);readtree(c,n);
    vis.resize(n+1);
    int x=a(1,1)+b(4,5)+c(1,4);
    const clock_t srtclc=clock();
    auto getclock=[&](){
        return (double)(clock()-srtclc)/
            CLOCKS_PER_SEC;
    };
    lint ans=0;
    while(true){
        ans=max(ans,runx(3,n));
        if(getclock()>3.70) break;
    }
    cout<<ans<<'\n';
    return 0;
}