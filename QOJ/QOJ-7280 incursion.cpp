#include"incursion.h"
#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;

class tree{
protected:
    vector<vector<int>> gr;
    vector<int> uf;
    vector<int> siz;
    auto dfs(int u,int f=-1)->int{
        siz[u]=1;uf[u]=f;
        for(auto&i:gr[u]) if(i!=f) siz[u]+=dfs(i,u);
        return siz[u];
    }
    auto findroot(){
        const auto n=(int)(gr.size());
        vector<int> res;
        cir(u,0,n) [&]{
            for(auto&i:gr[u]) if(i!=uf[u]) if(siz[i]>n/2) return;
            if(n-siz[u]<n/2+1) res.emplace_back(u);
        }();
        return res;
    }
public:
    auto link(int u,int v){
        gr[u].emplace_back(v);
        gr[v].emplace_back(u);
    }
    tree(int _n):gr(_n),uf(_n),siz(_n){}
};

class alice_tree:public tree{
public:
    using tree::tree;
    auto mark_path(int x){
        dfs(0);
        const auto ux=findroot();
        if(x==ux[0]||(ux.size()>1&&x==ux[1])) return vector{x};
        const auto u=ux[0];
        dfs(u);
        vector<int> marks{x};
        while(x!=u) marks.emplace_back(x=uf[x]);
        return marks;
    }
};

class bob_tree:public tree{
private:
    using tree::tree;
    auto move_until(int&x,const int u,map<int,int>&cnt){
        dfs(u);
        while(uf[x]>-1){
            if(cnt.contains(x)&&cnt[x]) return x;
            cnt[uf[x]]=visit(uf[x]+1);
            x=uf[x];
        }
        if(cnt.contains(x)&&cnt[x]) return x;
        return -1;
    }
    auto sorted(int u){
        ranges::sort(gr[u],[&](auto u,auto v){return siz[u]>siz[v];});
        vector<int> res;
        for(auto&i:gr[u]) if(i!=uf[u]) res.emplace_back(i);
        auto sim=true;
        cir(i,1,(int)(res.size())) sim&=(siz[res[i]]==siz[res[0]]);
        if(sim) ranges::shuffle(res,random_device());
        return res;
    }
public:
    auto find_node(int x,int s){
        map<int,int> cnt;
        cnt[x]=s;
        dfs(0);
        const auto ul=findroot();
        auto u=move_until(x,ul[0],cnt);
        if(u==-1) u=move_until(x,ul[1],cnt);
        auto failed=false;
        auto cx=0;
        unordered_set<int> vis;
        while([&]{
            vis.emplace(u);
            const auto ux=sorted(u);
            for(auto&i:ux) if(i!=ul[0]&&(ul.size()<2||i!=ul[1])){
                if(vis.contains(i)) continue;
                if(ul.size()>1&&u==ul[0]&&i==ul[1]&&failed) continue;
                if(visit(i+1)) return u=i,true;
                cx+=2;
                visit(u+1);
            }
            for(auto&i:ux) if(i==ul[0]||(ul.size()>1&&i==ul[1])){
                if(vis.contains(i)) continue;
                if(ul.size()>1&&u==ul[0]&&i==ul[1]&&failed) continue;
                if(visit(i+1)) return u=i,true;
                cx+=2;
                visit(u+1);
            }
            if(ul.size()>1&&u==ul[1]){
                failed=true;
                if(visit(ul[0]+1)) return u=ul[0],true;
                cx+=2;
                visit(ul[1]+1);
            }
            return false;
        }());
        cerr<<ul.size()<<" --> FAIL: "<<cx<<'\n';
        assert(cx<31);
        return u;
    }
};

vector<int> mark(vector<pair<int,int>> es,int ux){
    const auto n=(int)(es.size())+1;
    alice_tree gr(n);
    for(auto&[u,v]:es) gr.link(u-1,v-1);
    vector<int> res(n);
    const auto ul=gr.mark_path(ux-1);
    for(auto&i:ul) res[i]=true;
    return res;
}

void locate(vector<pair<int,int>> es,int u,int t){
    const auto n=(int)(es.size())+1;
    bob_tree gr(n);
    for(auto&[u,v]:es) gr.link(u-1,v-1);
    gr.find_node(u-1,t);
}

