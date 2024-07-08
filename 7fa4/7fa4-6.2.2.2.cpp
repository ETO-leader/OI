#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
class link_cut_tree{
private:
    vector<int> f,rev;
    vector<array<int,2>> ch;
    auto&ls(int u){return ch[u][0];}
    auto&rs(int u){return ch[u][1];}
    auto nrt(int u){
        return ls(f[u])==u||rs(f[u])==u;
    }
    auto getch(int u){
        return rs(f[u])==u;
    }
    auto push_down(int u){
        if(!rev[u]) return;
        rev[ls(u)]^=true;rev[rs(u)]^=true;
        swap(ls(u),rs(u));
        rev[u]=false;
    }
    auto down(int u)->void{
        if(nrt(u)) down(f[u]);
        push_down(u);
    }
    auto rotate(int u){
        const auto fu=f[u],gu=f[fu];
        const auto c=getch(u);
        if(nrt(fu)) ch[gu][getch(fu)]=u;
        f[u]=gu;
        ch[fu][c]=ch[u][!c];f[ch[u][!c]]=fu;
        ch[u][!c]=fu;f[fu]=u;
        push_down(fu);push_down(u);
    }
    auto splay(int u){
        for(down(u);nrt(u);rotate(u));
    }
    auto access(int u){
        for(auto v=0;u;u=f[v=u]) splay(u),rs(u)=v;
    }
    auto mkrt(int u){
        access(u);splay(u);
        rev[u]^=true;push_down(u);
    }
    auto split(int u,int v){
        mkrt(u);access(v);splay(v);
    }
    auto fndrt(int u){
        for(access(u),splay(u);ls(u);u=ls(u));
        return u;
    }
public:
    auto link(int u,int v){
        mkrt(u);f[u]=v;
    }
    auto cut(int u,int v){
        split(u,v);ls(v)=f[u]=0;
    }
    auto check(int u,int v){
        return fndrt(u)==fndrt(v);
    }
    link_cut_tree(int _n):ch(_n),f(_n),rev(_n){}
};
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n,q;cin>>n>>q;link_cut_tree lct(n+1);
    cir(i,0,q){
        string op;cin>>op;
        if(op=="Connect"){
            int u,v;cin>>u>>v;
            lct.link(u,v);
        }else if(op=="Destroy"){
            int u,v;cin>>u>>v;
            lct.cut(u,v);
        }else{
            int u,v;cin>>u>>v;
            cout<<(lct.check(u,v)?"Yes":"No")<<'\n';
        }
    }
    return 0;
}
