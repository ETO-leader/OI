#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
class interactor{
public:
    static auto insert(int id){
        println(cout,"+ {}",id);
        cout.flush();
    }
    static auto remove(int id){
        println(cout,"- {}",id);
        cout.flush();
    }
    static auto ask(int u){
        println(cout,"? {}",u);
        cout.flush();
        int s;cin>>s;
        return s;
    }
    static auto answer(vector<int> x){
        print(cout,"!");
        for(auto&i:x) print(cout," {}",i);
        println(cout);
        cout.flush();
        int succ;cin>>succ;
        assert(succ);
    }
};
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int T;cin>>T;
    while(T--) []{
        int n,m;cin>>n>>m;
        vector<pair<int,int>> es(m);
        for(auto&[u,v]:es) cin>>u>>v,--u,--v;
        vector<vector<pair<int,int>>> gr(n);
        vector<int> ans(m);
        static constexpr auto k=20;
        cir(i,0,m){
            interactor::remove(i+1);
            auto connected=true;
            cir(c,0,k) connected&=interactor::ask(es[i].first+1);
            cir(c,0,k) connected&=interactor::ask(es[i].second+1);
            if(!connected){
                gr[es[i].first].emplace_back(es[i].second,i);
                gr[es[i].second].emplace_back(es[i].first,i);
                ans[i]=true;
                interactor::insert(i+1);
            }
        }
        cir(i,0,m) if(!ans[i]){
            const auto eid=[&](this auto __self,int u,int f){
                for(auto&[v,id]:gr[u]) if(v!=f){
                    if(v==es[i].second) return id;
                    const auto vx=__self(v,u);
                    if(vx>-1) return vx;
                }
                return -1;
            }(es[i].first,-1);
            interactor::remove(eid+1);
            interactor::insert(i+1);
            auto connected=true;
            cir(c,0,k) connected&=interactor::ask(es[i].first+1);
            cir(c,0,k) connected&=interactor::ask(es[i].second+1);
            ans[i]=connected;
            interactor::remove(i+1);
            interactor::insert(eid+1);
        }
        interactor::answer(ans);
    }();
    return 0;
}
