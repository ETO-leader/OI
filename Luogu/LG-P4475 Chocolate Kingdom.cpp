#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
const int _inf=1e9+7;
struct point{
    int x,y;
    point(int _x,int _y):x(_x),y(_y){}
};
const point mn(-_inf,-_inf),mx(_inf,_inf);
//ax+by=c
struct line{
    lint a,b,c;
    bool calc(lint x,lint y){
        return a*x+b*y<c;
    }
};
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
    bool under(line&lx){
        return lx.calc(l.x,r.y)&&lx.calc(r.x,r.y)
            &&lx.calc(l.x,l.y)&&lx.calc(r.x,l.y);
    }
    bool operator&(line&lx){
        return lx.calc(l.x,l.y)||lx.calc(l.x,r.y)||
            lx.calc(r.x,r.y)||lx.calc(r.x,l.y);
    }
    bool isinside(rectangle&c){
        return l.x<=c.l.x&&r.x>=c.r.x&&
            l.y<=c.l.y&&r.y>=c.r.y;
    }
    bool isinside(point&p){
        return l.x<=p.x&&p.x<=r.x&&l.y<=p.y&&r.y>=p.y;
    }
    void print(){
        cout<<"[("<<l.x<<','<<l.y<<")("<<r.x<<','<<r.y<<")]:";
    }
    rectangle():l(mx),r(mn){}
};
template<typename T>
class KD_tree{
private:
    struct node:rectangle{
        int cnx;T sum,tag;
        node*ls,*rs;int id;
        node&operator+=(T w){
            tag+=w;sum+=cnx*w;
            return*this;
        }
        void push_down(){
            if(ls){
                ls->tag+=tag;ls->sum+=ls->cnx*tag;
            }
            if(rs){
                rs->tag+=tag;rs->sum+=rs->cnx*tag;
            }
            tag=0;
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
            sum(0),tag(0),rectangle(){}
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
    void update(node*u,rectangle&p,T w){
        if(p.isinside(*u)) return (*u)+=w,void();
        u->push_down();
        if((u->ls)&&(p&(*(u->ls)))) update(u->ls,p,w);
        if((u->rs)&&(p&(*(u->rs)))) update(u->rs,p,w);
        u->maintain();
    }
    T query(node*u,line&p){
        if(u->under(p)) return u->sum;
        u->push_down();T res=0;
        if((u->ls)&&((*(u->ls))&p)) res+=query(u->ls,p);
        if((u->rs)&&((*(u->rs))&p)) res+=query(u->rs,p);
        u->maintain();
        return res;
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
    void update(rectangle c,T w){
        for(auto&i:roots) update(i,c,w);
    }
    bool count(point p){
        return nodex.count({p.x,p.y});
    }
    T operator()(line lx){
        T res=0;
        for(auto&i:roots) res+=query(i,lx);
        return res;
    }
    KD_tree():cnt(0){}
};
istream&operator>>(istream&is,line&l){
    return is>>l.a>>l.b>>l.c;
}
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n,m;cin>>n>>m;KD_tree<lint> kdt;
    cir(i,0,n){
        int x,y;lint w;cin>>x>>y>>w;
        kdt.insert(point(x,y),w);
    }
    cir(i,0,m){
        line l;cin>>l;
        cout<<kdt(l)<<'\n';
    }
    return 0;
}
