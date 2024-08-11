#pragma GCC optimize("Ofast")
#pragma GCC optimize("inline")
#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
ifstream fcin("bst.in");
ofstream fcout("bst.out");
class fileio{
public:
    ~fileio(){
        fcin.close();fcout.close();
    }
} use_fileio;
class link_cut_tree{
private:
    struct node{
        int w,siz,sum,tag;
        auto upd(int nt){
            sum=nt*siz;tag=nt;w=nt;
        }
        node():w(0),siz(1),sum(0),tag(-1){}
    };
    vector<node> tr;
    vector<array<int,2>> ch;
    vector<int> f,rev;
    auto&ls(int u){return ch[u][0];}
    auto&rs(int u){return ch[u][1];}
    auto nrt(int u){return ls(f[u])==u||rs(f[u])==u;}
    auto getch(int u){return rs(f[u])==u;}
    auto push_down(int u){
        if(tr[u].tag>-1){
            tr[ls(u)].upd(tr[u].tag);
            tr[rs(u)].upd(tr[u].tag);
            tr[u].tag=-1;
        }
        if(!rev[u]) return;
        for(auto v:{ls(u),rs(u)}) rev[v]^=true;
        swap(ls(u),rs(u));
        rev[u]=false;
    }
    auto maintain(int u){
        tr[u].siz=tr[ls(u)].siz+tr[rs(u)].siz+1;
        tr[u].sum=tr[ls(u)].sum+tr[rs(u)].sum+tr[u].w;
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
        down(u);
        for(int fx;fx=f[u],nrt(u);rotate(u)){
            if(nrt(fx)) rotate(getch(fx)==getch(u)?fx:u);
        }
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
        mkrt(v);access(u);splay(u);
    }
public:
    auto link(int u,int v){
        ++u;++v;
        mkrt(u);mkrt(v);
        f[u]=v;
    }
    auto update(int u,int v,int c){
        ++u;++v;
        split(u,v);splay(u);
        tr[u].upd(c);
    }
    auto query(int u,int v){
        ++u;++v;
        split(u,v);splay(u);
        return tr[u].sum;
    }
    link_cut_tree(int _n):tr(_n+1),ch(_n+1),f(_n+1),rev(_n+1){
        tr[0].siz=0;
    }
};
class bit{
private:
    vector<int> a;
    constexpr auto lowbit(int p){return p&(-p);}
public:
    auto update(int u,int w){
        for(++u;u<(int)(a.size());u+=lowbit(u)) a[u]+=w;
    }
    auto query(int u){
        auto res=0;
        for(++u;u;u-=lowbit(u)) res+=a[u];
        return res;
    }
    bit(int _n):a(_n+1){}
};
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n,q;fcin>>n>>q;vector<int> ls(n),rs(n);
    cir(i,0,n) fcin>>ls[i]>>rs[i],--ls[i],--rs[i];
    vector<int> rk(n),lx(n),rx(n);
    link_cut_tree lct(n);
    const auto ups=(int)(log2(n)+2);
    vector up(n,vector<int>(ups));
    [&](){
        auto cnt=-1;
        auto dfs=[&](auto __self,int u,int f)->void {
            // cerr<<u<<' '<<ls[u]<<' '<<rs[u]<<'\n';
            up[u][0]=f;lx[u]=cnt+1;
            cir(i,1,ups) up[u][i]=up[up[u][i-1]][i-1];
            if(ls[u]>-1) __self(__self,ls[u],u),lct.link(u,ls[u]);
            rk[u]=++cnt;
            if(rs[u]>-1) __self(__self,rs[u],u),lct.link(u,rs[u]);
            rx[u]=cnt;
        };
        dfs(dfs,0,0);
    }();
    cir(i,0,n) lct.update(0,i,1);
    bit bx(n);
    cir(i,1,n) bx.update(i,1);
    auto ans=n;
    vector<int> wx(n);
    auto updbx=[&](int u,int w){
        const auto rku=rk[u];
        if(rku){
            bx.update(rku,-(wx[rku]>wx[rku-1]-1));
            bx.update(rku,w>wx[rku-1]-1);
        }
        if(rku<n-1){
            bx.update(rku+1,-(wx[rku+1]>wx[rku]-1));
            bx.update(rku+1,wx[rku+1]>w-1);
        }
        wx[rku]=w;
    };
    auto ok=[&](int u){
        return bx.query(rx[u])-bx.query(lx[u])==rx[u]-lx[u];
    };
    auto upd=[&](int u,int w){
        updbx(u,w);
        ans-=lct.query(0,u);
        lct.update(0,u,0);
        auto ux=u;
        for(auto i=ups-1;~i;--i) if(ok(up[ux][i])) ux=up[ux][i];
        if(ok(u)) lct.update(ux,u,1);
        ans+=lct.query(0,u);
    };
    cir(i,0,n){
        int w;fcin>>w;upd(i,w);
    }
    cir(i,0,q){
        int u,w;fcin>>u>>w;--u;
        upd(u,w);
        fcout<<ans<<'\n';
    }
    return 0;
}
