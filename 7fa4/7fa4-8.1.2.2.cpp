#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
class link_cut_tree{
private:
    vector<int> rev,f;
    vector<array<int,2>> ch;
    auto&ls(int u){return ch[u][0];}
    auto&rs(int u){return ch[u][1];}
    auto push_down(int u){
        if(rev[u]){
            swap(ls(u),rs(u));
            rev[ls(u)]^=true;rev[rs(u)]^=true;
            rev[u]=false;
        }
    }
    auto getch(int u)->int{return rs(f[u])==u;}
    auto nrt(int u){return ls(f[u])==u||rs(f[u])==u;}
    auto rotate(int u){
        const auto fu=f[u],gu=f[fu],c=getch(u);
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
    auto dfs(int u,vector<int>&q)->void{
        q.push_back(u-1);
        if(ls(u)) dfs(ls(u),q);
        if(rs(u)) dfs(rs(u),q);
    }
    auto split(int u,int v){
        mkrt(u);access(v);splay(v);
    }
public:
    auto link(int u,int v){
        mkrt(++u);mkrt(++v);f[u]=v;
    }
    auto splitnd(int u,int v){
        split(++u,++v);splay(u);
        vector<int> res;
        return dfs(u,res),res;
    }
    link_cut_tree(int _n):rev(_n+1),f(_n+1),ch(_n+1){}
};
class dsu{
private:
    vector<int> f,siz;
public:
    auto findset(int u)->int{
        return f[u]==u?u:(f[u]=findset(f[u]));
    }
    auto merge(int u,int v){
        u=findset(u);v=findset(v);
        if(u==v) return;
        siz[v]+=siz[u];f[u]=v;
    }
    auto size(int u){return siz[findset(u)];}
    dsu(int _n):f(_n),siz(_n,1){iota(f.begin(),f.end(),0);}
};
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n,m,p;cin>>n>>m>>p;
    dsu ds(n),ads(n);link_cut_tree lct(n);
    auto link=[&](int u,int v){
        if(ds.findset(u)==ds.findset(v)){
            const auto nds=lct.splitnd(ads.findset(u),ads.findset(v));
            auto ux=nds.front();
            for(auto&i:nds) ads.merge(ux,i);
            return ads.size(u);
        }
        u=ads.findset(u);v=ads.findset(v);
        lct.link(u,v);
        return ds.merge(u,v),-1;
    };
    cir(i,0,m){
        int u,v;cin>>u>>v;link(u-1,v-1);
    }
    cir(i,0,p){
        int u,v;cin>>u>>v;
        const auto ans=link(u-1,v-1);
        cout<<(ans<0?"No":to_string(ans).data())<<'\n';
    }
    return 0;
}
