#include"stations.h"
#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;

class encode_function{
private:
    class tree{
    private:
        vector<vector<int>> gr;
        vector<int> id;
        auto dfs(int u,auto&cdfn,int utype=true,int f=-1)->void{
            if(utype) id[u]=++cdfn;
            for(auto&i:gr[u]) if(i!=f) dfs(i,cdfn,utype^1,u);
            if(!utype) id[u]=++cdfn;
        }
    public:
        auto link(int u,int v){
            gr[u].emplace_back(v);
            gr[v].emplace_back(u);
        }
        auto encode(){
            auto cdfn=-1;
            dfs(0,cdfn);
            return id;
        }
        tree(int _n):gr(_n),id(_n){}
    };
public:
    static auto encode(vector<int> u,vector<int> v){
        const auto n=(int)(u.size())+1;
        tree gr(n);
        cir(i,0,n-1) gr.link(u[i],v[i]);
        return gr.encode();
    }
};

class decode_function{
private:
    enum node_type{uODD,uEVEN};
    static auto get_type(int u,vector<int> v){
        for(auto&x:v) if(u<x) return uEVEN;
        return uODD;
    }
    static auto noderange(int u,vector<int> v){
        const auto utype=get_type(u,v);
        if(utype==uEVEN){
            const auto l=u;
            v.erase(ranges::max_element(v));
            const auto r=v.empty()?l:*ranges::max_element(v);
            return pair(l,r);
        }else{
            const auto r=u;
            v.erase(ranges::min_element(v));
            const auto l=v.empty()?r:*ranges::min_element(v);
            return pair(l,r);
        }
    }
    static auto father(int u,vector<int> v){
        const auto utype=get_type(u,v);
        return utype==uEVEN?*ranges::max_element(v):*ranges::min_element(v);
    }
    static auto child(int u,int t,vector<int> v){
        const auto utype=get_type(u,v);
        if(utype==uEVEN){
            v.emplace_back(u);
            ranges::sort(v);
            for(auto i=(int)(v.size())-1;i;--i) if(v[i-1]<t){
                return v[i];
            }
            return u;
        }else{
            v.emplace_back(u);
            ranges::sort(v);
            cir(i,0,(int)(v.size())-1) if(v[i+1]>t) return v[i];
            return u;
        }
    }
public:
    static auto decode(int u,int t,vector<int> v){
        const auto[l,r]=noderange(u,v);
        if(t>l-1&&t-1<r) return child(u,t,v);
        return father(u,v);
    }
};

vector<int> label(int,int,vector<int> u,vector<int> v){
    return encode_function::encode(u,v);
}

int find_next_station(int u,int t,vector<int> v){
    return decode_function::decode(u,t,v);
}
