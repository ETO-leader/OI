#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
class tree{
private:
    vector<vector<int>> gr;
    vector<int> dis,vis;
    auto bfs(){
        queue<int> q;
        cir(i,0,(int)(gr.size())) if(gr[i].size()==1) q.emplace(i),vis[i]=true;
        while(!q.empty()){
            const auto u=q.front();q.pop();
            for(auto&v:gr[u]) if(!vis[v]){
                dis[v]=dis[u]+1;vis[v]=true;
                q.emplace(v);
            }
        }
    }
    auto check(int u,lint&ans,lint cgr,int f=-1)->int{
        auto cnt=(int)(dis[u]>1);
        for(auto&i:gr[u]) if(i!=f){
            const auto c=check(i,ans,cgr,u);
            cnt+=c;
            if(dis[i]==1&&dis[u]) ans+=c;
        }
        if(f>-1&&dis[f]==1&&dis[u]) ans+=(cgr-cnt);
        return cnt;
    }
public:
    auto link(int u,int v){
        gr[u].emplace_back(v);
        gr[v].emplace_back(u);
    }
    auto check(){
        bfs();
        auto cgr=0,cok=0;
        for(auto&i:dis) cgr+=i>1,cok+=(bool)(i);
        auto ans=0ll;
        for(auto&i:dis) if(!i) ans+=cok;
        check(0,ans,cgr);
        return ans;
    }
    tree(int _n):gr(_n),dis(_n),vis(_n){}
};
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int T;cin>>T;
    while(T--) [&]{
        int n;cin>>n;tree gr(n);
        cir(i,0,n-1){
            int u,v;cin>>u>>v;--u;--v;
            gr.link(u,v);
        }
        cout<<gr.check()<<'\n';
    }();
    return 0;
}
