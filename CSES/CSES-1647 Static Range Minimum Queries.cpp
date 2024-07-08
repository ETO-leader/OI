#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
template<typename T,T _inf=(T)(1e9+7),class comp=less<T>>
class segment{
private:
    int _n;vector<T> val;
    T change(int u,int l,int r,int s,int v){
        if(l==s&&r==s){val[u]=v;return val[u];}
        auto ls=u*2,rs=u*2+1,mid=(l+r)/2;
        val[u]=min((mid<s?change(rs,mid+1,r,s,v):
            change(ls,l,mid,s,v)),(mid<s?val[ls]:val[rs]),comp());
        return val[u];
    }
    T quary(int u,int l,int r,int ql,int qr){
        if(ql<=l&&r<=qr) return val[u];
        auto ls=u*2,rs=u*2+1,mid=(l+r)/2;T res=_inf;
        if(mid>=ql) res=min(quary(ls,l,mid,ql,qr),res,comp());
        if(mid<qr) res=min(quary(rs,mid+1,r,ql,qr),res,comp());
        return res;
    }
public:
    segment(int __n=1):_n(__n-1),val(__n*4,_inf){}
    void resize(int __n){(*this)=segment(__n);}
    void change(int s,int v){change(1,1,_n,s,v);}
    T quary(int l,int r){return quary(1,1,_n,min(l,r),max(l,r));}
};
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n,q,x;cin>>n>>q;segment<int> sig(n+1);
    cir(i,1,n+1) cin>>x,sig.change(i,x);
    cir(i,0,q){
        int l,r;cin>>l>>r;cout<<sig.quary(l,r)<<'\n';
    }
    return 0;
}