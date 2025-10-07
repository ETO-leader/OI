#pragma GCC optimize("Ofast")

#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;

class nodeinfo;
template<const int w,const int h>
class rectangle_range;
class node;
class application;

class nodeinfo{
public:
    friend class node;
    string name;
    node*origin;
    constexpr auto is_linked() const{
        return !!origin;
    }
    nodeinfo(node*__origin,string origname):origin(__origin),name(origname){}
    nodeinfo(string name):origin(nullptr),name(name){}
};

template<const int w,const int h>
class rectangle_range{
private:
    int x,y;
public:
    friend class node;
    auto inrange(int u,int v){
        return
            x<u&&y<v&&
            x+w>u&&y+h>v;
    }
    rectangle_range(int _x,int _y):x(_x),y(_y){}
};

class node{
private:
    nodeinfo info;
    node*f;
    int limy;
    vector<node*> ch;
    rectangle_range<50,10> r;
public:
    friend class application;
    auto nodeset(unordered_set<string>&s,unordered_set<node*>&rvis)->void{
        if(rvis.count(this)) return;
        rvis.emplace(this);
        s.emplace(info.name);
        if(info.is_linked()) info.origin->nodeset(s,rvis);
        for(auto&c:ch) c->nodeset(s,rvis);
    }
    auto ensure()->int{
        assert(f);
        auto res=10;
        r=rectangle_range<50,10>(f->r.x+10,f->limy);
        limy=f->limy+10;
        if(info.is_linked()){
            f->limy+=res;
            return res;
        }
        for(auto&c:ch) res+=c->ensure();
        f->limy+=res;
        return res;
    }
    auto unlink(node*p){
        p->f->limy=p->r.y;
        ch.erase(find(ch.begin(),ch.end(),p));
        p->f=nullptr;
    }
    auto addchild(node*p){
        ch.emplace_back(p);
        p->f=this;
        p->ensure();
    }
    auto copylinked(node*res){
        *res=*this;
        res->info=info;
        if(!info.is_linked()) res->info.origin=this;
        return res;
    }
    auto name(){
        return info.is_linked()?info.origin->info.name:info.name;
    }
    node(string name):info(name),f(nullptr),r(-1,-1),limy(-1){}
};

class application{
private:
    vector<node*> allocated;
    unordered_map<string,node*> origins;
    auto newnode(){
        auto res=new node("unnamed");
        allocated.emplace_back(res);
        return res;
    }
public:
    auto init(string s,vector<string> chl){
        auto&p=origins[s];
        for(auto x:chl){
            const auto u=newnode();
            if(x.find("(link)")!=string::npos){
                cir(i,0,6) x.pop_back();
                origins[x]->copylinked(u);
                assert(u->name()!="unnamed");
            }else{
                u->info.name=x;
                origins[x]=u;
            }
            p->addchild(u);
        }
    }
    auto ensure(){
        origins["root"]->limy=10;
        for(auto&x:origins["root"]->ch) x->ensure();
    }
    auto left_click(int x,int y,int u,int v){
        auto ux=(node*)(nullptr),vx=(node*)(nullptr);
        for(auto&p:allocated){
            if(p->r.inrange(x,y)) ux=p;
            if(p->r.inrange(u,v)) vx=p;
        }
        if(!ux) return 1;                  // Invalid : No node detected
        if(!vx) return 1;                  // Invalid : No node detected
        if(ux==vx) return 1;
        if(vx->info.is_linked()) return 2; // Invalid : Move to LINK node
        unordered_set<string> s;
        unordered_set<node*> rvis;
        origins[ux->name()]->nodeset(s,rvis);
        if(s.count(vx->name())) return 2;  // Invalid : Loop detected
        const auto uf=ux->f;
        uf->unlink(ux);
        vx->addchild(ux);
        return 0;
    }
    auto right_click(int x,int y,int u,int v){
        auto ux=(node*)(nullptr),vx=(node*)(nullptr);
        for(auto&p:allocated){
            if(p->r.inrange(x,y)) ux=p;
            if(p->r.inrange(u,v)) vx=p;
        }
        if(!ux) return 1;                  // Invalid : No node detected
        if(!vx) return 1;                  // Invalid : No node detected
        if(ux==vx) return 1;
        if(vx->info.is_linked()) return 2; // Invalid : Move to LINK node
        unordered_set<string> s;
        unordered_set<node*> rvis;
        origins[ux->name()]->nodeset(s,rvis);
        if(s.count(vx->name())) return 2;  // Invalid : Loop detected
        const auto uv=newnode();
        ux->copylinked(uv);
        vx->addchild(uv);
        return 0;
    }
    application(){
        origins["root"]=newnode();
        origins["root"]->r=rectangle_range<50,10>(10,0);
        origins["root"]->limy=10;
        origins["root"]->info.name="root";
    }
    ~application(){
        for(auto&p:allocated) delete p;
    }
};

int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int n,m;cin>>n>>m;
    application app;
    string s;getline(cin,s);
    cir(i,0,n){
        getline(cin,s);
        stringstream info(s);
        string u;info>>u;
        string c;
        vector<string> chl;
        while(info>>c) chl.emplace_back(c);
        app.init(u,chl);
    }
    app.ensure();
    cir(i,0,m){
        string op;int x,y,u,v;cin>>op>>x>>y>>u>>v;
        if(op=="L"){
            cout<<app.left_click(x,y,u,v)<<'\n';
        }else{
            cout<<app.right_click(x,y,u,v)<<'\n';
        }
        app.ensure();
    }
    return 0;
}
