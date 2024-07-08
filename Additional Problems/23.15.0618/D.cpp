#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using VI=vector<int>;
const int _inf=numeric_limits<int>::max();
class segment{
private:
    struct node{
        int andsum,orsum,mn,adt;
    };
    vector<node> vn;int n;
    void pushdown(int u){
        const int ls=(u<<1),rs=(ls|1),a=vn[u].adt;
        vn[ls].adt+=a;vn[rs].adt+=a;
        vn[ls].andsum+=a;vn[rs].andsum+=a;
        vn[ls].orsum+=a;vn[rs].orsum+=a;
        vn[ls].mn+=a;vn[rs].mn+=a;
        vn[u].adt=0;
    }
    void maintain(int u){
        const int ls=(u<<1),rs=(ls|1);
        vn[u].andsum=(vn[ls].andsum&vn[rs].andsum);
        vn[u].orsum=(vn[ls].orsum|vn[rs].orsum);
        vn[u].mn=min(vn[ls].mn,vn[rs].mn);
    }
    template<class oper>
    void update(int u,int l,int r,int ql,int qr,int p){
        if(ql<=l&&r<=qr){
            if(oper::ok(u,vn,p)) return oper::update(u,vn,p);
        }
        const int ls=(u<<1),rs=(ls|1),mid=((l+r)>>1);
        pushdown(u);
        if(mid>=ql) update<oper>(ls,l,mid,ql,qr,p);
        if(mid<qr) update<oper>(rs,mid+1,r,ql,qr,p);
        maintain(u);
    }
    void init(int u,int l,int r,VI&v){
        if(l==r) return vn[u]={v[l],v[l],v[l]},void();
        const int ls=(u<<1),rs=(ls|1),mid=((l+r)>>1);
        init(ls,l,mid,v);init(rs,mid+1,r,v);
        maintain(u);
    }
    int query(int u,int l,int r,int ql,int qr){
        if(ql<=l&&r<=qr) return vn[u].mn;
        const int ls=(u<<1),rs=(ls|1),mid=((l+r)>>1);
        int res=_inf;
        pushdown(u);
        if(mid>=ql) res=min(res,query(ls,l,mid,ql,qr));
        if(mid<qr) res=min(res,query(rs,mid+1,r,ql,qr));
        maintain(u);
        return res;
    }
public:
    struct segandfalse{
        static bool ok(const int u,auto&vnx,int pos){
            return (vnx[u].andsum&(1<<pos))
                ==(vnx[u].orsum&(1<<pos));
        }
        static void update(const int u,auto&vnx,int pos){
            if(!(vnx[u].andsum&(1<<pos))) return;
            vnx[u].andsum^=(1<<pos);
            vnx[u].orsum^=(1<<pos);vnx[u].mn^=(1<<pos);
            vnx[u].adt-=(1<<pos);
        }
    };
    struct segortrue{
        static bool ok(const int u,auto&vnx,int pos){
            return (vnx[u].andsum&(1<<pos))
                ==(vnx[u].orsum&(1<<pos));
        }
        static void update(const int u,auto&vnx,int pos){
            if(vnx[u].andsum&(1<<pos)) return;
            vnx[u].andsum|=(1<<pos);
            vnx[u].orsum|=(1<<pos);vnx[u].mn|=(1<<pos);
            vnx[u].adt+=(1<<pos);
        }
    };
    template<class oper>
    void update(int l,int r,int p){
        update<oper>(1,1,n,l,r,p);}
    int operator()(int l,int r){
        return query(1,1,n,l,r);}
    segment(VI&v):n(v.size()-1),
        vn(v.size()<<2){init(1,1,v.size()-1,v);}
};
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n,m;cin>>n>>m;VI v(n);
    for(auto&i:v) cin>>i;
    v.insert(v.begin(),114514);
    segment seg(v);
    cir(i,0,m){
        int op,l,r;cin>>op>>l>>r;
        if(op==1||op==2){
            int x;cin>>x;
            cir(i,0,31) if(x&(1<<i)){
                if(op==2)
                    seg.update<segment::segortrue>(l,r,i);
            }else{
                if(op==1)
                    seg.update<segment::segandfalse>(l,r,i);
            }
        }else{
            cout<<seg(l,r)<<'\n';
        }
    }
    return 0;
}
