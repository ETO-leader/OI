#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
class link_cut_tree{
private:
    struct node{
        lint lf,rg,mx,sum,val,fx,siz;
        bool fxd,rev;
        auto set(lint x){
            fxd=true;
            lf=rg=mx=max<lint>(sum=x*siz,0);
            val=x;fx=x;
        }
        auto reverse(){rev^=true;swap(lf,rg);}
        node():lf(0),rg(0),sum(0),val(0),rev(false),
            fx(0),fxd(false),mx(0),siz(1){}
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
    auto maintain(int u){
        tr[u].siz=tr[ls(u)].siz+tr[rs(u)].siz+1;
        tr[u].lf=max(tr[ls(u)].lf,tr[ls(u)].sum+
            tr[u].val+tr[rs(u)].lf);
        tr[u].rg=max(tr[rs(u)].rg,tr[rs(u)].sum+
            tr[u].val+tr[ls(u)].rg);
        tr[u].mx=max({tr[ls(u)].mx,tr[rs(u)].mx,
            tr[ls(u)].rg+tr[u].val+tr[rs(u)].lf});
        tr[u].sum=tr[ls(u)].sum+tr[u].val+tr[rs(u)].sum;
    }
    auto push_down(int u){
        if(tr[u].rev){
            swap(ls(u),rs(u));
            tr[ls(u)].reverse();tr[rs(u)].reverse();
        }
        if(tr[u].fxd){
            if(ls(u)) tr[ls(u)].set(tr[u].fx);
            if(rs(u)) tr[rs(u)].set(tr[u].fx);
        }
        tr[u].rev=false;tr[u].fxd=false;
        maintain(u);
    }
    auto rotate(int u){
        int fu=f[u],ffu=f[fu],c=getch(u);
        if(nrt(fu)) ch[ffu][getch(fu)]=u;
        f[u]=ffu;
        ch[fu][c]=ch[u][!c];f[ch[u][!c]]=fu;
        ch[u][!c]=fu;f[fu]=u;
        maintain(fu);maintain(u);
    }
    auto down(int u)->void{
        if(nrt(u)) down(f[u]);
        push_down(u);
    }
    auto splay(int u){
        for(down(u);nrt(u);rotate(u)){
            int ff=f[u];
            if(nrt(ff)){
                if(getch(ff)==getch(u)) rotate(ff);
                else rotate(u);
            }
        }
    }
    auto access(int u){
        for(int v=0;u;u=f[v=u]){
            splay(u);rs(u)=v;maintain(u);
        }
    }
    auto strt(int u){
        access(u);splay(u);
        tr[u].reverse();push_down(u);
    }
public:
    auto split(int u,int v){
        strt(u);access(v);splay(v);
    }
    auto update(int u,int v,lint x){
        split(u,v);splay(u);
        tr[u].set(x);
    }
    auto query(int u,int v){
        split(u,v);splay(u);
        return tr[u].mx;
    }
    auto link(int u,int v){
        strt(u);f[u]=v;
    }
    link_cut_tree(int n):ch(n),tr(n),f(n){
        tr[0].siz=0;
    }
};
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n;cin>>n;link_cut_tree lct(n+1);
    vector<lint> wi(n+1);
    cir(i,1,n+1) cin>>wi[i];
    cir(i,0,n-1){
        int u,v;cin>>u>>v;lct.link(u,v);
    }
    cir(i,1,n+1) lct.update(i,i,wi[i]);
    int q;cin>>q;
    cir(i,0,q){
        int op;cin>>op;
        if(op==1){
            int u,v;cin>>u>>v;
            cout<<lct.query(u,v)<<'\n';
        }else{
            int u,v,w;cin>>u>>v>>w;
            lct.update(u,v,w);
        }
    }
    return 0;
}
