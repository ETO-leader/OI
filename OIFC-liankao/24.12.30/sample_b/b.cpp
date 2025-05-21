#include"b.h"
#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;

static constexpr auto _inf=(int)(1e9+7);

class random_engine{
private:
    mt19937 eng;
public:
    template<typename _Ty>
    auto randint(auto l,auto r){
        return uniform_int_distribution<_Ty>(l,r);
    }
    auto shuffle(auto&x){
        std::shuffle(x.begin(),x.end(),eng);
    }
    random_engine():eng(
        #ifdef ONLINE_JUDGE
            random_device().operator()()
        #else
            251
        #endif    
    ){}
} rnd;

class tree{
private:
    vector<unordered_set<int>> ch,fx;
    vector<vector<int>> cv;
    vector<int> vis;
    auto chkchild(int u,vector<int> cur){
        if(cur.empty()) return;
        if(!count(cur.begin(),cur.end(),1)) cur.emplace_back(1);
        if(!Ask(u+1,cur)) return [&]{for(auto&i:cur) if(fx[i-1].count(u)) fx[i-1].extract(u);}();
        cur.erase(find(cur.begin(),cur.end(),1));
        if(cur.size()==1) return ch[u].emplace(cur[0]-1),fx[cur[0]-1].emplace(u),void();
        const auto mid=(int)(cur.size())/2;
        chkchild(u,vector(cur.begin(),cur.begin()+mid));
        chkchild(u,vector(cur.begin()+mid,cur.end()));
    }
    auto updchild(int u,unordered_set<int> v){
        if(vis[u]) return;
        vis[u]=true;
        auto ax=vector(v.begin(),v.end());
        if(count(ax.begin(),ax.end(),u)) ax.erase(find(ax.begin(),ax.end(),u));
        for(auto&i:ax) ++i;
        chkchild(u,ax);
        for(auto&i:ax) cv[u].emplace_back(i-1);
        cv[u]=vector(ch[u].begin(),ch[u].end());
        rnd.shuffle(cv[u]);
        for(auto&i:cv[u]) if(!vis[i]){
            updchild(i,ch[u]);
            for(auto&c:cv[i]) ch[u].extract(c); 
        }
    }
    int n;
public:
    auto build(){
        vector<int> ans(n),ord(n);
        iota(ord.begin(),ord.end(),0);
        rnd.shuffle(ord);
        unordered_set vaild(ord.begin(),ord.end());
        for(auto&u:ord) if(!vis[u]){
            updchild(u,vaild);
            for(auto&c:cv[u]) vaild.extract(c);
        }
        cir(i,0,n){
            vector<int> chk;
            cir(u,0,n) if(fx[u].size()==1){
                ans[u]=*fx[u].begin();
                fx[u].clear();
                chk.emplace_back(ans[u]);
            }
            cir(v,0,n) for(auto&x:chk) if(fx[v].count(x)) fx[v].extract(x);
        }
        return ans;
    }
    tree(int _n):ch(_n),fx(_n),vis(_n),cv(_n),n(_n){}
};

vector<pair<int,int>> Solve(int n,int){
    vector<pair<int,int>> res;
    const auto fx=tree(n).build();
    cir(i,1,n) res.emplace_back(fx[i]+1,i+1);
    return res;
}

#undef cir
