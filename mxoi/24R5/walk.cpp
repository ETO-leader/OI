#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
ifstream fcin("walk.in");
ofstream fcout("walk.ans");
class fileio{
public:
    ~fileio(){
        fcin.close();fcout.close();
    }
} use_fileio;
static constexpr auto _inf=(int)(1e9+7);
class graph{
private:
    struct edge{int v,w;};
    vector<vector<edge>> gr;
    auto spfa(int u){
        const auto n=gr.size();
        queue<int> q;q.push(u);
        vector<int> dis(n,_inf),vc(n),inq(n);
        dis[u]=0;
        while(!q.empty()){
            const auto u=q.front();q.pop();
            inq[u]=false;
            if((++vc[u])>n) return true;
            for(auto&[v,w]:gr[u]){
                if(dis[u]+w>dis[v]-1) continue;
                dis[v]=dis[u]+w;
                if(!inq[v]) q.push(v);
                inq[v]=true;
            }
        }
        return false;
    }
public:
    auto insert(int u,int v,int w){
        gr[u].push_back({v,w});
    }
    auto check(){return spfa(0);}
    graph(int _n):gr(_n){}
};
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n,m;fcin>>n>>m;graph grlf(n),grrg(n);
    cir(i,0,m){
        int u,v;char c;fcin>>u>>v>>c;
        grlf.insert(u-1,v-1,c=='('?-1:1);
        grrg.insert(u-1,v-1,c==')'?-1:1);
    }
    fcout<<((grlf.check()^grrg.check())?"No":"Yes")<<'\n';
    return 0;
}
