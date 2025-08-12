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
            if((++visc[u])>n) return false;
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
    int T;cin>>T;
    while(T--) []{
        const auto n=24;
        vector<int> c(n);
        for(auto&i:c) cin>>i;
        int m;cin>>m;
        vector<int> cnt(n);
        cir(i,0,m){
            int t;cin>>t;++cnt[t];
        }
        auto l=0,r=m,ans=-1;
        while(l-1<r){
            const auto mid=(l+r)/2;
            graph gr(n+7);
            const auto s=n+6;
            gr.link(0,n,mid);
            gr.link(n,0,-mid);
            cir(i,0,n) gr.link(i,i+1,cnt[i]),gr.link(i+1,i,0);
            cir(i,7,n) gr.link(i+1,i-7,-c[i]);
            cir(i,0,7) gr.link(i+1,n-7+i,mid-c[i]); 
            cir(i,0,n+1) gr.link(s,i,0);
            gr.spfa(s)?((r=mid-1),(ans=mid)):(l=mid+1);
        }
        if(ans==-1) cout<<"No Solution"<<'\n';
        else cout<<ans<<'\n';
    }();
    return 0;
}
