#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
class interactor{
public:
    auto initcase() const{
        int n;cin>>n;vector<pair<int,int>> a(n-1);
        for(auto&[u,v]:a) cin>>u>>v,--u,--v;
        return pair(n,a);
    }
    auto ask(int u) const{
        println(cout,"? {}",u);
        cout.flush();
        int ans;cin>>ans;
        return ans;
    }
    auto answer(int x) const{
        println(cout,"{}",x);
        cout.flush();
    }
    auto answer(int a,int b) const{
        println(cout,"! {} {}",a,b);
        cout.flush();
    }
} interact;
template<class engine=mt19937>
class random_engine{
private:
    engine eng;
public:
    template<typename _Ty>
    auto randint(auto l,auto r){
        return uniform_int_distribution<_Ty>(l,r)(eng);
    }
    random_engine(uint _seed=random_device().operator()()):eng(_seed){}
};
class treap{
    struct node{
        node*ls,*rs;int val,mx,rlv,siz,add;
        auto maintain(){
            mx=val;siz=1;
            for(auto v:{ls,rs}) if(v) mx=max(mx,v->mx),siz+=v->siz;
        }
        node(int _w):ls(nullptr),rs(nullptr),val(_w),mx(_w),rlv(_w),siz(1){}
        ~node(){for(auto v:{ls,rs}) if(v) delete v;}
    };
    random_engine<mt19937_64> rnd;
    node*root;
    auto add(node*u,int x){
        if(!u) return;
        u->add+=x;u->val+=x;u->mx+=x;
    }
    auto push_down(node*u){
        add(u->ls,u->add);
        add(u->rs,u->add);
        u->add=0;
    }
    // left : \le val, right > val
    auto split(node*u,int val){
        if(!u) return pair<node*,node*>(nullptr,nullptr);
        push_down(u);
        if(u->rlv>val){
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
        push_down(u);push_down(v);
        if(rnd.randint<int>(0,u->siz+v->siz)<u->siz){
            u->rs=merge(u->rs,v);
            return u->maintain(),u;
        }else{
            v->ls=merge(u,v->ls);
            return v->maintain(),v;
        }
    }
public:
    auto emplace(int key){
        const auto[u,v]=split(root,key-1);
        add(v,1);
        root=merge(merge(u,new node(key+(u?u->siz:0))),v);
    }
    auto remove(int key){
        auto[u,v]=split(root,key-1);
        auto x=v,las=(node*)(nullptr);
        while(x->ls) las=x,x=x->ls;
        if(las) las->ls=x->rs;
        else v=x->rs;
        x->rs=nullptr;
        delete x;
        add(v,-1);
        root=merge(u,v);
    }
    auto maxval(){return root?root->mx:0;}
    auto clear(){if(root) delete root;}
    treap(auto _seed=random_device().operator()()):root(nullptr),rnd(_seed){}
    ~treap(){if(root) delete root;}
};
class tree{
private:
    vector<vector<int>> gr;
    vector<treap> uft;
    vector<int> uf;
    auto init(int u,int f=-1)->int{
        uft[u].clear();
        for(auto&i:gr[u]) if(i!=f) uft[u].emplace(init(i,u));
        return uf[u]=max(uft[u].maxval(),1);
    }
    auto dfs(int u,auto&ans,int f=-1){
        if(f!=-1){
            uft[f].remove(uf[u]);
            const auto fwf=uft[f].maxval();
            uft[u].emplace(fwf);
            uft[f].emplace(uf[u]);
        }
        ans=max(ans,uft[u].maxval());
    }
    auto inside(int u){
        return interact.ask(u+1)==u+1;
    }
    auto getpos()
public:

};
