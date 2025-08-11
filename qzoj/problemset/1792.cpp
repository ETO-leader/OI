#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
static constexpr auto _inf=(int)(1e9+7);
class graph{
private:
    vector<vector<pair<int,int>>> gr;
public:
    auto link(int u,int v,int w){
        gr[u].emplace_back(v,w);
        gr[v].emplace_back(u,w);
    }
    auto bfs(int s,int t){
        deque<int> q;
        vector<int> dis(gr.size(),_inf),vis(gr.size());
        dis[s]=0;
        q.emplace_back(s);
        while(!q.empty()){
            const auto x=q.front();q.pop_front();
            if(vis[x]) continue;
            vis[x]=true;
            for(auto&[v,w]:gr[x]) if(dis[v]>dis[x]+w){
                dis[v]=dis[x]+w;
                if(w) q.emplace_back(v);
                else q.emplace_front(v);
            }
        }
        return dis[t];
    }
    graph(int _n):gr(_n){}
};
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int T;cin>>T;
    while(T--) []{
        int n,m;cin>>n>>m;
        graph gr((n+1)*(m+1));
        cir(i,0,n){
            string s;cin>>s;
            cir(j,0,m) if(s[j]=='/'){
                gr.link(i*(m+1)+j,(i+1)*(m+1)+(j+1),1);
                gr.link(i*(m+1)+(j+1),(i+1)*(m+1)+j,0);
            }else{
                gr.link(i*(m+1)+j,(i+1)*(m+1)+(j+1),0);
                gr.link(i*(m+1)+(j+1),(i+1)*(m+1)+j,1);
            }
        }
        const auto ans=gr.bfs(0,(n+1)*(m+1)-1);
        if(ans==_inf) cout<<"NO SOLUTION"<<'\n';
        else cout<<ans<<'\n';
    }();
    return 0;
}
