#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
ifstream fcin("tree.in");
ofstream fcout("tree.out");
class fileio{
public:
    ~fileio(){
        fcin.close();fcout.close();
    }
} use_fileio;
using lf=long double;
class link_cut_tree{
private:
    struct node{
        lf w,tag;
        node():w(1),tag(1){}
    };
    vector<node> tr;
    vector<array<int,2>> ch;
    vector<int> f,rev;
    auto&ls(int u){return ch[u][0];}
    auto&rs(int u){return ch[u][1];}
    auto nrt(int u){return ls(f[u])==u||rs(f[u])==u;}
    auto getch(int u){return rs(f[u])==u;}
    auto push_down(int u){
        tr[ls(u)].w*=tr[u].tag;
        tr[ls(u)].tag*=tr[u].tag;
        tr[rs(u)].w*=tr[u].tag;
        tr[rs(u)].tag*=tr[u].tag;
        tr[u].tag=1;
        if(!rev[u]) return;
        for(auto v:{ls(u),rs(u)}) rev[v]^=true;
        swap(ls(u),rs(u));
        rev[u]=false;
    }
    auto rotate(int u){
        const auto fu=f[u],gu=f[fu],c=(int)(getch(u));
        if(nrt(fu)) ch[gu][getch(fu)]=u;
        f[u]=gu;
        ch[fu][c]=ch[u][!c];f[ch[u][!c]]=fu;
        ch[u][!c]=fu;f[fu]=u;
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
            splay(u);rs(u)=v;
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
        mkrt(u);mkrt(v);
        f[u]=v;
    }
    auto update(int u,int v,lf w){
        split(u,v);splay(u);
        tr[u].tag*=w;tr[u].w*=w;
    }
    auto query(int u){
        splay(u);
        return tr[u].w;
    }
    link_cut_tree(int _n):tr(_n),ch(_n),f(_n),rev(_n){}
};
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n;fcin>>n;link_cut_tree lct(n+7);
    auto ncnt=1;
    vector<lf> chsiz(n);
    cir(i,0,n){
        int op;fcin>>op;
        if(op==0){
            int f;fcin>>f;++ncnt;
            ++chsiz[f];
            if(chsiz[f]>1) lct.update(f,1,chsiz[f]/(chsiz[f]-1));
            lct.link(f,ncnt);
        }else{
            int u;fcin>>u;
            fcout<<lct.query(u)<<'\n';
        }
    }
    return 0;
}
