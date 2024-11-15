#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int T;cin>>T;
    while(T--) [&](){
        int n,m;cin>>n>>m;
        set<int> endn;
        vector<vector<int>> to(n);
        cir(i,0,m){
            int u,v;cin>>u>>v;--u;--v;
            if(u>v) swap(u,v);
            if(v<n-1) to[u].push_back(v);
            else if(endn.count(u)) endn.erase(u);
            else endn.insert(u);
        }
        vector<tuple<int,int,int>> ans;
        cir(u,0,n-1){
            for(auto&v:to[u]){
                ans.emplace_back(u+1,v+1,n);
                if(endn.count(u)) endn.erase(u);
                else endn.insert(u);
                if(endn.count(v)) endn.erase(v);
                else endn.insert(v);
            }
        }
        if(endn.empty()){
            println("{}",ans.size());
            for(auto&[u,v,w]:ans) println("{} {} {}",u,v,w);
            return;
        }
        const auto x=*endn.begin();
        auto cur=n-1;
        cir(i,0,n-1) if(!endn.count(i)){
            ans.emplace_back(cur+1,x+1,i+1);
            cur=i;
        }
        println("{}",ans.size());
        for(auto&[u,v,w]:ans) println("{} {} {}",u,v,w);
    }();
    return 0;
}
