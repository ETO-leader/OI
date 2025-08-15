#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
static constexpr auto _inf=(int)(1e9+7);
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int T;cin>>T;
    while(T--) []{
        int n,m,k;cin>>n>>m>>k;
        vector<vector<int>> vx(n);
        map<pair<int,int>,int> col;
        vector<tuple<int,int,int>> es;
        cir(i,0,m){
            int u,v,c;cin>>u>>v>>c;--u;--v;
            vx[u].emplace_back(v);
            vx[v].emplace_back(u);
            col[{u,v}]=col[{v,u}]=c;
            es.emplace_back(u,v,c);
        }
        if(n-1==m){
            cout<<"Yes"<<'\n';
        }else if(n==m){
            stack<int> stc;
            vector<int> vis(n);
            vector<int> circ;
            auto dfs=[&](auto __self,int u,int f)->bool {
                stc.emplace(u);vis[u]=true;
                for(auto&i:vx[u]) if(i!=f){
                    if(vis[i]){
                        auto x=-1;
                        while(x!=i){
                            x=stc.top();stc.pop();
                            circ.emplace_back(x);
                        }
                        return true;
                    }
                    if(__self(__self,i,u)) return true;
                }
                stc.pop();
                return false;
            };
            dfs(dfs,0,-1);
            auto ok=false;
            cir(i,0,(int)(circ.size())){
                const auto u=circ[i],v=circ[(i+1)%circ.size()],w=circ[(i+2)%circ.size()];
                ok|=(col[{u,v}]==col[{v,w}]);
            }
            cout<<(ok?"Yes":"No")<<'\n';
        }else{
            vector<int> del(n);
            auto ok=true;
            cir(i,0,n-1){
                vector<set<int>> col(n);
                vector<int> cnt(n);
                for(auto&[u,v,w]:es) if((!del[u])&&(!del[v])){
                    col[u].emplace(w);
                    col[v].emplace(w);
                    ++cnt[u];++cnt[v];
                }
                auto mn=pair(_inf,-1);
                cir(i,0,n) if(col[i].size()<2&&cnt[i]<3) mn=min(mn,pair(cnt[i],i));
                if(mn.second==-1){
                    ok=false;break;
                }
                del[mn.second]=true;
            }
            cout<<(ok?"Yes":"No")<<'\n';
        }
    }();
    return 0;
}
