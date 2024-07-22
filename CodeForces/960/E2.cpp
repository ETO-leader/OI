#include<bits/stdc++.h>

#if not defined(ONLINE_JUDGE)

#include"grader.h"

#else

extern int checkml(int u){
    std::cout<<std::format("? {}",u)<<'\n';
    std::cout.flush();
    int tp;std::cin>>tp;
    return tp;
}

extern void answer(int u){
    std::cout<<std::format("! {}",u)<<'\n';
    std::cout.flush();
}

extern std::vector<std::pair<int,int>> init(){
    int n;std::cin>>n;
    std::vector<std::pair<int,int>> es(n-1);
    for(auto&[a,b]:es) std::cin>>a>>b;
    return es;
}

void findit();

int main(){
    std::ios::sync_with_stdio(false),std::cin.tie(0);
    int T;std::cin>>T;
    while(T--) findit();
    return 0;
}

#endif

#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;

class check{
private:
    vector<vector<int>> gr;
    vector<int> chs,fx;
    auto dfs(int u,int f=0)->int{
        fx[u]=f;
        for(auto&i:gr[u]) if(i!=f) chs[u]=max(chs[u],dfs(i,u)+1);
        return chs[u];
    }
    auto fnd(int u,const int sqr,int fx=0){
        vector<int> rlt;
        for(auto&i:gr[u]) if(i!=fx&&chs[i]>sqr-1) rlt.push_back(i);
        if(rlt.empty()) return u;
        for(auto&i:rlt){
            if(i==rlt.back()||checkml(i)) return fnd(i,sqr,u);
        }
        abort();
    }
public:
    auto insert(int u,int v){
        gr[u].push_back(v);
        gr[v].push_back(u);
    }
    auto play(){
        dfs(1);chs[0]=-1;
        const auto fdlf=ranges::find(chs,0)-chs.begin();
        const auto sqr=70;
        cir(i,0,sqr+2){
            if(checkml(fdlf)) return answer(fdlf);
        }
        const auto ux=fnd(1,sqr);
        vector<int> ns;
        for(auto u=ux;u;u=fx[u]) ns.push_back(u);
        ranges::reverse(ns);
        auto l=0,r=(int)(ns.size())-1,ans=(int)(ns.size())-1;
        while(l-1<r){
            for(auto x:{&l,&r,&ans}) (*x)=max(*x,0);
            const auto mid=midpoint(l,r);
            checkml(ns[mid])?(l=mid+1):((ans=mid-1),(r=mid-2),(--l));
        }
        ans=max(ans,0);
        auto un=ns[ans],vn=ns[ans];
        assert(vn==1||(!checkml(vn)));
        fx[1]=1;
        cir(i,0,2) un=fx[un];
        cir(i,0,5){
            if(!checkml(un)) break;
            checkml(vn);
        }
        answer(fx[fx[un]]);
    }
    check(int n):gr(n+1),chs(n+1),fx(n+1){}
};

void findit(){
    const auto es=init();
    const auto n=(int)(es.size())+1;
    check chk(n);
    for(auto&[u,v]:es) chk.insert(u,v);
    chk.play();
}
