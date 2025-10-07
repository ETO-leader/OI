#include<bits/stdc++.h>
#define cir(i,a,b) for(auto i=a;i<b;++i)
using namespace std;
using lint=long long;
static constexpr auto _inf=(int)(1e9+7);
class self_adjusting_top_tree{
private:
    enum types{splay_tree,link_cut_tree};
    enum idch{lson,mson,rson};
    struct tag{
        int add,fill;bool filled;
        tag():add(0),fill(0),filled(false){}
        tag(int _a,int _f,bool _fl):add(_a),fill(_f),filled(_fl){}
    };
    struct data{
        int mn,mx,sum,siz;
        data():mn(_inf),mx(-_inf),sum(0),siz(0){}
        data(int _a,int _b,int _sum,int _siz):mn(_a),mx(_b),sum(_sum),siz(_siz){}
    };
    struct node{
        tag pt,ct;
        data pd,cd;
        int f;
        array<int,3> ch;
        int val;
        bool rev;
        node():
            pt(),ct(),pd(),cd(),
            f(0),ch({0,0,0}),val(0),
            rev(false){}
    };
    friend auto operator+(const tag a,const tag b){
        return tag(
            (!b.filled)?a.add+b.add:b.add,
            b.filled?b.fill:a.fill,
            a.filled||b.filled
        );
    }
    friend auto operator+(const data a,const tag b){
        auto c=a;
        if(b.fill) c.mn=c.mx=b.fill,c.sum=a.siz*b.fill;
        c.sum+=b.add*c.siz;c.mn+=b.add;c.mx+=b.add;
        if(a.mn==_inf) c.mn=_inf;
        if(a.mx==-_inf) c.mx=-_inf;
        return c;
    }
    friend auto operator+(const data a,const data b){
        return data(
            min(a.mn,b.mn),
            max(a.mx,b.mx),
            a.sum+b.sum,
            a.siz+b.siz
        );
    }
    auto&ls(int u){return tr[u].ch[lson];}
    auto&ms(int u){return tr[u].ch[mson];}
    auto&rs(int u){return tr[u].ch[rson];}
    auto&fr(int u){return tr[u].f;}
    vector<node> tr;
    stack<int,vector<int>> rmved;
    int cur;
    auto newnode(){
        auto res=rmved.empty()?++cur:rmved.top();
        if(!rmved.empty()) rmved.pop();
        tr[res]=node();
        tr[res].pd.siz=tr[res].cd.siz=0;
        return res;
    }
    auto getch(int u){
        return (idch)(find(tr[fr(u)].ch.begin(),tr[fr(u)].ch.end(),u)-tr[fr(u)].ch.begin());
    }
    auto nrt(int u){
        return ls(fr(u))==u||rs(fr(u))==u;
    }
    constexpr auto rdir(idch c) const{return (c==rson)?lson:rson;}
    auto pathtag(int u,tag w){
        if(!u) return;
        tr[u].val=(w.filled?w.fill:tr[u].val)+w.add;
        tr[u].pd=tr[u].pd+w;
        tr[u].pt=tr[u].pt+w;
    }
    auto subtag(int u,tag w){
        if(!u) return;
        tr[u].cd=tr[u].cd+w;
        tr[u].ct=tr[u].ct+w;
    }
    auto reverse(int u){
        swap(ls(u),rs(u));
        tr[u].rev^=true;
    }
    template<const types type>
    auto push_down(int u){
        if(type){      // Link-cut-tree nodes (Circle nodes)
            if(tr[u].rev) reverse(ls(u)),reverse(rs(u));
            pathtag(ls(u),tr[u].pt);
            pathtag(rs(u),tr[u].pt);
            cir(i,0,3) subtag(tr[u].ch[i],tr[u].ct);
            tr[u].pt=tr[u].ct=tag();
            tr[u].rev=false;
        }else{         // Splay tree nodes (Square nodes)
            pathtag(ms(u),tr[u].ct);
            cir(i,0,3) subtag(tr[u].ch[i],tr[u].ct);
            tr[u].ct=tag();
        }
    }
    template<const types type>
    auto maintain(int u){
        if(type){      // Link-cut-tree nodes: Update both path and subtree
            tr[u].pd=tr[ls(u)].pd+data(tr[u].val,tr[u].val,tr[u].val,1)+tr[rs(u)].pd;
            tr[u].cd=tr[ls(u)].cd+tr[ms(u)].cd+tr[rs(u)].cd;
        }else{         // Splay tree nodes: Only update subtree data
            tr[u].cd=tr[ls(u)].cd+tr[ms(u)].cd+tr[rs(u)].cd+tr[ms(u)].pd;
        }
    }
    template<const types type>
    void rotate(int u) {
        const auto c=getch(u);
        const auto fu=fr(u),gu=fr(fu),vx=tr[u].ch[rdir(c)];
        if(gu) tr[gu].ch[getch(fu)]=u;
        if(vx) fr(vx)=fu;
        fr(u)=gu;tr[u].ch[rdir(c)]=fu;
        fr(fu)=u;tr[fu].ch[c]=vx;
        maintain<type>(fu);maintain<type>(u);
    }
    template<const types type>
    auto down(int u)->void{
        if(nrt(u)) down<type>(fr(u));
        push_down<type>(u);
    }
    template<const types type>
    auto splay(int u,int target=0){
        for(down<type>(u);nrt(u)&&fr(u)!=target;rotate<type>(u)){
            if(fr(fr(u))!=target&&nrt(fr(u))) rotate<type>(getch(fr(u))==getch(u)?fr(u):u);
        }
    }
    auto relink(int u,int f,idch c){
        tr[f].ch[c]=u;
        if(u) fr(u)=f;
    }
    // Remove the square node with no mid-son after current Splice operation
    auto remove(int u){
        relink(ms(u),fr(u),rson);
        if(ls(u)){
            auto v=ls(u);
            push_down<splay_tree>(v);
            while(rs(v)) v=rs(v),push_down<splay_tree>(v);
            splay<splay_tree>(v,u);
            relink(rs(u),v,rson);
            relink(v,fr(u),mson);
            maintain<splay_tree>(v);
            maintain<link_cut_tree>(fr(u));
        }else{
            relink(rs(u),fr(u),mson);
        }
        rmved.emplace(u);
    }
    auto splice(int u){
        splay<splay_tree>(u);
        const auto v=fr(u);
        splay<link_cut_tree>(v);
        push_down<splay_tree>(u);
        if(rs(v)) swap(fr(ms(u)),fr(rs(v))),swap(ms(u),rs(v));
        else remove(u);
        maintain<splay_tree>(u);
        maintain<link_cut_tree>(v);
    }
    auto access(int u){
        splay<link_cut_tree>(u);
        if(rs(u)){
            const auto v=newnode();
            relink(ms(u),v,lson);
            relink(rs(u),v,mson);
            rs(u)=0;
            relink(v,u,mson);
            maintain<splay_tree>(v);
            maintain<link_cut_tree>(u);
        }
        for(auto v=u;fr(v);) splice(fr(v)),v=fr(v),maintain<link_cut_tree>(v);
        splay<link_cut_tree>(u);
    }
    int root;
    auto makeroot(int u){
        access(u);reverse(u);
    }
    auto split(int u,int v){
        makeroot(u);access(v);splay<link_cut_tree>(u);
    }
    auto findtop(int u){
        access(u);
        while(ls(u)) push_down<link_cut_tree>(u),u=ls(u);
        splay<link_cut_tree>(u);
        return u;
    }
    auto updsub(int u,tag w){
        access(u);
        subtag(ms(u),w);
        tr[u].val=(w.filled?w.fill:tr[u].val)+w.add;
        maintain<link_cut_tree>(u);
        makeroot(root);
    }
    auto updpath(int u,int v,tag w){
        split(u,v);
        pathtag(u,w);
        makeroot(root);
    }
    auto qrysub(int u){
        access(u);
        const auto res=tr[ms(u)].cd+data(tr[u].val,tr[u].val,tr[u].val,1);
        makeroot(root);
        return res;
    }
    auto qrypath(int u,int v){
        split(u,v);
        const auto res=tr[u].pd;
        makeroot(root);
        return res;
    }
    auto cut(int u){
        access(u);
        auto v=ls(u);
        while(rs(v)) push_down<link_cut_tree>(v),v=rs(v);
        ls(u)=fr(ls(u))=0;
        maintain<link_cut_tree>(u);
        return v;
    }
public:
    auto subadd(int u,int w){updsub(u+1,tag(w,0,false));}
    auto subfill(int u,int w){updsub(u+1,tag(0,w,true));}
    auto pathadd(int u,int v,int w){updpath(u+1,v+1,tag(w,0,false));}
    auto pathfill(int u,int v,int w){updpath(u+1,v+1,tag(0,w,true));}
    auto submin(int u){return qrysub(u+1).mn;}
    auto submax(int u){return qrysub(u+1).mx;}
    auto pathmin(int u,int v){return qrypath(u+1,v+1).mn;}
    auto pathmax(int u,int v){return qrypath(u+1,v+1).mx;}
    auto subsum(int u){return qrysub(u+1).sum;}
    auto pathsum(int u,int v){return qrypath(u+1,v+1).sum;}
    auto chgroot(int nrt){
        makeroot(root=(nrt+1));
    }
    auto link(int u,int v){
        ++u;++v;
        access(u);makeroot(v);
        relink(v,u,rson);
        maintain<link_cut_tree>(u);
        makeroot(root);
    }
    auto chgfather(int u,int v){
        ++u;++v;
        if(u==v||u==root) return;
        const auto w=cut(u);
        if(findtop(u)==findtop(v)) link(u-1,w-1);
        else link(u-1,v-1);
        makeroot(root);
    }
    self_adjusting_top_tree(int _n):tr(_n*2+7),cur(_n+3){
        tr[0].pd.mn=tr[0].cd.mn=_inf;
        tr[0].pd.mx=tr[0].cd.mx=-_inf;
        tr[0].pd.siz=tr[0].cd.siz=0;
    }
};
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int n;cin>>n;self_adjusting_top_tree satt(n);
    satt.chgroot(0);
    cir(i,0,n-1){
        int u,v;cin>>u>>v;--u;--v;
        satt.link(u,v);
    }
    cir(i,0,n){
        lint w;cin>>w;
        satt.pathfill(i,i,w);
    }
    int q;cin>>q;
    cir(i,0,q){
        string op;cin>>op;
        if(op=="CHANGE"){
            int p;lint w;cin>>p>>w;--p;
            satt.pathfill(p,p,w);
        }else if(op=="QMAX"){
            int u,v;cin>>u>>v;--u;--v;
            cout<<satt.pathmax(u,v)<<'\n';
        }else{
            int u,v;cin>>u>>v;--u;--v;
            cout<<satt.pathsum(u,v)<<'\n';
        }
    }
    return 0;
}
