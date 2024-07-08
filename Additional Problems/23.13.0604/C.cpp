#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using VI=vector<int>;
template<typename T>
class sparsetable{
private:
    vector<vector<T>> st;
    int ht;
    void init(const vector<T>&v){
        int n=v.size();ht=log2(n)+2;
        st.assign(n,vector<T>(ht));
        cir(i,0,n) st[i][0]=v[i];
        cir(j,1,ht) cir(i,0,(n-(1<<(j-1))))
            st[i][j]=max(st[i][j-1],st[i+(1<<(j-1))][j-1]);
    }
public:
    T operator()(int l,int r) const{
        int lg=log2(r-l+1);
        if(l>r) return -1;
        return max(st[l][lg],st[r-(1<<lg)+1][lg]);
    }
    sparsetable(const vector<T>&v){init(v);}
};
vector<VI> G;
VI taga,siz,tagb,eul,tin,tout,dx;
void abort_x(){
    cout<<-1<<'\n';exit(0);
}
int dfs(int u,int f=0){
    int res=0;siz[u]=1;
    tin[u]=eul.size();eul.push_back(tagb[u]);
    for(auto&i:G[u]) if(i!=f){
        res+=dfs(i,u);siz[u]+=siz[i];
    }
    if(res>siz[u]-1) abort_x();
    res=max(res,taga[u]);
    if(res>siz[u]) abort_x();
    tout[u]=eul.size()-1;
    return (dx[u]=res);
}
void resize_all(int n){
    siz.resize(n+1);tagb.resize(n+1);
    G.resize(n+1);taga.resize(n+1);
    eul.resize(n+1);tin.resize(n+1);
    tout.resize(n+1);dx.resize(n+1);
}
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n;cin>>n;resize_all(n);
    cir(i,0,n-1){
        int u,v;cin>>u>>v;
        G[u].push_back(v);G[v].push_back(u);
    }
    int ax;cin>>ax;
    cir(i,0,ax){
        int u,t;cin>>u>>t;
        taga[u]=max(taga[u],t);
    }
    int bx;cin>>bx;
    cir(i,0,bx){
        int u,t;cin>>u>>t;
        tagb[u]=max(tagb[u],t);
    }
    int d=dfs(1);
    auto brksubtree=[&](int u){
        return n-d-siz[u]+dx[u];
    };
    cir(i,1,n+1){
        eul[tin[i]]=(n-siz[i])-tagb[i];
    }
    sparsetable<int> st(eul);
    int ans=0;
    cir(i,1,n+1){
        int mx=st(1,tin[i]-1);
        mx=max(mx,st(tout[i]+1,n));
        ans=max(ans,dx[i]+tagb[i]+
            max(0,brksubtree(i)-mx));
    }
    cout<<ans<<'\n';
    return 0;
}
