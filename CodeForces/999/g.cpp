#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
class interactor{
public:
    auto getcases(){
        int T;cin>>T;
        return T;
    }
    auto getn(){
        int n;cin>>n;
        return n;
    }
    auto ask(int u,int v){
        println(cout,"? {} {}",u+1,v+1);
        cout.flush();
        int w;cin>>w;
        return w;
    }
    auto answer(int w){
        println(cout,"{}",w);
        cout.flush();
    }
    auto answer(vector<pair<int,int>> a){
        print(cout,"!");
        for(auto&[u,v]:a) print(cout," {} {}",u+1,v+1);
        println(cout);
        cout.flush();
    }
} interact;
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    auto T=interact.getcases();
    while(T--) []{
        const auto n=interact.getn();
        interact.answer((n+1)/3);
        vector<int> cur;
        map<pair<int,int>,int> col;
        queue<int> ux;
        auto color=[&](int u,int v,bool no_ask=false){
            if(u>v) swap(u,v);
            if(col.contains({u,v})) return col[{u,v}];
            if(no_ask) return -1;
            return col[{u,v}]=interact.ask(u,v);
        };
        cir(i,0,n) ux.emplace(i);
        vector<tuple<int,int,int>> tri;
        while((!ux.empty())){
            if(cur.empty()){
                if(ux.size()<2) break;
                const auto u=ux.front();
                ux.pop();
                const auto v=ux.front();
                ux.pop();
                cur.emplace_back(u);
                cur.emplace_back(v);
            }else{
                const auto u=ux.front();
                const auto v=cur.back();
                ux.pop();
                if(cur.size()==1){
                    cur.emplace_back(u);
                }else{
                    const auto w=cur[cur.size()-2];
                    if(color(u,v)==color(v,w)){
                        cur.emplace_back(u);
                    }else{
                        tri.emplace_back(u,v,w);
                        cur.pop_back();
                        cur.pop_back();
                    }
                }
            }
        }
        const auto c=(cur.size()<2?0:color(cur[0],cur[1]));
        vector<pair<int,int>> ans;
        for(auto i=0;i+1<(int)(cur.size());i+=2) ans.emplace_back(cur[i],cur[i+1]);
        for(auto&[u,v,w]:tri){
            if(color(u,v,true)==c){
                ans.emplace_back(u,v);
            }else if(color(v,w,true)==c){
                ans.emplace_back(v,w);
            }else{
                ans.emplace_back(u,w);
            }
        }
        ans.resize((n+1)/3);
        interact.answer(ans);
    }();
    return 0;
}
