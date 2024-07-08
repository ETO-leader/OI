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
    segment(int __n=0):_n(__n),val(__n*4),tag(__n*4){}
    void resize(int __n){(*this)=segment(__n);}
    void add(int l,int r,int v){add(1,1,_n,min(l,r),max(l,r),v);}
    T quary(int l,int r){return quary(1,1,_n,min(l,r),max(l,r));}
};
using lint=long long;
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n,q,v;cin>>n>>q;segment<lint> sig(n);
    cir(i,1,n+1) cin>>v,sig.add(i,i,v);
    cir(i,0,q){
        int op,u,v;cin>>op>>u>>v;
        if(op-1){
            cout<<sig.quary(u,v)<<'\n';
        }else{
            sig.add(u,u,v-sig.quary(u,u));
        }
    }
    return 0;
}