#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
template<typename T,const T Min_Element=0,class comp=less<T>>
class segment{
private:
    vector<T> val,tag,mx;int _n;
    void push_down(int u){
        auto ls=u*2,rs=u*2+1;
        mx[ls]+=tag[u]-(mx[ls]==Min_Element)*(mx[ls]);
        mx[rs]+=tag[u]-(mx[rs]==Min_Element)*(mx[rs]);
        tag[ls]+=tag[u];tag[rs]+=tag[u];
        tag[u]=0;
    }
    void update(int u,int l,int r,int ql,int qr,T v){
        if(ql<=l&&r<=qr){
            tag[u]+=v;val[u]+=(r-l+1)*v;mx[u]+=v-(mx[u]==Min_Element)*(mx[u]);
            return;
        }
        auto ls=u*2,rs=u*2+1,mid=(l+r)/2;
        push_down(u);
        if(mid>=ql) update(ls,l,mid,ql,qr,v);
        if(mid<qr) update(rs,mid+1,r,ql,qr,v);
        mx[u]=max(mx[ls],mx[rs],comp());val[u]=val[ls]+val[rs];
    }
    pair<T,T> quary(int u,int l,int r,int ql,int qr){
        if(ql<=l&&r<=qr) return {val[u],mx[u]};
        pair<T,T> res={0,Min_Element};
        push_down(u);
        auto ls=u*2,rs=u*2+1,mid=(l+r)/2;
        if(mid>=ql){
            auto q=quary(ls,l,mid,ql,qr);
            res.first+=q.first;
            res.second=max(res.second,q.second,comp());
        }
        if(mid<qr){
            auto q=quary(rs,mid+1,r,ql,qr);
            res.first+=q.first;
            res.second=max(res.second,q.second,comp());
        }
        return res;
    }
public:
    segment(int __n):_n(__n),val(__n*4),
        tag(__n*4),mx(__n*4,Min_Element){}
    void update(int l,int r,T v){update(1,1,_n,l,r,v);}
    T getmax(int l,int r){return quary(1,1,_n,l,r).second;}
};
const lint _inf=1e18+7;
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    lint n,q,ccnt=0,x;cin>>n>>q;
    segment<lint,-_inf> seg(n+1);
    cir(i,0,n) cin>>x,ccnt+=x,seg.update(i+1,i+1,ccnt);
    cir(i,0,q){
        int op,a,b;cin>>op>>a>>b;
        if(op==1){
            auto sm=seg.getmax(a,a)-(!(a-1)?0:seg.getmax(a-1,a-1));
            seg.update(a,n,b-sm);
        }else{
            cout<<max((seg.getmax(a,b)-(!(a-1)?0:seg.getmax(a-1,a-1))),0LL)<<'\n';
        }
    }
    return 0;
}