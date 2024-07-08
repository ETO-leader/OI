#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
const int MOD=1e9+7;
template<typename T>
class segment{
private:
    vector<T> add,mul,val;
    vector<int> lx,rx;
    function<void(int,T)> addtag=
        [&](int u,T w){
        (add[u]+=w);
        (val[u]+=w*(rx[u]-lx[u]+1));
    };
    void init(int u,int l,int r){
        lx[u]=l;rx[u]=r;
        if(l==r) return;
        init(u*2,l,(l+r)/2);
        init(u*2+1,(l+r)/2+1,r);
    }
    void pushdown_s(int u,int s){
        (((val[s]*=mul[u]))+=add[u]*(rx[s]-lx[s]+1));
        (mul[s]*=mul[u]);
        ((add[s]*=mul[u])+=add[u]);
    }
    void pushdown(int u){
        pushdown_s(u,u*2);
        pushdown_s(u,u*2+1);
        mul[u]=1;add[u]=0;
    }
    void maintain(int u){
        val[u]=(val[u*2]+val[u*2+1]);
    }
    void update(int u,int l,int r,int ql
        ,int qr,T w,function<void(int,T)> clc){
        if(ql<=l&&r<=qr) return clc(u,w),void();
        const int ls=u*2,rs=u*2+1,mid=(l+r)/2;
        pushdown(u);
        if(mid>=ql) update(ls,l,mid,ql,qr,w,clc);
        if(mid<qr) update(rs,mid+1,r,ql,qr,w,clc);
        maintain(u);
    }
    T query(int u,int l,int r,int ql,int qr){
        if(ql<=l&&r<=qr) return val[u];
        const int ls=u*2,rs=u*2+1,mid=(l+r)/2;
        T res=0;pushdown(u);
        if(mid>=ql) res+=query(ls,l,mid,ql,qr);
        if(mid<qr) res+=query(rs,mid+1,r,ql,qr);
        maintain(u);
        return res;
    }
    int n;
public:
    void additional(int l,int r,T w){
        update(1,1,n,l,r,w,addtag);}
    T operator()(int l,int r){
        return query(1,1,n,l,r);}
    segment(int _n):n(_n),add(_n*4),mul(_n*4,1),
        val(_n*4),lx(_n*4),rx(_n*4){init(1,1,n);}
};
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n;cin>>n;vector<int> vx(n);
    for(auto&i:vx) cin>>i;
    lint ans=0,lans=0;
    unordered_map<int,int> um;
    segment<lint> seg(n);
    cir(i,0,n){
        if(!um.count(vx[i])){
            lans+=(i+1)+seg(1,i+1)*2;
            seg.additional(1,i+1,1);    
        }else{
            lans+=(i-um[vx[i]])+
                seg(um[vx[i]]+2,i+1)*2;
            seg.additional(um[vx[i]]+2,i+1,1);
        }
        um[vx[i]]=i;
        (ans+=lans)%=MOD;lans%=MOD;
    }
    cout<<ans<<'\n';
    return 0;
}
