#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
const int _inf=1e9+7;
const lint MOD=998244353;
struct point{
    int x,y;
    point(int _x,int _y):x(_x),y(_y){}
};
const point mn(-1,-1),mx(_inf,_inf);
struct rectangle{
    point l,r;
    void update(point p){
        l.x=min(l.x,p.x);l.y=min(l.y,p.y);
        r.x=max(r.x,p.x);r.y=max(r.y,p.y);
    }
    bool operator&(rectangle&c){
        bool res=false;
        if(r.x>=c.l.x&&l.x<=c.r.x)
            res|=(r.y>=c.l.y&&l.y<=c.r.y);
        if(res) return true;
        if(c.r.x>=l.x&&c.l.x<=r.x)
            res|=(c.r.y>=l.y&&c.l.y<=r.y);
        return res;
    }
    bool isinside(rectangle&c){
        return l.x<=c.l.x&&r.x>=c.r.x&&
            l.y<=c.l.y&&r.y>=c.r.y;
    }
    bool isinside(point&p){
        return l.x<=p.x&&p.x<=r.x&&l.y<=p.y&&r.y>=p.y;
    }
    rectangle():l(mx),r(mn){}
};
enum tree_tag{mul_tree_tag,add_tree_tag};
template<typename T,T mod>
class KD_tree{
private:
    static T qpow(T a,T b){
        T res=1;
        while(b){
            if(b&1) (res*=a)%=MOD;
            (a*=a)%=MOD;b>>=1;
        }
        return res;
    }
    static T inv(T x){return qpow(x,mod-2);}
    struct node:rectangle{
        int cnx;T sum,mul,tag;
        node*ls,*rs;int id;
        node&operator+=(T w){
            (tag+=w)%=mod;(sum+=cnx*w)%=mod;
            return*this;
        }
        node&operator*=(T w){
            (tag*=w)%=mod;(mul*=w)%=mod;
            (sum*=w)%=mod;
            return*this;
        }
        void push_down(){
            if(ls) ((*ls)*=mul)+=tag;
            if(rs) ((*rs)*=mul)+=tag;
            tag=0;mul=1;
        }
        void maintain(){
            if((!ls)&&(!rs)) return;
            sum=0;cnx=0;l=mx;r=mn;
            if(ls) (sum+=ls->sum),(cnx+=ls->cnx);
            if(rs) (sum+=rs->sum),(cnx+=rs->cnx);
            if(ls) update(ls->l),update(ls->r);
            if(rs) update(rs->l),update(rs->r);
        }
        node():ls(nullptr),rs(nullptr),
            sum(0),tag(0),mul(1),rectangle(){}
        ~node(){
            if(ls) delete ls;
            if(rs) delete rs;
        }
    };
    static auto cmp_x(pair<point,int>&a,pair<point,int>&b){
        return a.first.x<b.first.x;}
    static auto cmp_y(pair<point,int>&a,pair<point,int>&b){
        return a.first.y<b.first.y;}
    vector<pair<point,int>> arr;
    vector<node> tr;
    vector<T> wx;
    node*build(int l,int r,bool vec=false){
        node*res=new node();
        if(l==r){
            res->update(arr[l].first);
            res->id=arr[l].second;
            res->cnx=1;(*res)+=wx[res->id];
            return res;
        }
        const int mid=(l+r)/2;
        nth_element(arr.begin()+l,arr.begin()+mid,
            arr.begin()+r+1,vec?cmp_y:cmp_x);
        res->ls=build(l,mid,vec^1);
        res->rs=build(mid+1,r,vec^1);
        res->maintain();
        return res;
    }
    void update(node*u,rectangle&p,T w,tree_tag op){
        if(p.isinside(*u)){
            return (op?((*u)+=w):((*u)*=w)),void();
        }
        u->push_down();
        if((u->ls)&&(p&(*(u->ls)))) update(u->ls,p,w,op);
        if((u->rs)&&(p&(*(u->rs)))) update(u->rs,p,w,op);
        u->maintain();
    }
    T query(node*u,rectangle&p){
        if(p.isinside(*u)) return u->sum;
        u->push_down();T res=0;
        if((u->ls)&&(p&(*(u->ls)))) res+=query(u->ls,p);
        if((u->rs)&&(p&(*(u->rs)))) res+=query(u->rs,p);
        u->maintain();
        return (res%=mod);
    }
    void getinformations(node*u){
        if((!(u->ls))&&(!(u->rs))){
            wx[u->id]=u->sum;
            return;
        }
        u->push_down();
        if(u->ls) getinformations(u->ls);
        if(u->rs) getinformations(u->rs);
    }
    vector<node*> roots;int cnt;
    int lowbit(int x){return x&(-x);}
    void distory(int x){
        cir(i,0,31) if(x&(1<<i)){
            getinformations(roots.back());
            delete roots.back();roots.pop_back();
        }
    }
    set<pair<int,int>> nodex;
    void __insert(point&p,T w){
        int delsum=lowbit(cnt+1);
        distory(delsum-1);
        arr.push_back({p,cnt});wx.push_back(w);
        nodex.insert({p.x,p.y});++cnt;
        roots.push_back(build(cnt-delsum,cnt-1));
    }
public:
    void insert(point p,T w){__insert(p,w);}
    void update(rectangle c,T w,tree_tag op){
        for(auto&i:roots) update(i,c,w,op);
    }
    bool count(point p){
        return nodex.count({p.x,p.y});
    }
    T operator()(rectangle c){
        T res=0;
        for(auto&i:roots) (res+=query(i,c))%=mod;
        return res;
    }
    KD_tree():cnt(0){}
};
struct query_s{
    point p;int op,w,del,id;
    query_s(point _p=mn,int _op=0,int _w=0):
        p(_p),op(_op),w(_w),del(false),id(-1){}
};
struct query_q{rectangle p;int op,w,id;};
auto getrec(point a,point b){
    rectangle res;
    res.update(a);res.update(b);
    return res;
}
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n,q;cin>>n>>q;
    vector<query_s> um(q);
    vector<query_q> ops;
    KD_tree<lint,MOD> kdt;
    vector<point> qryp;
    cir(i,0,q){
        int op;cin>>op;
        if(op==1){
            int l,r,d;cin>>l>>r>>d;
            um[i]=query_s(point(l,r),op,d);
            um[i].id=i;
        }else if(op==2){
            int l,r,d;cin>>l>>r>>d;
            um[i]=query_s(point(l,r),op,d);
            um[i].id=i;
        }else if(op==3){
            int p;cin>>p;
            kdt.insert(point(i,p),0);
            qryp.push_back(point(i,p));
        }else{
            int t;cin>>t;--t;
            rectangle psb;
            auto [l,r]=um[t].p;
            ops.push_back({getrec(point(t,l),
                point(i,r)),um[t].op,um[t].w,t});
            um[t].del=true;
        }
    }
    for(auto&[p,op,w,del,id]:um){
        if((del)||(!op)) continue;
        rectangle psb;
        auto [l,r]=p;
        ops.push_back({getrec(point(id,l),
            point(q,r)),op,w,id});
    }
    sort(ops.begin(),ops.end(),
        [](query_q&a,query_q&b){return a.id<b.id;});
    for(auto&[rec,op,w,id]:ops){
        kdt.update(rec,w,((op==1)?
            add_tree_tag:mul_tree_tag));
    }
    for(auto&i:qryp) cout<<kdt(getrec(i,i))<<'\n';
    return 0;
}
