#include"rts.h"
#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;

class checklist{
private:
    vector<int> v,pos;
public:
    auto checked(int w){
        if(w==v.back()) return v.pop_back();
        auto p=pos[w];
        auto r=v.back();
        swap(v[p],v.back());
        v.pop_back();
        pos[v[p]]=p;
    }
    auto choice(mt19937_64&eng){
        return v[uniform_int_distribution<int>(0,(int)(v.size())-1)(eng)];
    }
    auto empty(){return v.empty();}
    auto size(){return v.size();}
    checklist(int _n):v(_n),pos(_n){
        ranges::iota(v,0);
        ranges::iota(pos,0);
    }
};

class optimized_set{
private:
    vector<int> info;
    multiset<int> sinfo;
    bool mode;
    inline auto ensure(){
        if(info.size()>10){
            sinfo=multiset(info.begin(),info.end());
            info.clear();
            mode=true;
        }
    }
public:
    auto emplace(int x){
        if(mode) sinfo.emplace(x);
        else info.emplace_back(x),ensure();
    }
    auto extract(int x){
        if(mode) sinfo.extract(x);
        else info.erase(ranges::find(info,x));
    }
    auto clear(){
        info.clear();sinfo.clear();
    }
    auto maxval(){
        if(mode) return*sinfo.rbegin();
        else return*ranges::max_element(info);
    }
    optimized_set(vector<int> _w):info(_w),mode(false){ensure();}
};

class divided_tree{
private:
    vector<vector<int>> gr;
    vector<int> ban,fr,intr,visd,siz,subtsiz;
    vector<optimized_set> ht;
    int root,n;
    auto dfssz(int u,int f=-1)->int{
        siz[u]=1;
        for(auto&i:gr[u]) if(i!=f&&(!ban[i])) siz[u]+=dfssz(i,u);
        return siz[u];
    }
    auto dfsgrv(int u,const int usz,int f=-1)->int{
        auto sum=usz-1,mx=0;
        for(auto&i:gr[u]) if(i!=f&&(!ban[i])){
            const auto fv=dfsgrv(i,usz,u);
            if(fv>-1) return fv; 
            mx=max(mx,siz[i]);
            sum-=siz[i];
        }
        if(max(mx,sum)<usz/2+1) return u;
        return -1;
    }
    auto build(int u)->int{
        const auto usz=dfssz(u);
        const auto ng=dfsgrv(u,usz);
        visd.emplace_back(ng);
        ban[ng]=true;
        ht[ng].clear();
        subtsiz[ng]=usz;
        for(auto&i:gr[ng]) if(!ban[i]){
            const auto v=build(i);
            fr[v]=ng;
            ht[ng].emplace(ht[v].maxval()+1);
        }
        ht[ng].emplace(0);
        return ng;
    }
    auto remove_ht(int u){
        auto x=u;
        while(x!=root){
            ht[fr[x]].extract(ht[x].maxval()+1);
            x=fr[x];
            visd.emplace_back(x);
            ban[x]=true;
        }
    }
    auto update_ht(int u){
        auto x=u;
        while(x!=root){
            ht[fr[x]].emplace(ht[x].maxval()+1);
            x=fr[x];
        }
        for(auto&x:visd) ban[x]=false;
        visd.clear();
    }
    auto rebuild(int u){
        remove_ht(u);
        const auto fru=fr[u];
        const auto ur=build(u);
        if(u!=root){
            fr[ur]=fru;
        }else{
            fr[ur]=ur;
            root=ur;
        }
        update_ht(ur);
        return ur;
    }
    auto ensure(int u)->void{
        if(ht[u].maxval()>__lg(subtsiz[u])*3) u=rebuild(u);
        do{
            u=fr[u];        
            if(ht[u].maxval()>__lg(subtsiz[u])*3) u=rebuild(u);
        }while(u!=root);        
    }
    auto getancestor(int x,int u){
        while(fr[u]!=x) u=fr[u];
        return u;
    }
    auto addpath(int u){
        while(u!=root) ++subtsiz[u],u=fr[u];
        ++subtsiz[u];
    }
    auto getpath(int x,checklist&chk){
        auto u=root,las=root;
        while(true){
            las=u;
            u=explore(u+1,x+1)-1;
            if(!intr[u]) break;
            u=getancestor(las,u);
        }
        remove_ht(las);
        fr[u]=las;
        gr[las].emplace_back(u);
        gr[u].emplace_back(las);
        addpath(u);
        update_ht(u);
        ensure(u);
        chk.checked(u);
        intr[u]=true;
        while(u!=x){
            las=u;
            u=explore(u+1,x+1)-1;
            addpath(u);
            remove_ht(las);
            fr[u]=las;
            gr[las].emplace_back(u);
            gr[u].emplace_back(las);
            update_ht(u);
            ensure(u);
            chk.checked(u);
            intr[u]=true;
        }
    }
public:
    auto play(){
        checklist chk(n);
        chk.checked(0);
        intr[0]=true;
        mt19937_64 eng(251);
        while(!chk.empty()){
            const auto v=chk.choice(eng);
            getpath(v,chk);
        }
    }
    divided_tree(int _n):gr(_n),ban(_n),fr(_n),intr(_n),siz(_n),ht(_n,vector{0}),subtsiz(_n),root(0),n(_n){}
};

class randomized_chain{
private:
    const int n;
public:
    auto play(){
        auto ul=0,ur=0;
        vector<int> ban(n);
        ban[0]=true;
        checklist chk(n);
        chk.checked(0);
        auto remove=[&](int w){
            ban[w]=true;
            chk.checked(w);
        };
        mt19937_64 eng(251);
        while(!chk.empty()){
            const auto x=chk.choice(eng);
            auto u=ul;
            auto chg=false;
            [&]{
                auto vux=explore(u+1,x+1)-1;
                if(ban[vux]) chg=true,u=ur;
                else remove(vux),u=vux;
            }();
            while(u!=x){
                u=explore(u+1,x+1)-1;
                remove(u);
            }
            (chg?ur:ul)=u;
        }
    }
    randomized_chain(int _n):n(_n){}
};

void play(int n,int T,int dataType){
    if(dataType==3) randomized_chain(n).play();
    else divided_tree(n).play();
}

