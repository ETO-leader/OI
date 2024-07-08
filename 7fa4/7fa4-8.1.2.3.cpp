#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
class link_cut_tree{
    struct node{int w,id;};
    vector<node> tr,mx;
    vector<int> rev,f;
    vector<array<int,2>> ch;
    auto&ls(int u){return ch[u][0];}
    auto&rs(int u){return ch[u][1];}
    auto getch(int u){return rs(f[u])==u;}
    auto nrt(int u){return ls(f[u])==u||rs(f[u])==u;}
    auto push_down(int u){
        if(rev[u]){
            swap(ls(u),rs(u));
            rev[ls(u)]^=true;rev[rs(u)]^=true;
            rev[u]=false;
        }
    }
    auto maintain(int u){
        mx[u]=max({mx[ls(u)],mx[rs(u)],tr[u]},[&](auto&a,auto&b){
            return a.w<b.w;
        });
    }
    auto rotate(int u){
        const auto fu=f[u],gu=f[fu],c=(int)(getch(u));
        if(nrt(fu)) ch[gu][getch(fu)]=u;
        f[u]=gu;
        ch[fu][c]=ch[u][!c];f[ch[u][!c]]=fu;
        ch[u][!c]=fu;f[fu]=u;
        maintain(fu);maintain(u);
    }
    auto down(int u)->void{
        if(nrt(u)) down(f[u]);
        push_down(u);
    }
    auto splay(int u){
        for(down(u);nrt(u);rotate(u));
    }
    auto access(int u){
        for(auto v=0;u;u=f[v=u]){
            splay(u);rs(u)=v;maintain(u);
        }
    }
    auto mkrt(int u){
        access(u);splay(u);
        rev[u]^=true;push_down(u);
    }
    auto split(int u,int v){
        mkrt(u);access(v);splay(v);
    }
public:
    auto query(int u,int v){
        split(++u,++v);splay(u);
        return mx[v];
    }
    auto link(int u,int v){
        mkrt(++u);mkrt(++v);f[u]=v;
    }
    auto cut(int u,int v){
        split(++u,++v);ls(v)=f[u]=0;maintain(v);
    }
    auto setwght(int u,int w,int id){
        ++u;tr[u]=mx[u]={w,id};
    }
    link_cut_tree(int _n):
        tr(_n+1),rev(_n+1),f(_n+1),ch(_n+1),mx(_n+1){}
};
class dsu{
private:
    vector<int> f;
public:
    auto findset(int u)->int{
        return f[u]==u?u:(f[u]=findset(f[u]));
    }
    auto merge(int u,int v){
        f[findset(u)]=findset(v);
    }
    dsu(int _n):f(_n){iota(f.begin(),f.end(),0);}
};
class nodegen{
private:
    int cnt;
public:
    auto gen(){return ++cnt;}
    nodegen(int s=-1):cnt(s){}
};
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n,m,q;cin>>n>>m>>q;
    map<pair<int,int>,int> es;
    vector<tuple<int,int,int>> qi(m);
    nodegen ngen(n);
    for(auto&[u,v,w]:qi){
        cin>>u>>v>>w;
        const auto eid=ngen.gen();
        es[{u,v}]=eid;
    }
    auto qes=es;
    vector<tuple<int,int,int>> qs;
    cir(i,0,q){
        int q,x,y;cin>>q>>x>>y;
        if(q==2){
            if(!es.count({x,y})) swap(x,y);
            es.erase({x,y});
        }
        qs.push_back({q,x,y});
    }
    dsu ds(n+m+7);
    link_cut_tree lct(n+m+7);
    auto insert=[&](int p,int u,int v,int w){
        lct.setwght(p,w,p);
        if(ds.findset(u)==ds.findset(v)){
            const auto[mxw,mxid]=lct.query(u,v);
            if(mxw<w+1) return;
            const auto[mu,mv,mw]=qi[mxid-n-1];
            lct.cut(mu,mxid);lct.cut(mv,mxid);
            lct.link(u,p);lct.link(v,p);
        }else{
            lct.link(u,p);lct.link(v,p);
            ds.merge(u,v);
        }
    };
    for(auto&[e,id]:es){
        const auto[u,v]=e;
        insert(id,u,v,get<2>(qi[id-n-1]));
    }
    deque<int> ans;
    reverse(qs.begin(),qs.end());
    for(auto&[q,u,v]:qs){
        if(q==1){
            ans.push_front(lct.query(u,v).w);
        }else{
            insert(qes[{u,v}],u,v,get<2>(qi[qes[{u,v}]-n-1]));
        }
    }
    for(auto&i:ans) cout<<i<<'\n';
    return 0;
}
