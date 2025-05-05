#include"koala.h"
#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;

class local_prechecker{
public:
    const auto cost(int N,int W,vector<int> c) const{
        vector g(N,vector<int>(W+1));
        vector<int> f(W+1),h(W+1);
        cir(i,0,N){
            const auto lf=f,lh=h;
            cir(w,0,W+1) if(w+c[i]+1<W+1){
                if(pair(lf[w]+(i+1),lh[w]+1)>pair(f[w+c[i]+1],h[w+c[i]+1])){
                    f[w+c[i]+1]=lf[w]+(i+1);
                    h[w+c[i]+1]=lh[w]+1;
                    g[i][w+c[i]+1]=1;
                }
            }
        }
        vector<int> result(N);
        auto u=W;
        for(auto i=N-1;~i;--i){
            result[i]=g[i][u]*(c[i]+1);
            u-=g[i][u]*(c[i]+1);
        }
        return result;
    }
};

int minValue(int N,int W){
    vector<int> st(N),usr(N);
    st[0]=1;
    playRound(st.data(),usr.data());
    return ranges::find(usr,0)-usr.begin();
}

int maxValue(int N,int W){
    vector<int> q(N),vaild(N),info(N),uinfo;
    ranges::iota(info,0);
    auto round=[&]{
        ranges::fill(q,0);
        for(auto&i:info) q[i]=W/(int)(info.size());
        playRound(q.data(),vaild.data());
        uinfo=info;info.clear();
        for(auto&i:uinfo) if(vaild[i]) info.emplace_back(i);
        return info.size()==1;
    };
    while(!round());
    return info[0];
}

int greaterValue(int N,int W){
    auto l=0,r=min(W/2,15);
    vector<int> ans(N);
    while(l-1<r){
        const auto mid=midpoint(l,r);
        vector<int> st(N),vaild(N);
        st[0]=st[1]=mid;
        playRound(st.data(),vaild.data());
        if((bool)(vaild[0])!=(bool)(vaild[1])){
            ans=vaild;break;
        }
        vaild[0]?(l=mid+1):(r=mid-1);
    }
    return !ans[0];
}

void allValues(int N,int W,int*P){
    if(W==2*N){
        vector<int> rnk(N);
        ranges::iota(rnk,0);
        ranges::stable_sort(rnk,[&](auto a,auto b){
            vector<int> st(N),vaild(N);
            st[a]=st[b]=N;
            playRound(st.data(),vaild.data());
            return vaild[a]<vaild[b];
        });
        cir(i,0,N) P[rnk[i]]=i+1;
    }else{
        auto valrange=[&](auto __self,int l,int r,vector<int> lst){
            if(l==r){
                assert(lst.size()==1);
                P[lst[0]]=l;
                return;
            }
            auto ul=0,ur=W/(int)(lst.size()),ans=0;
            while(ul-1<ur){
                const auto mid=midpoint(ul,ur);
                vector<int> q(N);
                cir(i,l-1,r) q[i]=mid;
                const auto vaild=local_prechecker().cost(N,W,q);
                auto okf=false,okt=false;
                cir(i,l-1,r) (vaild[i]?okt:okf)|=true;
                if(okf&&okt){
                    ans=mid;break;
                }
                okf?(ur=mid-1):(ul=mid+1);
            }
            vector<int> st(N),vaild(N);
            for(auto&i:lst) st[i]=ans;
            playRound(st.data(),vaild.data());
            vector<int> lef,rig;
            for(auto&i:lst) (vaild[i]?rig:lef).emplace_back(i);
            __self(__self,l,l+(int)(lef.size())-1,lef);
            __self(__self,l+(int)(lef.size()),r,rig);
        };
        valrange(valrange,1,N,[&]{
            vector<int> res(N);
            ranges::iota(res,0);
            return res;
        }());
    }
}
