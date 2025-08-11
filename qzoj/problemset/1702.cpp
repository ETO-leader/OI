#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
static constexpr auto _infl=(lint)(1e16l);
class graph{
private:
    vector<vector<pair<int,lint>>> gr;
public:
    auto link(int u,int v,lint w){
        gr[u].emplace_back(v,w);
    }
    auto spfa(int s){
        const auto n=(int)(gr.size());
        queue<int> q;q.emplace(s);
        vector<lint> dis(n,_infl);
        vector<int> inq(n),visc(n);
        dis[s]=0;
        while(!q.empty()){
            const auto u=q.front();q.pop();
            inq[u]=false;
            if((++visc[u])>200) return false;
            for(auto&[v,w]:gr[u]) if(dis[u]+w<dis[v]){
                dis[v]=dis[u]+w;
                if(!inq[v]) q.emplace(v);
                inq[v]=true;
            }
        }
        return true;
    }
    graph(int _n):gr(_n){}
};
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int n,a,b;cin>>n>>a>>b;
    graph gr(n+1);
    cir(i,0,a){
        int u,v,d;cin>>u>>v>>d;
        if(u>v) swap(u,v);
        gr.link(v,u,d);
    }
    cir(i,0,b){
        int u,v,d;cin>>u>>v>>d;
        if(u>v) swap(u,v);
        gr.link(u,v,-d);
    }
    cir(i,1,n+1) gr.link(0,i,0);
    auto l=0ll,r=_infl,ans=-1ll;
    while(l-1<r){
        const auto mid=(l+r)/2;
        auto ngr=gr;
        ngr.link(1,n,-mid);
        ngr.spfa(0)?((l=mid+1),(ans=mid)):(r=mid-1);
    }
    if(ans==_infl) cout<<-2<<'\n';
    else cout<<ans<<'\n';
    return 0;
}
