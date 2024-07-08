#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
class link_cut_tree{
private:
    struct node{
        int siz,tsiz,val,rev;
        node():siz(0),tsiz(0),val(0),rev(false){}
    };
    vector<node> tr;
    vector<array<int,2>> ch;
    vector<int> f;
    auto&ls(int u){return ch[u][0];}
    auto&rs(int u){return ch[u][1];}
    auto nrt(int u){
        return ls(f[u])==u||rs(f[u])==u;
    }
    auto getch(int u){
        return rs(f[u])==u;
    }
    auto push_down(int u){
        if(!tr[u].rev) return;
        tr[ls(u)].rev^=true;tr[rs(u)].rev^=true;
        swap(ls(u),rs(u));
        tr[u].rev=false;
    }
    auto maintain(int u){
        tr[u].siz=tr[ls(u)].siz+tr[rs(u)].siz+
            tr[u].val+tr[u].tsiz;
    }
    auto rotate(int u){
        const auto fu=f[u],gu=f[fu];
        const auto c=getch(u);
        if(nrt(fu)) ch[gu][getch(fu)]=u;
        f[u]=gu;
        ch[fu][c]=ch[u][!c];f[ch[u][!c]]=fu;
        ch[u][!c]=fu;f[fu]=u;
        maintain(fu);maintain(u);maintain(gu);
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
            splay(u);
            tr[u].tsiz+=tr[rs(u)].siz-tr[v].siz;
            rs(u)=v;
            maintain(u);
        }
    }
    auto mkrt(int u){
        access(u);splay(u);
        tr[u].rev^=true;push_down(u);
    }
    auto split(int u,int v){
        mkrt(u);access(v);splay(v);
    }
public:
    auto link(int u,int v){
        mkrt(u);mkrt(v);
        f[u]=v;tr[v].tsiz+=tr[u].siz;
    }
    auto cut(int u,int v){
        split(u,v);
        ls(v)=f[u]=0;
        maintain(v);maintain(u);
    }
    auto query(int u,int v){
        cut(u,v);mkrt(u);mkrt(v);
        const auto res=1ll*tr[u].siz*tr[v].siz;
        link(u,v);
        return res;
    }
    auto set(int u){tr[u].siz=tr[u].val=1;}
    link_cut_tree(int n):tr(n),ch(n),f(n){}
};
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n,q;cin>>n>>q;link_cut_tree lct(n+1);
    cir(i,1,n+1) lct.set(i);
    cir(i,0,q){
        string op;cin>>op;
        if(op[0]=='A'){
            int u,v;cin>>u>>v;
            lct.link(u,v);
        }else{
            int u,v;cin>>u>>v;
            cout<<lct.query(u,v)<<'\n';
        }
    }
    return 0;
}
