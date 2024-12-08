#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
class casereader{
private:
    union datatype{
        int i32;
        datatype(int _x):i32(_x){}
    };
    vector<datatype> ax;
    int cur;
    auto initint(){
        int x;cin>>x;ax.emplace_back(x);
        return x;
    }
public:
    auto init(){
        const auto n=initint();
        cir(i,0,n) initint();
        const auto q=initint();
        cur=0;
        cir(i,0,q){
            auto op=initint();
            if(op<4) cir(i,0,3) initint();
            else cir(i,0,2) initint();
        }
    }
    auto readargs(int&x){
        x=ax[cur].i32;++cur;
    }
    auto readargs(auto&x,auto&...args){
        readargs(x);readargs(args...);
    }
};
template<class node>
class segment{
private:
    vector<node> tr;
    constexpr auto ls(auto u){return u*2;}
    constexpr auto rs(auto u){return u*2+1;}
    auto push_down(int u){
        tr[u].down(tr[ls(u)],tr[rs(u)]);
    }
    auto maintain(int u){
        tr[u].maintain(tr[ls(u)],tr[rs(u)]);
    }
    auto build(int u,int l,int r){
        tr[u].init(l,r);
        if(l==r) return;
        const auto mid=(l+r)/2;
        build(ls(u),l,mid);
        build(rs(u),mid+1,r);
    }
    auto access(int u,int l,int r,int ql,int qr,auto x,lint w){
        if(qr<l||r<ql) return x.nulltype();
        if(ql-1<l&&r-1<qr&&x.vaild(tr[u],w)) return x.access(tr[u],w);
        const auto mid=(l+r)/2;
        push_down(u);
        const auto res=x.merge(access(ls(u),l,mid,ql,qr,x,w),access(rs(u),mid+1,r,ql,qr,x,w));
        maintain(u);
        return res;
    }
    int n;
public:
    template<class operation>
    auto access(int l,int r,lint w=-1){
        return access(1,0,n-1,l,r,operation(),w);
    }
    segment(int _n):n(_n),tr(_n<<2){build(1,0,_n-1);}
};
struct node{
    lint sum,len,mn,mx,add,fval;
    bool cfval;
    auto addw(lint x){
        sum+=len*x;mn+=x;mx+=x;add+=x;fval+=x;
    }
    auto fill(lint x){
        sum=len*x;mn=x;mx=x;fval=x;add=0;
        cfval=true;
    }
    auto down(node&ls,node&rs){
        ls.addw(add);rs.addw(add);
        if(cfval){
            ls.fill(fval);rs.fill(fval);
        }
        cfval=false;add=0;
    }
    auto init(int l,int r){len=r-l+1;}
    auto maintain(node&ls,node&rs){
        sum=ls.sum+rs.sum;
        mx=max(ls.mx,rs.mx);mn=min(ls.mn,rs.mn);
    }
    node():sum(0),len(0),mx(0),mn(0),add(0),fval(0),cfval(false){}
};
class checkmax{
public:
    auto nulltype(){return true;}
    auto vaild(node&x,lint w){return x.mn>w-1||x.mx<w+1;}
    auto access(node&x,lint w){if(x.mx<w+1) x.fill(w); return true;}
    auto merge(auto...){return true;}
};
class checkmin{
public:
    auto nulltype(){return true;}
    auto vaild(node&x,lint w){return x.mn>w-1||x.mx<w+1;}
    auto access(node&x,lint w){if(x.mn>w-1) x.fill(w);return true;}
    auto merge(auto...){return true;}
};
class add{
public:
    auto nulltype(){return true;}
    auto vaild(node&x,lint w){return true;}
    auto access(node&x,lint w){x.addw(w);return true;}
    auto merge(auto...){return true;}
};
class sum{
public:
    auto nulltype(){return 0ll;}
    auto vaild(node&x,lint w){return true;}
    auto access(node&x,lint w){return x.sum;}
    auto merge(lint a,lint b){return a+b;}
};
class maxval{
public:
    auto nulltype(){return numeric_limits<lint>::min();}
    auto vaild(node&x,lint w){return true;}
    auto access(node&x,lint w){return x.mx;}
    auto merge(lint a,lint b){return max(a,b);}
};
class minval{
public:
    auto nulltype(){return numeric_limits<lint>::max();}
    auto vaild(node&x,lint w){return true;}
    auto access(node&x,lint w){return x.mn;}
    auto merge(lint a,lint b){return min(a,b);}
};
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    casereader inf;inf.init();
    int n;inf.readargs(n);
    segment<node> sg(n);
    cir(i,0,n){
        int w;inf.readargs(w);
        sg.access<add>(i,i,w);
    }
    int q;inf.readargs(q);
    cir(i,0,q){
        int op;inf.readargs(op);
        if(op==1){
            int l,r,x;inf.readargs(l,r,x);--l;--r;
            sg.access<add>(l,r,x);
        }else if(op==2){
            int l,r,x;inf.readargs(l,r,x);--l;--r;
            sg.access<checkmax>(l,r,x);
        }else if(op==3){
            int l,r,x;inf.readargs(l,r,x);--l;--r;
            sg.access<checkmin>(l,r,x);
        }else if(op==4){
            int l,r;inf.readargs(l,r);--l;--r;
            cout<<sg.access<sum>(l,r)<<'\n';
        }else if(op==5){
            int l,r;inf.readargs(l,r);--l;--r;
            cout<<sg.access<maxval>(l,r)<<'\n';
        }else{
            int l,r;inf.readargs(l,r);--l;--r;
            cout<<sg.access<minval>(l,r)<<'\n';
        }
    }
    return 0;
}
