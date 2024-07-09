#include<bits/stdc++.h>

#if not defined(ONLINE_JUDGE)   // For grader interactive (local/OI/THU)

#include"grader.h"

#else                           // For I/O interactive (CodeForces/ICPC)

#include<vector>
#include<string>

#if not defined(__GRADER_H)

#define __GRADER_H 1

extern std::vector<bool> Relation(std::vector<std::pair<int,int>> rls){
    std::cout<<'A'<<' '<<rls.size()<<' ';
    for(auto&[a,b]:rls) std::cout<<a<<' '<<b<<' ';
    std::cout<<'\n';
    std::cout.flush();
    std::string resx;std::cin>>resx;
    std::vector<bool> res;
    for(auto&c:resx) res.push_back(c-'0');
    return res;
}

extern void Answer(std::vector<int> a,std::vector<int> b,std::vector<int> c){
    std::cout<<'Q'<<' '<<a.size()<<' '<<b.size()<<' '<<c.size()<<'\n';
    for(auto&x:{a,b,c}){
        for(auto&i:x) std::cout<<i<<' ';
        std::cout<<'\n';
    }
    std::cout.flush();
}

extern int CoinCount(){
    int n;std::cin>>n;
    return n;
}

extern void Coins();

int main(){
    std::ios::sync_with_stdio(false),std::cin.tie(0);
    int T;std::cin>>T;
    while(T--) Coins();
    return 0;
}

#endif

#endif

#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
class dsu{
private:
    vector<int> f;
public:
    auto findset(int u)->int{
        return f[u]==u?u:f[u]=findset(f[u]);
    }
    auto merge(int u,int v){
        u=findset(u);v=findset(v);
        if(u>v) swap(u,v);
        f[u]=v;
    }
    dsu(int _n):f(_n){iota(f.begin(),f.end(),0);}
};

void Coins(){
    const auto n=CoinCount();
    dsu ds(n);
    [&](){
        vector<pair<int,int>> ask;
        for(auto i=0;i+1<n;i+=2){
            ask.push_back({i+1,i+2});
        }
        const auto res=Relation(ask);
        for(auto i=0;i+1<n;i+=2) if(res[i/2]){
            ds.merge(i,i+1);
        }
    }();
    [&](){
        vector<pair<int,int>> ask;
        for(auto i=1;i+1<n;i+=2){
            ask.push_back({i+1,i+2});
        }
        const auto res=Relation(ask);
        for(auto i=1;i+1<n;i+=2) if(res[i/2]){
            ds.merge(i,i+1);
        }
    }();
    set<int> posx;
    cir(i,0,n) posx.insert(ds.findset(i));
    vector<int> blocks(posx.begin(),posx.end());
    const auto k=(int)(blocks.size());
    vector<int> samenxt(k);
    auto upd=[&](vector<bool> x){
        cir(i,0,k) samenxt[i]|=x[i];
    };
    cir(m,0,4){
        vector<pair<int,int>> ask;
        cir(i,0,k) if(i%4==m&&i+2<k){
            ask.push_back({blocks[i]+1,blocks[i+2]+1});
        }
        upd(Relation(ask));
    }
    vector<int> col;
    array<vector<int>,3> cls;
    col[0]=0;col[1]=2;
    auto mex=[&](int x,int y){
        set ax{0,1,2};
        if(ax.count(x)) ax.erase(x);
        if(ax.count(y)) ax.erase(y);
        return *ax.begin();
    };
    blocks.push_back(n);
    cir(i,2,k){
        if(samenxt[i-2]) col[i]=col[i-2];
        else col[i]=mex(col[i-2],col[i-1]);
        cir(x,blocks[i],blocks[i+1]) cls[col[i]].push_back(x+1);
    }
    Answer(cls[0],cls[1],cls[2]);
}
