#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
static constexpr auto _inf=(int)(1e9+7);
class segment{
private:
    struct node{
    private:
        // deque(pos:value)
        list<pair<int,int>> f,sub;
    public:
        node*ls,*rs;
        auto emplacenode(pair<int,int> x){
            while((!f.empty())&&f.front().second>x.second-1) f.pop_front();
            f.emplace_front(x);
        }
        auto emplacesub(pair<int,int> x){
            while((!sub.empty())&&sub.front().second>x.second-1) sub.pop_front();
            sub.emplace_front(x);
        }
        auto fit(const int lrange){
            while((!f.empty())&&f.back().first<lrange) f.pop_back();
            while((!sub.empty())&&sub.back().first<lrange) sub.pop_back();
        }
        auto fvalue(){return f.empty()?_inf:f.back().second;}
        auto subvalue(){return sub.empty()?_inf:sub.back().second;}
        node():ls(nullptr),rs(nullptr){}
        ~node(){for(auto v:{ls,rs}) if(v) delete v;}
    };
    node*root;
    auto update(node*&u,int l,int r,int ql,int qr,pair<int,int> ins){
        if(!u) u=new node();
        if(r<ql||qr<l) return;
        u->emplacesub(ins);
        if(ql-1<l&&r-1<qr) return u->emplacenode(ins);
        const auto mid=l+(r-l)/2;
        update(u->ls,l,mid,ql,qr,ins);
        update(u->rs,mid+1,r,ql,qr,ins);
    }
    auto query(node*u,int l,int r,int ql,int qr,int p){
        if(r<ql||qr<l||(!u)) return _inf;
        u->fit(p);
        if(ql-1<l&&r-1<qr) return u->subvalue();
        const auto mid=l+(r-l)/2;
        return min({query(u->ls,l,mid,ql,qr,p),query(u->rs,mid+1,r,ql,qr,p),u->fvalue()});
    }
    int n;
public:
    auto update(int l,int r,pair<int,int> ins){
        update(root,0,n-1,l,r,ins);
    }
    auto query(int l,int r,int p){
        return query(root,0,n-1,l,r,p);
    }
    segment(auto _n):n(_n),root(nullptr){}
    ~segment(){if(root) delete root;}
};
class caseistream{
private:
    stringstream inf;
public:
    auto&stream(){return inf;}
    auto init(){
        int n,l;cin>>n>>l;
        inf<<n<<' '<<l<<'\n';
        cir(i,0,n-1){
            int l,r,p;cin>>l>>r>>p;
            inf<<l<<' '<<r<<' '<<p<<'\n';
        }
    }
};
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    caseistream inf;inf.init();
    int n,q;inf.stream()>>n>>q;
    vector<tuple<int,int,int>> qry;
    map<int,int> idl;
    cir(i,0,n-1){
        int l,r,p;inf.stream()>>l>>r>>p;
        idl.emplace(l,0);idl.emplace(r,0);
        qry.emplace_back(l,r,p);
    }
    for(auto x=-1;auto&[a,b]:idl) b=++x;
    segment sg(idl.size());
    sg.update(0,(int)(idl.size())-1,pair(0,0));
    for(auto&[l,r,p]:qry){
        l=idl[l];r=idl[r];
        const auto fx=sg.query(l,r,p-q)+1;
        cout<<(fx>_inf?-1:fx)<<'\n';
        sg.update(l,r,pair(p,fx));
    }
    return 0;
}
