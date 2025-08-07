#include"migrations.h"
#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;

class tree{
private:
    vector<vector<int>> gr;
    vector<int> dis;
    auto dfs(int u,int c=0,int f=-1)->void{
        dis[u]=c;
        for(auto&i:gr[u]) if(i!=f) dfs(i,c+1,u);
    }
    auto dfsd(int u,int f=-1)->pair<int,int>{
        auto res=pair<int,int>(0,u);
        for(auto&i:gr[u]) if(i!=f){
            const auto[w,x]=dfsd(i,u);
            res=max(res,{w+1,x});
        }
        return res;
    }
public:
    auto link(int u,int v){
        gr[u].emplace_back(v);
        gr[v].emplace_back(u);
    }
    auto info(){
        const auto u=dfsd(0).second;
        const auto[w,v]=dfsd(u);
        return tuple(u,v,w);
    }
    auto check(int r){
        dfs(r);
        return dis;
    }
    tree(int _n):gr(_n),dis(_n){}
};

namespace info{
    static constexpr auto maxN=10000;
    tree tr(maxN);
    pair<int,int> d;
    int updl,updr;
    int len;
    bool apr2,apr3;
    int b0=4,b1=4;
}

int send_message(int N,int i,int Pi){
    info::tr.link(i,Pi);
    auto res=0;
    if(i+22<N){
        if(i+22==N-1){
            const auto[u,v,w]=info::tr.info();
            info::d=pair(u,v);
            info::len=w;
            info::updl=info::d.first;
            info::updr=info::d.second;
        }
    }else if(i+16<N){
        const auto b=N-17-i;
        auto v=info::d.first;
        cir(i,0,b) v/=5;
        res=v%5;
        if(info::tr.check(i)[info::updr]>info::len){
            ++info::len;
            info::updl=i;
        }else if(info::tr.check(i)[info::updl]>info::len){
            ++info::len;
            info::updr=i;
        }
    }else if(i+10<N){
        const auto b=N-11-i;
        auto v=info::d.second;
        cir(i,0,b) v/=5;
        res=v%5;
        if(info::tr.check(i)[info::updr]>info::len){
            ++info::len;
            info::updl=i;
        }else if(info::tr.check(i)[info::updl]>info::len){
            ++info::len;
            info::updr=i;
        }
        if(i+10==N-1){
            info::d=pair(info::updl-(N-23),info::updr-(N-23));
        }
    }else if(i+5<N){
        const auto b=(--info::b0);
        const auto x=(b>-1?(info::d.first>0?((info::d.first>>b)&1):0):0);
        if(info::tr.check(i)[info::updr]>info::len){
            ++info::len;
            info::updl=i;
            if((!info::apr3)&&(!info::apr2)) res=2;
            else if(!info::apr3) res=(x?4:2);
            else res=2;
            if(!info::apr2) ++info::b0;
            info::apr2=true;
        }else if(info::tr.check(i)[info::updl]>info::len){
            ++info::len;
            info::updr=i;
            if((!info::apr3)&&(!info::apr2)) res=3;
            else if(!info::apr2) res=(x?4:3);
            else res=3;
            if(!info::apr3) ++info::b0;
            info::apr3=true;
        }else{
            res=x;
        }
    }else{
        const auto b=(--info::b1);
        const auto x=(b>-1?(info::d.second>0?((info::d.second>>b)&1):0):0);
        if(info::tr.check(i)[info::updr]>info::len){
            ++info::len;
            info::updl=i;
            if((!info::apr3)&&(!info::apr2)) res=2;
            else if(!info::apr3) res=(x?4:2);
            else res=2;
            if(!info::apr2) ++info::b1;
            info::apr2=true;
        }else if(info::tr.check(i)[info::updl]>info::len){
            ++info::len;
            info::updr=i;
            if((!info::apr3)&&(!info::apr2)) res=3;
            else if(!info::apr2) res=(x?4:3);
            else res=3;
            if(!info::apr3) ++info::b1;
            info::apr3=true;
        }else{
            res=x;
        }
    }
    return res;
}

pair<int,int> longest_path(vector<int> S){
    const auto N=(int)(S.size());
    auto las2=-1,las3=-1,fp2=-1,fp3=-1;
    for(auto i=N-1;i>N-11;--i){
        if(S[i]==2){
            las2=i;
            break;
        }
    }
    for(auto i=N-1;i>N-11;--i){
        if(S[i]==3){
            las3=i;
            break;
        }
    }
    cir(i,N-11,N){
        if(S[i]==2){
            fp2=i;
            break;
        }
    }
    cir(i,N-11,N){
        if(S[i]==3){
            fp3=i;
            break;
        }
    }
    if(las2>-1&&las3>-1){
        if(las3>las2){
            for(auto i=N-1;i>N-11;--i){
                if(S[i]==2||S[i]==4){
                    las2=i;
                    break;
                }
            }
        }else{
            for(auto i=N-1;i>N-11;--i){
                if(S[i]==3||S[i]==4){
                    las3=i;
                    break;
                }
            }
        }
        return pair(las2,las3);
    }
    if(las2>-1){
        for(auto i=N-1;i>N-11;--i){
            if(S[i]==2||S[i]==4){
                las2=i;
                break;
            }
        }
    }
    if(las3>-1){
        for(auto i=N-1;i>N-11;--i){
            if(S[i]==3||S[i]==4){
                las3=i;
                break;
            }
        }
    }
    const auto pos=(fp2>-1?fp2:fp3);
    [&]{
        auto w=0;
        cir(i,N-5,N-(pos==-1||pos<N-5)) if(i!=pos) (w<<=1)|=(S[i]==1||S[i]==4);
        if(w) las3=max(las3,w+N-23);
    }();
    [&]{
        auto w=0;
        cir(i,N-10,N-5-(pos==-1||pos>N-6)) if(i!=pos) (w<<=1)|=(S[i]==1||S[i]==4);
        if(w) las2=max(las2,w+N-23);
    }();
    [&]{
        auto w=0;
        cir(i,N-16,N-10) (w*=5)+=S[i];
        las3=max(las3,w);
    }();
    [&]{
        auto w=0;
        cir(i,N-22,N-16) (w*=5)+=S[i];
        las2=max(las2,w);
    }();
    return pair(las2,las3);
}
