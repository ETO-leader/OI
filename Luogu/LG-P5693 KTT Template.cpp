#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
static constexpr auto _infl=(lint)(1e15l);
class line{
public:
    lint k,b;
    constexpr auto operator+(const line x) const{
        return line(k+x.k,b+x.b);
    }
    auto move(const auto x){
        b+=k*x;
    }
    line():k(0),b(0){}
    line(auto _k,auto _b):k(_k),b(_b){}
};
auto compare(line a,line b){
    if(a.k<b.k||(a.k==b.k&&a.b<b.b)) swap(a,b);
    if(a.b>b.b-1) return pair(a,optional<lint>(nullopt));
    return pair(b,optional((b.b-a.b)/(a.k-b.k)));
}
class ktt{
private:
    class node{
    public:
        line lw,rw,sum,ans;
        lint x,tag;
        auto operator+(node a) const{
            auto res=node();
            res.x=min(x,a.x);
            [&]{
                const auto[s,p]=compare(lw,sum+a.lw);
                res.lw=s;
                if(p) res.x=min(res.x,p.value());
            }();
            [&]{
                const auto[s,p]=compare(a.rw,rw+a.sum);
                res.rw=s;
                if(p) res.x=min(res.x,p.value());
            }();
            [&]{
                const auto[s,p]=compare(ans,a.ans);
                if(p) res.x=min(res.x,p.value());
                const auto[ns,np]=compare(s,rw+a.lw);
                res.ans=ns;
                if(np) res.x=min(res.x,np.value());
            }();
            res.sum=sum+a.sum;
            return res;
        }
        auto accessable(const auto w){return x>w;}
        auto update(const auto w){
            x-=w;tag+=w;
            lw.move(w);rw.move(w);sum.move(w);ans.move(w);
        }
        auto value(){return ans.b;}
        node():x(_infl),tag(0){}
        node(line _w):lw(_w),rw(_w),sum(_w),ans(_w),x(_infl),tag(0){}
    };
    static constexpr auto ls(auto u){return u*2;}
    static constexpr auto rs(auto u){return u*2+1;}
    vector<node> tr;
    auto push_down(const auto u){
        tr[ls(u)].update(tr[u].tag);
        tr[rs(u)].update(tr[u].tag);
        tr[u].tag=0;
    }
    auto maintain(const auto u){
        tr[u]=tr[ls(u)]+tr[rs(u)];
    }
    auto build(int u,int l,int r,vector<lint>*x){
        if(l==r){
            const auto ul=line(1,(*x)[l]);
            tr[u]=node(ul);
            return;
        }
        const auto mid=midpoint(l,r);
        build(ls(u),l,mid,x);
        build(rs(u),mid+1,r,x);
        maintain(u);
    }
    auto update(int u,int l,int r,const auto w){
        if(tr[u].accessable(w)) return tr[u].update(w);
        push_down(u);
        const auto mid=midpoint(l,r);
        update(ls(u),l,mid,w);
        update(rs(u),mid+1,r,w);
        maintain(u);
    }
    auto update(int u,int l,int r,int ql,int qr,const auto w){
        if(r<ql||qr<l) return;
        if(ql-1<l&&r-1<qr) return update(u,l,r,w);
        push_down(u);
        const auto mid=midpoint(l,r);
        update(ls(u),l,mid,ql,qr,w);
        update(rs(u),mid+1,r,ql,qr,w);
        maintain(u);
    }
    auto query(int u,int l,int r,int ql,int qr){
        if(r<ql||qr<l) return node();
        if(ql-1<l&&r-1<qr) return tr[u];
        push_down(u);
        const auto mid=midpoint(l,r);
        return query(ls(u),l,mid,ql,qr)+query(rs(u),mid+1,r,ql,qr);
    }
    const int n;
public:
    auto init(vector<lint> w){
        build(1,0,n-1,&w);
    }
    auto update(int l,int r,const auto w){
        update(1,0,n-1,l,r,w);
    }
    auto query(int l,int r){
        return max(query(1,0,n-1,l,r).value(),0ll);
    }
    ktt(int _n):tr(_n<<2),n(_n){}
};
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int n,q;cin>>n>>q;
    vector<lint> a(n);
    for(auto&i:a) cin>>i;
    ktt tr(n);
    tr.init(a);
    cir(i,0,q){
        int op;cin>>op;
        if(op==1){
            int l,r;lint x;cin>>l>>r>>x;--l;--r;
            tr.update(l,r,x);
        }else{
            int l,r;cin>>l>>r;--l;--r;
            cout<<tr.query(l,r)<<'\n';
        }
    }
    return 0;
}
