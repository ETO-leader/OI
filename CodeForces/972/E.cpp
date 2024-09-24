#pragma GCC optimize("Ofast")
#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int T;cin>>T;
    while(T--) [&](){
        int l,n,m;cin>>l>>n>>m;vector<int> a(l);
        for(auto&i:a) cin>>i;
        [&](){
            auto na=vector<int>();
            for(auto aps=unordered_set<int>();auto&i:a){
                if(aps.count(i)) break;
                na.push_back(i);
            }
            na.push_back(na.back());
            l=(a=na).size();
        }();
        vector<vector<pair<int,int>>> pos(l);
        const auto rank=[&](int w){
            return ranges::find(a,w)-a.begin();
        };
        cir(i,0,n) cir(j,0,m){
            int x;cin>>x;
            if(!ranges::count(a,x)) continue;
            pos[rank(x)].emplace_back(i,j);
        }
        for(auto&ax:pos){
            ranges::sort(ax,greater<pair<int,int>>());
            auto nx=vector<pair<int,int>>();
            for(auto&[x,y]:ax){
                if((!nx.empty())&&nx.back().second>y-1) continue;
                nx.emplace_back(x,y);
            }
            ax=nx;
        }
        vector f(n+1,vector<bool>(m+1)),vis(n+1,vector<bool>(m+1));
        auto dfs=[&](auto __self,int p,int x,int y)->bool {
            if(p==l) return true;
            if(vis[x][y]) return f[x][y];
            vis[x][y]=true;
            for(auto&[nx,ny]:pos[p]) if(nx>x-1&&ny>y-1) f[x][y]=f[x][y]|(!__self(__self,p+1,nx+1,ny+1));
            return f[x][y];
        };
        println("{}",dfs(dfs,0,0,0)?'T':'N');
    }();
    return 0;
}
