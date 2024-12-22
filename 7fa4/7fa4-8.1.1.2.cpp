#pragma GCC optimize("Ofast")
#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
static constexpr auto MOD=(int)(1e9+7);
class casereader{
public:
    auto readargs(int&x){
        cin>>x;
    }
    auto readargs(lint&x){
        cin>>x;
    }
    auto readargs(auto&x,auto&...args){
        readargs(x);readargs(args...);
    }
};
class random_engine{
private:
    mt19937_64 eng;
public:
    template<typename _Ty>
    auto randint(auto l,auto r){
        return uniform_int_distribution<_Ty>(l,r)(eng);
    }
    random_engine():eng(
            251
    ){}
} rnd;
struct node{
    node*ls,*rs;
    int w,add,sum;
    lint siz;
    auto addw(lint x){
        (add+=x)%=MOD;(w+=x)%=MOD;(sum+=1ll*x%MOD*((siz>>1)%MOD)%MOD)%=MOD;
    }
    auto reverse(){
        siz^=1;swap(ls,rs);
    }
    auto free()->void;
    auto lsiz(){return ls?(ls->siz>>1):0;}
    auto rsiz(){return rs?(rs->siz>>1):0;}
    node(lint _w=0):ls(nullptr),rs(nullptr),siz(2),add(0),w(_w),sum(_w){}
};
static constexpr auto maxmem=(int)(3e7+7);
array<node,maxmem> tr;
bitset<maxmem> inuse;
int cnt,vaildcnt=maxmem;
auto check(node*u){
    if(!u) return;
    if(inuse.test(u-tr.data())) return;
    inuse.set(u-tr.data());--vaildcnt;
    check(u->ls);check(u->rs);
}
auto checkm(node*root){
    inuse.reset();
    check(root);
    cnt=0;vaildcnt=maxmem-inuse.count()-1;
    cerr<<"REBUILD: "<<vaildcnt<<' '<<inuse.count()<<'\n';
}
auto getnode(node*root,lint w=0){
    --vaildcnt;
    while(inuse.test(cnt+1)) ++cnt;
    return&(tr[++cnt]=node(w));
}
class treap{
private:
    node*root;
    auto copy(node*u){
        if(!u) return getnode(root);
        const auto res=getnode(root);
        *res=*u;
        return res;
    }
    auto push_down(node*u){
        if(u->ls){
            u->ls=copy(u->ls);
            if(u->siz&1) u->ls->reverse();
            u->ls->addw(u->add);
        }
        if(u->rs){
            u->rs=copy(u->rs);
            if(u->siz&1) u->rs->reverse();
            u->rs->addw(u->add);
        }
        u->add=0;u->siz-=(u->siz&1);
    }
    auto maintain(node*u){
        u->sum=u->w%MOD;u->siz=2;
        for(auto v:{u->ls,u->rs}) if(v) (u->sum+=v->sum)%=MOD,u->siz+=(v->siz)-(v->siz&1);
    }
    auto split(node*u,lint rk)->pair<node*,node*>{
        if(!u) return pair<node*,node*>(nullptr,nullptr);
        u=copy(u);
        push_down(u);
        if(u->lsiz()>rk-1){
            const auto[ux,vx]=split(u->ls,rk);
            u->ls=vx;maintain(u);
            return pair(ux,u);
        }else{
            const auto[ux,vx]=split(u->rs,rk-u->lsiz()-1);
            u->rs=ux;maintain(u);
            return pair(u,vx);
        }
    }
    auto merge(node*u,node*v){
        if(!u) return v;
        if(!v) return u;
        if(rnd.randint<lint>(0,u->siz+v->siz-1)<u->siz){
            push_down(u);
            u->rs=merge(u->rs,v);
            maintain(u);
            return u;
        }else{
            push_down(v);
            v->ls=merge(u,v->ls);
            maintain(v);
            return v;
        }
    }
    auto getrange(lint l,lint r){
        const auto[al,qx]=split(root,l-1);
        const auto[rg,ar]=split(qx,r-l+1);
        return tuple(al,rg,ar);
    }
public:
    auto append(lint x){
        root=merge(root,getnode(root,x));
    }
    auto add(lint l,lint r,lint w){
        const auto[al,rg,ar]=getrange(l,r);
        rg->addw(w);
        root=merge(merge(al,rg),ar);
    }
    auto reverse(lint l,lint r){
        const auto[al,rg,ar]=getrange(l,r);
        rg->reverse();
        root=merge(merge(al,rg),ar);
    }
    auto remove(lint l,lint r){
        const auto[al,rg,ar]=getrange(l,r);
        root=merge(al,ar);
    }
    auto copy(lint l,lint r,lint p){
        const auto[al,rg,ar]=getrange(l,r);
        const auto ins=copy(rg);
        root=merge(merge(al,rg),ar);
        const auto[rl,rr]=split(root,p);
        root=merge(merge(rl,ins),rr);
    }
    auto sum(lint l,lint r){
        const auto[al,rg,ar]=getrange(l,r);
        const auto res=rg->sum;
        root=merge(merge(al,rg),ar);
        return res;
    }
    auto check(){
        if(vaildcnt<100000) checkm(root);
    }
    treap():root(nullptr){}
};
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    casereader inf;
    int n,q;inf.readargs(n,q);
    treap tr;
    cir(i,0,n){
        lint w;inf.readargs(w);tr.append((w%MOD+MOD)%MOD);
    }
    cir(i,0,q){
        int op;inf.readargs(op);
        if(op==1){
            lint l,r,x;inf.readargs(l,r,x);
            x=(x%MOD+MOD)%MOD;
            tr.add(l,r,x);
        }else if(op==2){
            lint l,r;inf.readargs(l,r);
            tr.reverse(l,r);
        }else if(op==3){
            lint l,r,p;inf.readargs(l,r,p);
            tr.copy(l,r,p);
        }else if(op==4){
            lint l,r;inf.readargs(l,r);
            tr.remove(l,r);
        }else{
            lint l,r;inf.readargs(l,r);
            cout<<tr.sum(l,r)<<'\n';
        }
        tr.check();
    }
    return 0;
}
