#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
template<typename T>
class segment{
private:
    vector<T> atag,mn;
    const T _inf=numeric_limits<T>::max();
    void push_down(int u){
        const int ls=u*2,rs=u*2+1;
        atag[ls]+=atag[u];atag[rs]+=atag[u];
        mn[ls]+=atag[u];mn[rs]+=atag[u];
        atag[u]=false;
    }
    void maintain(int u){
        const int ls=u*2,rs=u*2+1;
        mn[u]=min(mn[ls],mn[rs]);
    }
    void update(int u,int l,int r,int ql,int qr,T w){
        if(ql<=l&&r<=qr)
            return (mn[u]+=w),(atag[u]+=w),void();
        push_down(u);
        const int ls=u*2,rs=u*2+1,mid=(l+r)/2;
        if(ql<=mid) update(ls,l,mid,ql,qr,w);
        if(mid<qr) update(rs,mid+1,r,ql,qr,w);
        maintain(u);
    }
    T query(int u,int l,int r,int ql,int qr){
        if(ql<=l&&r<=qr) return mn[u];
        push_down(u);
        const int ls=u*2,rs=u*2+1,mid=(l+r)/2;
        T res=_inf;
        if(ql<=mid) res=min(res,query(ls,l,mid,ql,qr));
        if(mid<qr) res=min(res,query(rs,mid+1,r,ql,qr));
        maintain(u);
        return res; 
    }
    int n;
public:
    void update(int l,int r,T w){
        update(1,1,n,l,r,w);}
    T query(int l,int r){
        return query(1,1,n,l,r);
    }
    segment(int _n):n(_n),mn(_n*4),atag(_n*4){}
};
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int T;cin>>T;
    while(T--){
        int n;cin>>n;lint maxans=0,val=0;
        vector<lint> v(n),sum;
        segment<lint> seg(n);
        for(auto&i:v) cin>>i;
        sum=v;
        cir(i,1,n) sum[i]+=sum[i-1];
        maxans=max(maxans,sum[n-1]);
        if(maxans==sum[n-1]) val=sum[n-1];
        for(int i=n-2;~i;--i){
            seg.update(i+2,n,v[i+1]);
            const lint k=seg.query(i+1,n);
            lint sumi=sum[n-1]-k;
            maxans=max(maxans,sumi);
            if(maxans==sumi) val=sum[i];
        }
        seg.update(1,n,v[0]);
        const lint k=seg.query(1,n);
        lint sumk=sum[n-1]-k;
        maxans=max(maxans,sumk);
        if(maxans==sumk) val=0;
        cout<<val<<'\n';
    }
    return 0;
}