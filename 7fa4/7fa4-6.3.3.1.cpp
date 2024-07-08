#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
class link_cut_tree{
private:
    struct node{
        int w,nw,cov;
        auto cover(){nw=w=0;cov=true;}
        node():w(1),nw(1),cov(false){}
    };
    vector<node> tr;
    vector<array<int,2>> ch;
    vector<int> rev,f;
    auto&ls(int u){return ch[u][0];}
    auto&rs(int u){return ch[u][1];}
    auto nrt(int u){return ls(f[u])==u||rs(f[u])==u;}
    auto getch(int u){return rs(f[u])==u;}
    auto push_down(int u){
        if(tr[u].cov){
            tr[ls(u)].cover();tr[rs(u)].cover();
            tr[u].cov=false;
        }
        if(rev[u]){
            swap(ls(u),rs(u));
            rev[ls(u)]^=true;rev[rs(u)]^=true;
            rev[u]=false;
        }
    }
    auto maintain(int u){
        tr[u].w=tr[ls(u)].w+tr[rs(u)].w+tr[u].nw;
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
    auto link(int u,int v){
        mkrt(++u);mkrt(++v);f[u]=v;
    }
    auto cover(int u,int v){
        split(++u,++v);splay(u);
        tr[u].cover();
    }
    auto query(int u,int v){
        split(++u,++v);splay(u);
        return tr[u].w;
    }
    auto setw(int u){tr[++u].cover();}
    link_cut_tree(int n):tr(n+1,node()),ch(n+1),
        rev(n+1),f(n+1){tr[0].cover();}
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
    dsu(int n):f(n){iota(f.begin(),f.end(),0);}
};
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n,m;cin>>n>>m;set<pair<int,int>> es;
    cir(i,0,m){
        int u,v;cin>>u>>v;es.insert({u,v});
    }
    vector<tuple<int,int,int>> q;
    for(auto c=-1;cin>>c&&c>-1;){
        int u,v;cin>>u>>v;
        q.push_back({c,u,v});
        if(!c){
            if(!es.count({u,v})) swap(u,v);
            es.erase({u,v});
        }
    }
    reverse(q.begin(),q.end());
    link_cut_tree lct(n+m+2);dsu ds(n+1);
    cir(i,1,n+1) lct.setw(i);
    auto cntn=n;
    for(auto&[u,v]:es){
        if(ds.findset(u)==ds.findset(v)){
            lct.cover(u,v);
        }else{
            lct.link(u,++cntn);
            lct.link(cntn,v);
            ds.merge(u,v);
        }
    }
    vector<int> ans;
    for(auto&[c,u,v]:q){
        if(c) ans.push_back(lct.query(u,v));
        else lct.cover(u,v);
    }
    reverse(ans.begin(),ans.end());
    for(auto&i:ans) cout<<i<<'\n';
    return 0;
}
