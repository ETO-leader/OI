#include<bits/stdc++.h>
#include<bits/extc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace __gnu_pbds;
using namespace std;
using VI=vector<int>;
template<typename T>
using rbt=tree<T,null_type,greater<T>,rb_tree_tag,
    tree_order_statistics_node_update>;
template<typename T>
class bit{
private:
    vector<T> v;
    int lowbit(int x){return x&(-x);}
    void update(int u,T w){
        ++u;
        while(u<v.size()) v[u]+=w,u+=lowbit(u);
    }
public:
    void update(int l,int r,T w){
        update(l,w);update(r+1,-w);}
    T operator()(int u){
        T res=0;++u;
        while(u) res+=v[u],u-=lowbit(u);
        return res;
    }
    void resize(int n){(*this)=bit<T>(n);}
    bit(int n=0):v(n){}
};
vector<VI> up,G;
VI h,inx,oux,ans;int ht,cnx(0);
void dfs(int u,int f=0){
    up[0][u]=f;inx[u]=cnx++;
    cir(i,1,ht) up[i][u]=up[i-1][up[i-1][u]];
    for(auto&i:G[u]) if(i!=f) dfs(i,u);
    oux[u]=cnx;
}
bool isancestor(int u,int v){
    return inx[u]<=inx[v]&&oux[v]<=oux[u];
}
//u -> v's son
int findnerst(int u,int v){
    for(int i=ht-1;~i;--i){
        if(up[i][u]!=v&&isancestor(v,up[i][u]))
            u=up[i][u];
    }
    assert(isancestor(v,u));
    return u;
}
struct query{bool q;int y,l,r,k,id;};
bit<int> b;
vector<query> qx,q1,q2;
void bound(int l,int r,int ql,int qr){
    if(ql>qr) return;
    if(l==r){
        cir(i,ql,qr+1) if(qx[i].q) ans[qx[i].id]=l;
        return;
    }
    const int mid=(l+r)/2;
    q1.clear();q2.clear();
    cir(i,ql,qr+1) if(!qx[i].q){
        if(qx[i].k<=mid)
            b.update(qx[i].l,qx[i].r,qx[i].id);
        if(qx[i].k<=mid) q1.push_back(qx[i]);
        else q2.push_back(qx[i]);
    }else{
        int sx=b(qx[i].l);
        if(sx<=qx[i].k) q1.push_back(qx[i]);
        else qx[i].k-=sx,q2.push_back(qx[i]);
    }
    cir(i,ql,qr+1) if(i-ql<q1.size()){
        qx[i]=q1[i-ql];
    }else{
        qx[i]=q2[i-ql-q1.size()];
    }
    bound(l,mid,ql,ql+q1.size()-1);
    bound(mid+1,r,ql+q1.size(),qr);
}
void init(int n){
    G.resize(n+1);inx.resize(n+1,-1);
    ht=log2(n)+2;up.assign(ht,VI(n+1));
    oux.resize(n+1,-1);b.resize(n+7);
}
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n,m,q;cin>>n>>m>>q;init(n);
    ans.resize(q);
    cir(i,0,n-1){
        int u,v;cin>>u>>v;
        G[u].push_back(v);G[v].push_back(u);
    }
    dfs(1);rbt<int> w;
    cir(i,0,m){
        int u,v,k;cin>>u>>v>>k;w.insert(k);
        bool swp=true;
        if(inx[u]>inx[v]) swap(u,v),swp=false;
        if(isancestor(u,v)){
            int fnd=findnerst(v,u);
            if(!swp) swap(u,v);
            v=fnd;
            cout<<"! "<<u<<' '<<v<<' '<<fnd<<'\n';
            if(inx[u]){
                qx.push_back({false,inx[u],1,inx[v]-1,k,1});
                qx.push_back({false,oux[u]+1,1,inx[v]-1,k,-1});
            }
            if(oux[v]<n-1){
                qx.push_back({false,oux[v]+1,inx[u],oux[u],k,1});
                qx.push_back({false,n,inx[u],oux[u],k,-1});
            }
        }else{
            swap(u,v);
            cout<<u<<' '<<v<<'\n';
            qx.push_back({false,inx[u],inx[v],oux[v],k,1});
            qx.push_back({false,oux[u]+1,inx[v],oux[v],k,-1});
        }
    }
    cout.flush();
    for(auto&i:qx) i.k=w.order_of_key(i.k);
    //cir(i,0,q){
    //    int u,v,k;cin>>u>>v>>k;
    //    if(h[u]>h[v]) swap(u,v);
    //    qx.push_back({true,inx[u],inx[v],0,k,i+1});
    //}
    //sort(qx.begin(),qx.end(),[](query&a,query&b){
    //    return a.y==b.y?a.q<b.q:a.y<b.y;
    //});
    //bound(0,w.size()-1,0,n);
    //for(auto&i:ans) cout<<*w.find_by_order(i)<<'\n';
    //cout.flush();
    return 0;
}
