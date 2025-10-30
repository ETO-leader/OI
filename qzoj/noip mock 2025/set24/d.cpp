#pragma GCC optimize("Ofast","unroll-loops","inline")
#include<bits/stdc++.h>
#define cir(i,a,b) for(auto i=a;i<b;++i)
using namespace std;
class link_cut_tree{
private:
    struct node{
        int siz,vsiz,fll,val;
        array<int,7> sum;
        bool rev;
        inline auto apply(int w){
            fll=w;val=w;
            std::fill(sum.begin(),sum.end(),0);
            sum[w]=siz;
        }
        node():siz(0),vsiz(0),fll(-1),val(-1),rev(false){
            std::fill(sum.begin(),sum.end(),0);
        }
    };
    vector<node> tr;
    vector<int> f;
    vector<array<int,2>> ch;
    auto&ls(auto u){return ch[u][0];}
    auto&rs(auto u){return ch[u][1];}
    auto nrt(int u){return ls(f[u])==u||rs(f[u])==u;}
    auto getch(int u)->int{return rs(f[u])==u;}
    auto reverse(int u){
        tr[u].rev^=1;
        swap(ls(u),rs(u));
    }
    inline auto push_down(int u){
        if(~tr[u].fll){
            tr[ls(u)].apply(tr[u].fll);
            tr[rs(u)].apply(tr[u].fll);
            tr[u].fll=-1;
        }
        if(tr[u].rev){
            reverse(ls(u));
            reverse(rs(u));
            tr[u].rev=false;
        }
    }
    inline auto maintain(int u){
        tr[u].siz=tr[ls(u)].siz+tr[rs(u)].siz+tr[u].vsiz;
        tr[u].sum[0]=tr[ls(u)].sum[0]+tr[rs(u)].sum[0];
        tr[u].sum[1]=tr[ls(u)].sum[1]+tr[rs(u)].sum[1];
        tr[u].sum[2]=tr[ls(u)].sum[2]+tr[rs(u)].sum[2];
        tr[u].sum[3]=tr[ls(u)].sum[3]+tr[rs(u)].sum[3];
        tr[u].sum[4]=tr[ls(u)].sum[4]+tr[rs(u)].sum[4];
        tr[u].sum[5]=tr[ls(u)].sum[5]+tr[rs(u)].sum[5];
        tr[u].sum[6]=tr[ls(u)].sum[6]+tr[rs(u)].sum[6];
        if(tr[u].val>-1) tr[u].sum[tr[u].val]+=tr[u].vsiz;
    }
    auto rotate(int u){
        const auto fu=f[u],gu=f[fu],c=getch(u);
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
        for(down(u);nrt(u);rotate(u)){
            const auto fu=f[u];
            if(nrt(fu)){
                if(getch(fu)==getch(u)) rotate(fu);
                else rotate(u);
            }
        }
    }
    auto access(int u){
        for(auto v=0;u;u=f[v=u]){
            splay(u);
            rs(u)=v;
            maintain(u);
        }
    }
    auto makeroot(int u){
        access(u);splay(u);
        reverse(u);
    }
    auto split(int u,int v){
        makeroot(u);access(v);splay(v);
    }
public:
    auto link(int u,int v){
        ++u;++v;
        makeroot(u);
        makeroot(v);
        f[v]=u;
    }
    auto makesiz(int u){
        ++u;
        tr[u].vsiz=1;
    }
    auto fill(int u,int v,int w){
        ++u;++v;
        split(u,v);
        auto res=tr[v].siz-tr[v].sum[w];
        tr[v].apply(w);
        return res;
    }
    link_cut_tree(int _n):tr(_n+1),f(_n+1),ch(_n+1){}
};
namespace fastIO{
    static array<char,10000000> buf;
    auto p1=buf.begin(),p2=buf.begin();
    #define getchar() p1==p2&&(p2=(p1=buf.begin())+fread(buf.begin(),1,10000000,stdin),p1==p2)?EOF:*p1++
    template<typename _Ty>
    inline auto read(_Ty&x){
        x=0;
        char c=getchar();
        while(!isdigit(c)) c=getchar();
        while(isdigit(c)){
            x=(x<<1)+(x<<3)+(c ^ 48);
            c=getchar();
        }
    }
    template<typename..._Args>
    inline auto read(_Args&...args){
        ((read(args)),...);
    }
    inline auto writeln(const string s){
        for(auto&x:s) putchar_unlocked(x);
        putchar_unlocked('\n');
    }
    #undef getchar
}
int main(){
    int n;fastIO::read(n);link_cut_tree lct(n*2);
    cir(i,0,n-1){
        int u,v;fastIO::read(u,v);--u;--v;
        lct.link(u,n+i);
        lct.link(v,n+i);
        lct.makesiz(n+i);
    }
    int q;fastIO::read(q);
    vector<int64_t> ans(7);
    cir(i,0,q){
        int u,v,w;fastIO::read(u,v,w);--u;--v;--w;
        ans[w]+=lct.fill(u,v,w);
    }
    for(auto&x:ans) fastIO::writeln(to_string(x));
    return 0;
}
