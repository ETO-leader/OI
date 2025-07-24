#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
class tree{
private:
    vector<vector<int>> gr;
    vector<int> uv,vv;
    auto dfs(int u,int f=-1)->pair<int,int>{
        for(auto&i:gr[u]) if(i!=f){
            const auto[xi,yi]=dfs(i,u);
            if(xi>-1) uv[u]=max(uv[u],xi+1);
            if(yi>-1) vv[u]=max(vv[u],yi+1);
        }
        return pair(uv[u],vv[u]);
    }
public:
    auto link(int u,int v){
        gr[u].emplace_back(v);
        gr[v].emplace_back(u);
    }
    auto check(const int d){
        dfs(0);
        auto ans=((int)(gr.size())-1)*4;
        cir(i,1,(int)(gr.size())){
            if(uv[i]<0&&vv[i]<0){
                ans-=4;
            }else if(uv[i]<d&&vv[i]<0){
                ans-=2;
            }else if(vv[i]<d&&uv[i]<0){
                ans-=2;
            }
        }
        return ans;
    }
    auto setu(int u){uv[u]=0;}
    auto setv(int u){vv[u]=0;}
    tree(int _n):gr(_n),uv(_n,-1),vv(_n,-1){}
};
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    auto T=1;
    while(T--) [&]{
        int n,d;cin>>n>>d;tree gr(n);
        cir(i,0,n-1){
            int u,v;cin>>u>>v;--u;--v;
            gr.link(u,v);
        }
        int c;cin>>c;
        cir(i,0,c){
            int u;cin>>u;--u;
            gr.setu(u);
        }
        cin>>c;
        cir(i,0,c){
            int u;cin>>u;--u;
            gr.setv(u);
        }
        cout<<gr.check(d)<<'\n';
    }();
    return 0;
}
