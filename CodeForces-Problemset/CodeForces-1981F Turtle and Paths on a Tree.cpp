#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
static constexpr auto _inf=(int)(1e9+7);
class tree{
private:
    vector<vector<int>> gr,f;
    vector<int> a;
    auto dfs(int u,const auto mx){
        f[u].resize(mx+7);
        if(gr[u].empty()){
            if(a[u]<mx+7) f[u][a[u]]=_inf;
            return;
        }
        if(gr[u].size()==1) {
            const auto v=gr[u][0];
            dfs(v,mx);
            auto mn=_inf;
            cir(i,1,mx+7) if(i!=a[u]){
                mn=min(mn,f[v][i]+i);
            }
            if(u==1) throw mn;
            cir(i,1,mx+7){
                f[u][i]=(i==a[u]?_inf:min(f[v][i],mn));
            }
            return;
        }
        const auto vx=gr[u][0],vy=gr[u][1];
        dfs(vx,mx);dfs(vy,mx);
        auto mnx=_inf,mny=_inf,mn=_inf;
        cir(i,1,mx+7) if(i!=a[u]){
            mnx=min(mnx,f[vx][i]+i);
            mny=min(mny,f[vy][i]+i);
            mn=min(mn,f[vx][i]+f[vy][i]+i);
        }
        mn=min(mn,mnx+mny);
        if(u==1) throw mn;
        cir(i,1,mx+7){
            f[u][i]=(i==a[u]?_inf:min({f[vx][i]+mny,f[vy][i]+mnx,mn}));
        }
    }
public:
    auto insert(int u,int f){
        gr[f].push_back(u);
    }
    auto check(){
        const auto n=(int)(gr.size())-1;
        try{
            dfs(1,min(n,4000));
        }catch(int ans){
            return ans;
        }
        return -1;
    }
    tree(vector<int> ax):gr(ax.size()),f(ax.size()),a(ax){}
};
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int T;cin>>T;
    while(T--) [&](){
        int n;cin>>n;vector<int> a(n+1);
        cir(i,1,n+1) cin>>a[i];
        tree gr(a);
        cir(i,2,n+1){
            int f;cin>>f;gr.insert(i,f);
        }
        cout<<gr.check()<<'\n';
    }();
    return 0;
}
