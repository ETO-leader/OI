#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
#define cirr(i,a,b) for(int i=b-1;i>=a;--i)
using namespace std;
using lint=long long;
using VI=vector<lint>;
template<typename T>
class dsu{
private:
    vector<T> F,siz,Mx,Exmx;
    vector<pair<T,T>> ops;
    vector<lint> chgw;
    lint w;
public:
    lint getw(){return w;}
    T findset(int x){return x==F[x]?x:findset(F[x]);}
    T merge(int x,int y){
        x=findset(x),y=findset(y);
        if(x==y){
            ops.push_back({-1,-1});return Mx[x];
        }
        if(siz[y]<siz[x]) swap(x,y);
        w+=1LL*siz[x]*siz[y];
        chgw.push_back(1LL*siz[x]*siz[y]);
        ops.push_back({x,y});siz[y]+=siz[x];
        Exmx.push_back(Mx[y]);Mx[y]=max(Mx[y],Mx[x]);
        return F[x]=y,Mx[y];
    }
    void remoke(){
        if(ops.empty()) return;
        assert(ops.size());
        T x=ops.back().first,y=ops.back().second;
        ops.pop_back();
        if(x<0||y<0) return;
        F[x]=x;siz[y]-=siz[x];
        w-=chgw.back();chgw.pop_back();
        Mx[y]=Exmx.back();Exmx.pop_back();
    }
    dsu(T n):F(n),Mx(n),siz(n,1),w(0){
        iota(F.begin(),F.end(),0);
        iota(Mx.begin(),Mx.end(),0);
    }
};
class trie{
private:
    const int intsiz=31;
    struct edge{int u,v;};
    struct node{
        array<node*,2> s;
        vector<edge> nx;lint w;
        node():w(0){s[0]=s[1]=nullptr;}
    };
    node*movenode(node*u,int g){
        if(u->s[g]==nullptr)
            u->s[g]=new node();
        return u->s[g];
    }
    node*root;dsu<int> ds;
    void dfs(node*u){
        for(auto&[u,v]:u->nx) ds.merge(u,v);
        u->w=ds.getw();
        for(auto s:u->s) if(s!=nullptr) dfs(s);
        for(auto&i:u->nx) ds.remoke();
    }
public:
    void insert_query(int s){
        auto u=root;
        cirr(i,0,intsiz)
            u=movenode(u,(bool)(s&(1<<i)));
    }
    void insert_edge(int k,int s,edge e){
        auto u=root;
        cirr(i,0,intsiz){
            if(k&(1<<i)){
                if(s&(1<<i))
                    movenode(u,1)->nx.push_back(e);
                else
                    movenode(u,0)->nx.push_back(e);
                u=movenode(u,(!(s&(1<<i))));
            }else{
                u=movenode(u,(bool)(s&(1<<i)));
            }
        }
    }
    void reload(){dfs(root);}
    lint calculate_query(int s){
        auto u=root;
        cirr(i,0,intsiz)
            u=movenode(u,(bool)(s&(1<<i)));
        return u->w;
    }
    trie(int _n):ds(_n){root=new node();}
};
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n,m,k;cin>>n>>m>>k;
    trie tr(n);
    cir(i,0,m){
        int u,v,c;cin>>u>>v>>c;
        tr.insert_edge(k,c,{--u,--v});
    }
    int q;cin>>q;VI qr(q);
    for(auto&i:qr){
        cin>>i;tr.insert_query(i);
    }
    tr.reload();
    for(auto&i:qr){
        cout<<tr.calculate_query(i)<<'\n';
    }
    return 0;
}
