#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
ifstream fcin("draughts.in");
ofstream fcout("draughts.out");
class fileio{
public:
    ~fileio(){
        fcin.close();fcout.close();
    }
};
using lint=long long;
class random_engine{
private:
    mt19937_64 eng;
public:
    template<typename _Ty>
    auto randint(auto l,auto r){
        return uniform_int_distribution<_Ty>(l,r)(eng);
    }
    random_engine():eng(
    #ifdef STABLE
        251
    #else
        random_device().operator()()
    #endif
    ){}
} rnd;
class treap{
private:
    struct node{
        node*ls,*rs;
        lint sum,val;
        int siz;
        constexpr auto lsiz() const{return ls?ls->siz:0;}
        constexpr auto rsiz() const{return rs?rs->siz:0;}
        constexpr auto lsum() const{return ls?ls->sum:0;}
        constexpr auto rsum() const{return rs?rs->sum:0;}
        auto maintain(){
            sum=lsum();
            sum+=val*(lsiz()&1?1:-1);
            sum+=rsum()*(lsiz()&1?1:-1);
            siz=lsiz()+rsiz()+1;
            // clog<<val<<": "<<ls<<' '<<rs<<" --> "<<sum<<' '<<siz<<": "<<lsum()<<' '<<lsiz()<<", "<<rsum()<<' '<<rsiz()<<" <=== "<<rsum()*(lsiz()&1?-1:1)<<' '<<val*(lsiz()&1?1:-1)<<"  * "<<(lsiz()&1?-1:1)<<'\n';
        }
        node(lint _w):ls(nullptr),rs(nullptr),sum(-_w),val(_w),siz(1){}
        ~node(){for(auto v:{ls,rs}) if(v) delete v;}
    };
    node*root;
    auto split(node*u,lint val){
        if(!u) return pair<node*,node*>(nullptr,nullptr);
        if(u->val>val){
            const auto[ux,vx]=split(u->ls,val);
            u->ls=vx;u->maintain();
            return pair(ux,u);
        }else{
            const auto[ux,vx]=split(u->rs,val);
            u->rs=ux;u->maintain();
            return pair(u,vx);
        }
    }
    auto merge(node*u,node*v){
        if(!u) return v;
        if(!v) return u;
        if(rnd.randint<int>(0,u->siz+v->siz)<u->siz){
            u->rs=merge(u->rs,v);
            u->maintain();
            return u;
        }else{
            v->ls=merge(u,v->ls);
            v->maintain();
            return v;
        }
    }
public:
    auto emplace(lint w){
        auto[al,ar]=split(root,w);
        root=merge(merge(al,new node(w)),ar);
    }
    auto value(){return root?root->sum:0;}
    treap():root(nullptr){}
    ~treap(){if(root) delete root;}
};
int main(){
    ios::sync_with_stdio(false),fcin.tie(nullptr);
    int n,q;lint l;fcin>>n>>q>>l;
    auto mn=numeric_limits<lint>::max(),mx=numeric_limits<lint>::min();
    treap tr;
    cir(i,0,n){
        lint w;fcin>>w;tr.emplace(w*2);
        mn=min(mn,w);mx=max(mx,w);
    }
    auto arcnt=n;
    cir(i,0,q){
        int op;lint w;fcin>>op>>w;
        if(op==1){
            tr.emplace(w*2);
            mn=min(mn,w);mx=max(mx,w);
            ++arcnt;
        }else{
            w=min(w,mn*2);
            const auto valx=tr.value()*(arcnt&1?-1:1);
            const auto valrx=valx+w*(arcnt&1?-1:1);
            const auto valnx=(mx*2-valx)+w*(arcnt&1?1:-1);
            if(valnx>l) fcout<<min(mx*2-l,l)<<'\n';
            else fcout<<min(valrx,l)<<'\n';
        }
    }
    return 0;
}
