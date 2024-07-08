#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using VI=vector<int>;
using lint=long long;
const int maxn=5e5+7;
template<int sz>
class trie_int{
private:
    struct node{
        array<int,2> s;
        node(){s[0]=s[1]=0;}
    };
    array<node,maxn*sz> tr;
    bool emp;int cnx;
    int newnode(){return ++cnx;}
    int into(int&u){
        if(!u) u=newnode();
        return u;
    }
    void __insert(lint x){
        int u=0;emp=false;
        for(int i=sz-1;~i;--i)
            u=into(tr[u].s[(x>>i)&1]);
    }
    lint __query(lint x){
        int u=0;lint w=0;
        for(lint i=sz-1;~i;--i){
            lint gt=(tr[u].s[((x>>i)&1)^1])?
                (((x>>i)&1)^1):((x>>i)&1);
            u=tr[u].s[gt];w|=(gt<<i);
        }
        return w;
    }
public:
    void clear(){
        emp=true;cnx=0;
        memset(tr.begin(),0,sizeof(tr));
    }
    bool empty(){return emp;}
    void insert(lint x){__insert(x);}
    lint operator()(lint x){return __query(x);}
    trie_int():emp(true),cnx(0){}
};
vector<VI> G;
VI tin,tout,fx,tag;
vector<lint> w,ans;
void dfs(int u,int&cnx,int f=0){
    tin[u]=++cnx;fx[u]=f;
    for(auto&i:G[u]) if(i!=f) dfs(i,cnx,u);
    tout[u]=cnx;
}
bool isancestor(int u,int v){
    return tin[u]<=tin[v]&&tout[v]<=tout[u];
}
void jump(int u,int v){
    while(!isancestor(u,v))
        tag[u]=true,u=fx[u];
    tag[u]=true;
}
int lca(int u,int v){
    while(!isancestor(u,v)) u=fx[u];
    return u;
}
trie_int<62> trx;
void dfs_x(int u,lint&ansz,
    bool rtg=false,int ex=0,int f=0){
    trx.insert(w[u]);
    ansz=max(ansz,w[u]^trx(w[u]));
    for(auto&i:G[u]){
        if(i!=f&&((!tag[i])||
            (rtg&&i!=ex))) dfs_x(i,ansz,rtg,ex,u);
    }
}
void movx(int u,int f,lint&ansz){
    ans[u]=ansz;dfs_x(u,ansz);
    for(auto&i:G[u]) if(tag[i]&&i!=f)
        movx(i,u,ansz);
}
void getans(int u){
    VI nxt;
    for(auto&i:G[u]) if(tag[i]) nxt.push_back(i);
    cir(i,0,nxt.size()){
        trx.clear();lint az=0;
        dfs_x(u,az,true,nxt[i]);
        movx(nxt[i],u,az);
    }
    ans[1]=0;
}
void init(int n){
    G.resize(n+1);w.resize(n+1);ans.resize(n+1);
    tout.resize(n+1);tin.resize(n+1);
    fx.resize(n+1);tag.resize(n+1);
}
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n;cin>>n;init(n);
    cir(i,2,n+1){
        int f;cin>>f;
        G[f].push_back(i);G[i].push_back(f);
    }
    cir(i,1,n+1) cin>>w[i];
    [&](int cnx=0){dfs(1,cnx);}();
    auto [answ,r1,r2]=[&](){
        lint res=0,w1=0,w2=0;
        cir(i,1,n+1){
            trx.insert(w[i]);
            auto nwi=trx(w[i]);
            if((w[i]^nwi)>=res){
                res=w[i]^nwi;w1=w[i];w2=nwi;
            }
        }
        int r1=-1,r2=-1;
        if(res==0){
            cir(i,1,n+1) cout<<ans[i]<<' ';
            exit(((cout<<'\n'),0));
        }
        cir(i,1,n+1){
            if(w1==w[i]&&(r1<0)) r1=i;
            else if(w2==w[i]&&r2<0) r2=i;
        }
        return make_tuple(res,r1,r2);
    }();
    trx.clear();
    jump(r1,r2);jump(r2,r1);int l=lca(r1,r2);
    cir(i,1,n+1) if(!tag[i]) ans[i]=answ;
    getans(l);fill(tag.begin(),tag.end(),0);
    jump(l,1);getans(1);
    cir(i,1,n+1) cout<<ans[i]<<'\n';
    return 0;
}