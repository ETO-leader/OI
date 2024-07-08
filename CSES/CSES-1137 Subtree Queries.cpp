#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
template<typename T>
class segment{
private:
    int _n;vector<T> val,tag;
    void push_down(int u){
        auto ls=u*2,rs=u*2+1;
        tag[ls]+=tag[u];tag[rs]+=tag[u];tag[u]=0;
    }
    T add(int u,int l,int r,int ql,int qr,T v){
        if(ql<=l&&r<=qr){
            tag[u]+=v;val[u]+=(r-l+1)*v;
            return (r-l+1)*v;
        }
        push_down(u);
        auto ls=u*2,rs=u*2+1,mid=(l+r)/2;T res=0;
        if(mid>=ql) res+=add(ls,l,mid,ql,qr,v);
        if(mid<qr) res+=add(rs,mid+1,r,ql,qr,v);
        val[u]+=res;
        return res;
    }
    T quary(int u,int l,int r,int ql,int qr){
        if(ql<=l&&r<=qr) return val[u];
        val[u]+=(r-l+1)*tag[u];push_down(u);
        auto ls=u*2,rs=u*2+1,mid=(l+r)/2;T res=0;
        if(mid>=ql) res+=quary(ls,l,mid,ql,qr);
        if(mid<qr) res+=quary(rs,mid+1,r,ql,qr);
        return res;
    }
public:
    segment(int n):_n(n),val(n*4),tag(n*4){}
    void add(int l,int r,int v){add(1,1,_n,l,r,v);}
    T quary(int l,int r){return quary(1,1,_n,l,r);}
};
using lint=long long;
vector<vector<int>> G;
vector<int> Tin,Tout;int cnt=0;
void dfs(int u,int f=0){
    Tin[u]=(++cnt);
    for(auto&i:G[u]) if(i!=f) dfs(i,u);
    Tout[u]=cnt;
}
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n,q;cin>>n>>q;segment<lint> sig(n+1);
    G.resize(n+1);Tin.resize(n+1);
    vector<int> v(n+1);Tout.resize(n+1);
    cir(i,1,n+1) cin>>v[i];
    cir(i,0,n-1){
        int u,v;cin>>u>>v;
        G[u].push_back(v),G[v].push_back(u);
    }
    dfs(1);
    cir(i,1,n+1) sig.add(Tin[i],Tin[i],v[i]);
    cir(i,0,q){
        int op,k,v;cin>>op>>k;
        if(op-1){
            cout<<sig.quary(Tin[k],Tout[k])<<'\n';
        }else{
            cin>>v;
            sig.add(Tin[k],Tin[k],
                v-sig.quary(Tin[k],Tin[k]));
        }
    }
    return 0;
}