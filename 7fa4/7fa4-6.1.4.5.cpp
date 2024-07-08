#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
template<typename T>
class dsu{
private:
    vector<T> F,siz,ew;
    vector<pair<T,T>> ops;
public:
    T findset(int x){return x==F[x]?x:findset(F[x]);}
    T height(int x){
        T res=0;
        while(x!=F[x]) res+=ew[x],x=F[x];
        return res;
    }
    void merge(int x,int y){
        int rx=x,ry=y;
        x=findset(x),y=findset(y);
        if(siz[y]<siz[x]) swap(x,y),swap(rx,ry);
        ops.push_back({x,y});
        siz[y]+=siz[x];ew[x]=height(ry)+1-height(rx);
        return F[x]=y,void();
    }
    void remoke(){
        auto [x,y]=ops.back();
        ops.pop_back();
        F[x]=x;siz[y]-=siz[x];ew[x]=0;
    }
    size_t size(){return F.size();}
    dsu(T n):F(n),siz(n,1),ew(n){
        iota(F.begin(),F.end(),0);
    }
};
struct edge_t{int u,v;};
class segment{
private:
    vector<vector<edge_t>> es;
    vector<bool> ans;int q;
    void insert(int u,int l,int r,int ql,int qr,edge_t&ie){
        if(ql<=l&&r<=qr) return es[u].push_back(ie);
        const int ls=u*2,rs=u*2+1,mid=(l+r)/2;
        if(mid>=ql) insert(ls,l,mid,ql,qr,ie);
        if(qr>mid) insert(rs,mid+1,r,ql,qr,ie);
    }
    dsu<int> ds;
    void dfs(int u,int l,int r){
        int rmksiz=0;
        for(auto&[x,y]:es[u]){
            if(ds.findset(x)!=ds.findset(y)){
                ++rmksiz;
                ds.merge(x,y);
                continue;
            }
            if((ds.height(x)+ds.height(y)+1)&1){
                fill(ans.begin()+l,ans.begin()+r+1,false);
                cir(i,0,rmksiz) ds.remoke();
                return;
            }
        }
        if(l==r){
            cir(i,0,rmksiz) ds.remoke();
            return ans[l]=true,void();
        }
        const int ls=u*2,rs=u*2+1,mid=(l+r)/2;
        dfs(ls,l,mid);dfs(rs,mid+1,r);
        cir(i,0,rmksiz) ds.remoke();
    }
public:
    void insert(int ql,int qr,edge_t ie){
        insert(1,0,q-1,ql,qr,ie);
    }
    void dfs(){dfs(1,0,q-1);}
    bool operator()(int x){return ans[x];}
    segment(int _q,int n):
        q(_q),es(_q<<2),ans(_q),ds(n+1){}
};
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n,m,q;cin>>n>>m>>q;
    segment seg(q,n);
    cir(i,0,m){
        int u,v,s,e;cin>>u>>v>>s>>e;
        if(s==e) continue;
        seg.insert(s,e-1,{u,v});
    }
    seg.dfs();
    cir(i,0,q) cout<<(seg(i)?"Yes":"No")<<'\n';
    return 0;
}
