#pragma GCC optimize("Ofast")
#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
ifstream fcin("c.in");
ofstream fcout("c.out");
class fileio{
public:
    ~fileio(){
        fcin.close();fcout.close();
    }
} use_fileio;
static constexpr auto _inf=(int)(1e9+7);
class graph{
private:
    vector<vector<int>> gr;
    vector<int> lcml,id;
    vector<set<int>> ban;
    // C++ 14
    constexpr auto lcm(auto a,auto b){
        return a/__gcd(a,b)*b;
    }
    auto bfs(int ux,int vx){
        const auto n=(int)(gr.size());
        deque<pair<int,int>> q;
        vector<vector<int>> dis(n),inq(n);
        cir(i,0,n) dis[i].resize(lcml[i],_inf),inq[i].resize(lcml[i]);
        cir(i,0,lcml[ux]) if(!ban[ux].count(i)) dis[ux][i]=i,inq[ux][i]=true,q.emplace_back(ux,i);
        while(!q.empty()){
            const auto[u,c]=q.front();q.pop_front();
            inq[u][c]=false;
            const auto rc=dis[u][c];
            for(auto&i:gr[u]) cir(delta,1,lcml[i]+1){
                if(ban[u].count((rc+delta-1)%lcml[u])) break;
                const auto nw=(rc+delta)%lcml[i];
                if(id[u]==id[i]&&ban[u].count(nw)&&ban[i].count((nw+lcml[i]-1)%lcml[i])) continue;
                if(ban[i].count(nw)) continue;
                if(dis[i][nw]<dis[u][c]+delta+1) break;
                dis[i][nw]=dis[u][c]+delta;
                if(!inq[i][nw]){
                    if((!q.empty())&&dis[i][nw]<dis[q.front().first][q.front().second]+1) q.emplace_front(i,nw);
                    q.emplace_back(i,nw);
                }
                inq[i][nw]=true;
            }
        }
        return*min_element(dis[vx].begin(),dis[vx].end());
    }
public:
    auto link(int u,int v){
        gr[u].emplace_back(v);
        gr[v].emplace_back(u);
    }
    auto initban(vector<vector<pair<int,int>>> _ban,vector<int> _id){
        id=_id;
        cir(i,0,(int)(gr.size())){
            lcml[i]=1;
            for(auto&[w,l]:_ban[i]) lcml[i]=lcm(lcml[i],l);
            for(auto&[w,l]:_ban[i]){
                auto c=w;
                while(c<lcml[i]) ban[i].emplace(c),c+=l;
            }
        }
        cir(u,0,(int)(id.size())) gr[u].emplace_back(u);
    }
    auto check(int s,int t){
        return bfs(s,t);
    }
    graph(int _n):gr(_n),lcml(_n),ban(_n){}
};
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int n,m;fcin>>n>>m;graph gr(n);
    cir(i,0,m){
        int u,v;fcin>>u>>v;--u;--v;
        gr.link(u,v);
    }
    int k;fcin>>k;
    vector<vector<pair<int,int>>> ban(n);
    vector<int> id(n,-1);
    cir(i,0,k){
        int l;fcin>>l;
        cir(c,0,l){
            int u;fcin>>u;--u;id[u]=i;
            ban[u].emplace_back(c,l);
        }
    }
    gr.initban(ban,id);
    const auto ans=gr.check(0,n-1);
    if(ans>_inf/2) fcout<<"impossible\n";
    else fcout<<ans<<'\n';
    return 0;
}
