#pragma GCC optimize("Ofast")
#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
class link_cut_tree{
private:
    struct node{
        int mxa,mxb,x,add;
        auto upd(int xk){
            if(!xk) return;
            x+=xk;add+=xk;swap(mxa,mxb);
        }
        node():mxa(-1),mxb(-1),x(0),add(0){}
    };
    vector<node> tr;
    vector<array<int,2>> ch;
    vector<int> f;
    auto&ls(int u){return ch[u][0];}
    auto&rs(int u){return ch[u][1];}
    auto nrt(int u){
        return ls(f[u])==u||rs(f[u])==u;
    }
    auto getch(int u){return rs(f[u])==u;}
    auto push_down(int u){
        tr[ls(u)].upd(tr[u].add);
        tr[rs(u)].upd(tr[u].add);
        tr[u].add=0;
    }
    auto maintain(int u){
        tr[u].mxa=(tr[u].x==1?-1:u);
        tr[u].mxb=(tr[u].x==2?-1:u);
        tr[u].mxa=max({tr[u].mxa,
            tr[ls(u)].mxa,tr[rs(u)].mxa});
        tr[u].mxb=max({tr[u].mxb,
            tr[ls(u)].mxb,tr[rs(u)].mxb});
    }
    auto rotate(int u){
        int fx=f[u],gx=f[fx],c=getch(u);
        if(nrt(fx)) ch[gx][getch(fx)]=u;
        f[u]=gx;
        ch[fx][c]=ch[u][!c];f[ch[u][!c]]=fx;
        ch[u][!c]=fx;f[fx]=u;
        maintain(fx);maintain(u);
    }
    auto down(int u)->void{
        if(nrt(u)) down(f[u]);
        push_down(u);
    }
    auto splay(int u){
        for(down(u);u&&nrt(u);rotate(u));
    }
    auto access(int u){
        for(int v=0;u;u=f[v=u]){
            splay(u);rs(u)=v;maintain(u);
        }
    }
    bool rootstate;
public:
    auto static_link(int u,int v){
        f[v]=u;
    }
    auto accessa(int u,int x){
        u=f[u];access(u);splay(u);
        int p=(x<0?tr[u].mxb:tr[u].mxa);
        if(p>0){
            splay(p);tr[rs(p)].upd(x);
            maintain(rs(p));tr[p].x+=x;
            maintain(p);
        }else{
            tr[u].upd(x);rootstate^=1;maintain(u);
        }
    }
    auto register_command(){
        rootstate=tr[1].x>1;
    }
    auto check(){return rootstate;}
    auto&at(int u){return tr[u];}
    link_cut_tree(int n):ch(n),tr(n),
        f(n),rootstate(false){}
};
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n;cin>>n;
    link_cut_tree lct(n*3+7);
    vector<vector<int>> g(n*3+7);
    stringstream sstream;
    cir(i,1,n+1){
        int u,v,w;cin>>u>>v>>w;
        sstream<<u<<' '<<v<<' '<<w<<'\n';
        g[i].push_back(u);
        g[i].push_back(v);
        g[i].push_back(w);
    }
    vector<int> id(n*3+7);
    [&](){
        int cnt=0;
        function<void(int)> dfs=[&](int u){
            id[u]=++cnt;
            for(auto&i:g[u]) dfs(i);
        };
        dfs(1);
    }();
    cir(i,1,n+1){
        int u,v,w;sstream>>u>>v>>w;
        lct.static_link(id[i],id[u]);
        lct.static_link(id[i],id[v]);
        lct.static_link(id[i],id[w]);
    }
    vector<int> stx(n*3+7);
    cir(i,n+1,n*3+2){
        cin>>stx[i];
    }
    function<int(int)> ckdfs=[&](int u){
        if(u>n) return stx[u];
        for(auto&i:g[u]) lct.at(id[u]).x+=ckdfs(i);
        return (int)(lct.at(id[u]).x>1);
    };
    ckdfs(1);lct.register_command();
    int q;cin>>q;
    cir(i,0,q){
        int p;cin>>p;
        lct.accessa(id[p],(stx[p]?-1:1));
        stx[p]^=1;
        cout<<lct.check()<<'\n';
    }
    return 0;
}
