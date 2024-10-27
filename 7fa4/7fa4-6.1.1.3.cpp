#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
class randomengine{
private:
    mt19937 eng;
public:
    auto randint(int l,int r){return uniform_int_distribution<int>(l,r)(eng);}
    randomengine():eng(random_device().operator()()){}
} rnd;
class treap{
private:
    struct node{
        node*ls,*rs;
        int w,siz;bool flipped;
        auto flip(){
            flipped^=true;
            swap(ls,rs);
        }
        auto push_down(){
            if(!flipped) return;
            for(auto v:{ls,rs}) if(v) v->flip();
            flipped=false;
        }
        auto maintain(){
            siz=1;
            for(auto v:{ls,rs}) if(v) siz+=v->siz;
        }
        node(int _w):ls(nullptr),rs(nullptr),siz(1),w(_w),flipped(false){}
        ~node(){
            for(auto v:{ls,rs}) if(v) delete v;
        }
    };
    node*root;
    auto split(node*u,int qsiz){
        if(!u) return pair<node*,node*>(nullptr,nullptr);
        u->push_down();
        if((u->ls?u->ls->siz:0)>qsiz-1){
            const auto[ux,vx]=split(u->ls,qsiz);
            u->ls=vx;u->maintain();
            return pair(ux,u);
        }else{
            const auto[ux,vx]=split(u->rs,qsiz-(u->ls?u->ls->siz:0)-1);
            u->rs=ux;u->maintain();
            return pair(u,vx);
        }
    }
    auto merge(node*u,node*v){
        if(!u) return v;
        if(!v) return u;
        u->push_down();v->push_down();
        if(rnd.randint(1,u->siz+v->siz)<u->siz){
            u->rs=merge(u->rs,v);
            return u->maintain(),u;
        }else{
            v->ls=merge(u,v->ls);
            return v->maintain(),v;
        }
    }
    auto dfs(node*u,vector<int>&x){
        if(!u) return;
        u->push_down();
        dfs(u->ls,x);
        x.push_back(u->w);
        dfs(u->rs,x);
    }
public:
    auto flip(int l,int r){
        const auto[lx,mx]=split(root,l);
        const auto[qx,rx]=split(mx,r-l+1);
        qx->flip();
        root=merge(merge(lx,qx),rx);
    }
    auto append(int x){
        root=merge(root,new node(x));
    }
    auto foreach(){
        vector<int> res;
        return dfs(root,res),res;
    }
    treap():root(nullptr){}
    ~treap(){if(root) delete root;}
};
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int n,m;cin>>n>>m;treap tr;
    cir(i,0,n) tr.append(i+1);
    cir(i,0,m){
        int l,r;cin>>l>>r;--l;--r;
        tr.flip(l,r);
    }
    auto ans=tr.foreach();
    copy(ans.begin(),ans.end(),ostream_iterator<int>(cout," "));
    cout<<'\n';
    return 0;
}
