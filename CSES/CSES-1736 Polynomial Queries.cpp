#include<bits/stdc++.h>
#define cir(i,a,b) for(auto i=a;i<b;++i)
using namespace std;
template<typename T>
class segment{
private:
    using szt=size_t;
    szt _nx;
    vector<T> val,tag;vector<szt> L,R,Rx;
    T range_sum(T st,szt len){
        if(!st) return 0;
        return (st*2+len-1)*len/2;
    }
    T getx(T v,szt len,szt rx){
        return v*len+range_sum(1,len-1)*rx;
    }
    void push_down(szt u){
        if(L[u]==R[u]){tag[u]=0;return;}
        auto ls=u*2,rs=u*2+1;
        auto l=L[u],r=R[u],mid=(l+r)/2;
        L[ls]=l;R[ls]=mid;L[rs]=mid+1;R[rs]=r;
        T valx=tag[u]?tag[u]+(mid-l+1)*Rx[u]:0;
        val[ls]+=getx(tag[u],mid-l+1,Rx[u]);
        val[rs]+=getx(valx,r-mid,Rx[u]);
        tag[ls]+=tag[u];tag[rs]+=valx;tag[u]=0;
        Rx[ls]+=Rx[u];Rx[rs]+=Rx[u];Rx[u]=0;
    }
    void update(szt u,szt l,szt r,szt ql,szt qr,T v){
        if(ql<=l&&r<=qr){
            tag[u]+=v;++Rx[u];
            val[u]+=range_sum(v,r-l+1);
            push_down(u);
            return;
        }
        push_down(u);
        auto ls=u*2,rs=u*2+1,mid=(l+r)/2;
        if(mid>=ql) update(ls,l,mid,ql,qr,v);
        if(mid<qr) update(rs,mid+1,r,ql,qr,max(v+mid-max(ql,l)+1,v));
        val[u]=val[ls]+val[rs];
    }
    T query(szt u,szt l,szt r,szt ql,szt qr){
        if(ql<=l&&r<=qr){
            auto ls=u*2,rs=u*2+1;
            push_down(u);
            return val[u];
        }
        push_down(u);T res=0;
        auto ls=u*2,rs=u*2+1,mid=(l+r)/2;
        if(mid>=ql) res+=query(ls,l,mid,ql,qr);
        if(mid<qr) res+=query(rs,mid+1,r,ql,qr);
        return res;
    }
public:
    segment(szt _n):val(_n*4),tag(_n*4),L(_n*4),
        R(_n*4),_nx(_n),Rx(_n*4){L[1]=1;R[1]=_n;}
    void update(szt l,szt r,T v=1){update(1,1,_nx,l,r,v);}
    T query(szt l,szt r){return query(1,1,_nx,l,r);}
    T&operator[](szt x){return tag[x];}
};
using __int=__int128;
istream&operator>>(istream&is,__int&x){
    string s;is>>s;x=0;
    for(auto&i:s) (x*=10)+=(i-'0');
    return is;
}
ostream&operator<<(ostream&os,__int x){
    if(x>9) os<<(x/10);
    return (os<<(int)(x%10));
}
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n,q;cin>>n>>q;__int vi;
    segment<__int> seg(n+1);
    cir(i,1,n+1) cin>>vi,seg.update(i,i,vi);
    cir(i,0,q){
        int op,l,r;cin>>op>>l>>r;
        if(op==1) seg.update(l,r);
        else cout<<seg.query(l,r)<<'\n';
    }
    return 0;
}