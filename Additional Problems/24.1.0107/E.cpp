#include"train.h"
#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using VI=vector<int>;
vector<VI> gr,f;
template<bool tp>
auto chkisf(VI&a,VI&st,VI&r,int n){
    VI res(n),inx(n);
    queue<int> q;
    cir(i,0,n) if(r[i]&&st[i]){
        q.push(i);res[i]=true;
    }
    cir(i,0,n) for(auto&x:gr[i]) if(st[x]){
        (a[i]!=tp?++inx[i]:inx[i]=1);
    }
    while(!q.empty()){
        auto u=q.front();q.pop();
        for(auto&i:f[u]) if((!res[i])&&st[i]){
            if(!(--inx[i])) q.push(i),res[i]=true;
        }
    }
    return res;
}
VI who_wins(VI a,VI r,VI u,VI v){
    const int n=a.size(),m=u.size();
    gr.resize(n);f.resize(n);
    cir(i,0,m){
        gr[u[i]].push_back(v[i]);
        f[v[i]].push_back(u[i]);
    }
    VI res(n,true);
    while(true) try{
        auto fx=chkisf<true>(a,res,r,n);
        [&](){
            cir(i,0,n) if((!fx[i])&&res[i])
                return;
            throw (string)("not found");
        }();
        for(auto&i:fx) i^=1;
        auto fg=chkisf<false>(a,res,fx,n);
        cir(i,0,n) if(fg[i]) res[i]=false;
    }catch(string){break;}
    return res;
}
