#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
class bit_max{
private:
    vector<int> a;
    constexpr auto lowbit(auto x) const{return x&(-x);}
public:
    auto update(int u,int x){
        for(++u;u<(int)(a.size());u+=lowbit(u)) a[u]=max(a[u],x);
    }
    auto query(int u){
        auto res=0;
        for(++u;u;u-=lowbit(u)) res=max(res,a[u]);
        return res;
    }
    bit_max(int _n):a(_n+1){}
};
using lint=long long;
class treap{
private:
    mt19937_64 eng;
    struct node{
        node*ls,*rs;
        lint sum,tag,cx,cov,val;
        int siz;
        auto lsiz(){return (ls?ls->siz:0);}
        auto rsiz(){return (rs?rs->siz:0);}
        auto cover(lint w){
            tag=0;
            cx=0;
            cov=w;
            sum=w*siz;
            val=w;
        }
        auto addarr(lint w,lint x){
            tag+=w;cx+=x;
            val+=w+x*(this->lsiz());
            sum+=w*siz+(x*(siz-1))*(siz)/2;
        }
        node(auto _w):ls(nullptr),rs(nullptr),sum(_w),tag(0),cx(0),cov(-1),val(_w),siz(1){}
        ~node(){
            if(ls) delete ls;
            if(rs) delete rs;
        }
    };
    auto push_down(node*u){
        if(u->ls){
            if(u->cov>-1) u->ls->cover(u->cov);
            u->ls->addarr(u->tag,u->cx);
        }
        if(u->rs){
            if(u->cov>-1) u->rs->cover(u->cov);
            u->rs->addarr(u->tag+u->cx*(u->lsiz()+1),u->cx);
        }
        u->cov=-1;
        u->tag=0;
        u->cx=0;
    }
    auto maintain(node*u){
        u->sum=u->val;
        u->siz=1;
        if(u->ls) u->sum+=u->ls->sum,u->siz+=u->ls->siz;
        if(u->rs) u->sum+=u->rs->sum,u->siz+=u->rs->siz;
    }
    auto split(node*u,int p){
        if(!u) return pair<node*,node*>(nullptr,nullptr);
        push_down(u);
        if(u->lsiz()<p){
            const auto[sl,sr]=split(u->rs,p-u->lsiz()-1);
            u->rs=sl;
            maintain(u);
            return make_pair(u,sr);
        }else{
            const auto[sl,sr]=split(u->ls,p);
            u->ls=sr;
            maintain(u);
            return make_pair(sl,u);
        }
    }
    auto merge(node*u,node*v){
        if(!u) return v;
        if(!v) return u;
        push_down(u);push_down(v);
        if(uniform_int_distribution<int>(0,u->siz+v->siz)(eng)<u->siz){
            u->rs=merge(u->rs,v);
            maintain(u);
            return u;
        }else{
            v->ls=merge(u,v->ls);
            maintain(v);
            return v;
        }
    }
    node*root;
public:
    auto cover(int l,int r,auto x){
        const auto[ul,vr]=split(root,l);
        const auto[um,ur]=split(vr,r-l+1);
        um->cover(x);
        root=merge(ul,merge(um,ur));
    }
    auto addarr(int l,int r,auto x){
        const auto[ul,vr]=split(root,l);
        const auto[um,ur]=split(vr,r-l+1);
        um->addarr(x,x);
        root=merge(ul,merge(um,ur));
    }
    auto emplace(int p,auto x){
        const auto[ul,ur]=split(root,p);
        root=merge(ul,merge(new node(x),ur));
    }
    auto query(int l,int r){
        const auto[ul,vr]=split(root,l);
        const auto[um,ur]=split(vr,r-l+1);
        const auto res=um->sum;
        root=merge(ul,merge(um,ur));
        return res;
    }
    auto value(int p){
        const auto[ul,vr]=split(root,p);
        const auto[um,ur]=split(vr,1);
        const auto res=um->val;
        root=merge(ul,merge(um,ur));
        return res;
    }
    treap(uint _seed=251):eng(_seed),root(nullptr){}
    ~treap(){if(root) delete root;}
};
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int n;cin>>n;
    treap tr;
    cir(i,0,n){
        int p;cin>>p;--p;
        tr.emplace(p,i);
    }
    vector<int> pos(n);
    cir(i,0,n) pos[tr.value(i)]=i;
    bit_max qwq(n);
    cir(i,0,n){
        const auto p=pos[i];
        const auto uw=qwq.query(p)+1;
        qwq.update(p,uw);
        cout<<qwq.query(n-1)<<'\n';
    }
    return 0;
}
