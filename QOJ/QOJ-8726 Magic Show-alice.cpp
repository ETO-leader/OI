#include"Alice.h"
#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;

static constexpr auto basic_seed=7355608;

class dsu{
private:
    vector<int> a;
public:
    auto findset(int u)->int{
        return a[u]==u?u:a[u]=findset(a[u]);
    }
    auto merge(int u,int v){
        a[findset(u)]=findset(v);
    }
    dsu(int _n):a(_n){iota(a.begin(),a.end(),0);}
};

vector<pair<int,int>> Alice(){
    mt19937_64 eng(basic_seed);
    static constexpr auto n=4200;
    const auto x=setN(n);
    vector<int> id(n);
    iota(id.begin(),id.end(),0);
    shuffle(id.begin(),id.end(),eng);
    const auto _seed=random_device().operator()()&1023;
    mt19937_64 ueng(random_device().operator()());
    vector<pair<int,int>> res;
    dsu d(n);
    auto connect=[&](auto u,auto v){
        d.merge(u,v);
        res.emplace_back(u,v);
    };
    auto random_connect=[&](auto u,auto ban){
        while(true){
            const auto v=uniform_int_distribution<int>(0,n-1)(ueng);
            if(v!=ban&&d.findset(u)!=d.findset(v)){
                connect(u,v);
                break;
            }
        }
    };
    // send seed2
    cir(i,0,30){
        cir(b,0,10) ((_seed>>b)&1)?connect(id[i*20+b+10],id[i*20+b]):random_connect(id[i*20+b],id[i*20+b+10]);
        cir(b,0,10) random_connect(id[i*20+b+10],id[i*20+b]);
    }
    // get seed 2 rank
    mt19937_64 shuffle_eng(_seed);
    shuffle(id.begin()+600,id.end(),shuffle_eng);
    // send number
    cir(i,0,30){
        cir(b,0,60) ((x>>b)&1)?connect(id[i*120+b+660],id[i*120+b+600]):random_connect(id[i*120+b+600],id[i*120+b+660]);
        cir(b,0,60) if(i*120+b+660<n-1) random_connect(id[i*120+b+660],id[i*120+b+600]);
    }
    for(auto&[a,b]:res){
        ++a;++b;
        if(uniform_int_distribution<int>(0,1)(shuffle_eng)) swap(a,b);
    }
    clog<<res.size()<<'\n';
    shuffle(res.begin(),res.end(),shuffle_eng);
    return res;
}

