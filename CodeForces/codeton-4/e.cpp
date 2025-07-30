#include<bits/extc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
class dsu{
private:
    vector<int> f;
public:
    auto findset(auto u)->int{
        return f[u]==u?u:f[u]=findset(f[u]);
    }
    auto merge(int u,int v){
        u=findset(u);v=findset(v);
        f[u]=v;
    }
    dsu(int _n):f(_n){ranges::iota(f,0);}
};
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int T;cin>>T;
    while(T--) []{
        int n,m;cin>>n>>m;
        vector<int> a(n);
        for(auto&i:a) cin>>i;
        vector<vector<int>> gr(n);
        cir(i,0,m){
            int u,v;cin>>u>>v;--u;--v;
            gr[u].emplace_back(v);
            gr[v].emplace_back(u);
        }
        dsu qwq(n);
        vector<int> id(n,-1);
        vector<int> cnt(n);
        vector<__gnu_pbds::priority_queue<pair<int,int>,greater<>>> q(n);
        cir(i,0,n) if((!a[i])&&(id[i]<0)){
            q[i].push({0,i});
            while(!q[i].empty()){
                const auto[w,u]=q[i].top();
                if(w>cnt[i]) break;
                q[i].pop();
                if(id[u]==-1){
                    id[u]=i;++cnt[i];
                    for(auto&v:gr[u]) q[i].push({a[v],v});
                    continue;
                }
                if(qwq.findset(id[u])==qwq.findset(id[i])) continue;
                q[i].join(q[qwq.findset(id[u])]);
                cnt[i]+=cnt[qwq.findset(id[u])];
                qwq.merge(id[u],id[i]);
            }
        }
        if(ranges::count(id,-1)) return cout<<"NO"<<'\n',void();
        set<int> x;
        for(auto&w:id) x.emplace(qwq.findset(w));
        cout<<(x.size()>1?"NO":"YES")<<'\n';
    }();
    return 0;
}
