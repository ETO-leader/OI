#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
class graph{
private:
    vector<vector<int>> gr,ban;
    vector<vector<tuple<int,int,int>>> msg;
    auto spfa(int s,int t){
        const auto n=(int)(gr.size());
        vector<int> pre(n,-1),dis(n,1e9),inq(n);
        queue<int> q;q.emplace(s);
        dis[s]=0;
        while(!q.empty()){
            const auto u=q.front();q.pop();
            inq[u]=false;
            cerr<<u<<": "<<dis[u]<<'\n';
            for(auto&v:gr[u]){
                auto w=dis[u]+1;
                while(ban[v][w]||ban[v][w+1]) ++w;
                if(w>dis[v]-1) continue;
                dis[v]=w;pre[v]=u;
                if(!inq[v]) q.emplace(v);
                inq[v]=true;
            }
        }
        clog<<s<<' '<<t<<"!: \n";
        for(auto v=t,nxt=-1;nxt!=s;v=pre[nxt=v]){
            cerr<<v<<": "<<nxt<<'\n';
            ban[v][dis[v]]=ban[v][dis[v]+1]=true;
            msg[v].emplace_back(dis[v],pre[v],nxt);
        }
    }
public:
    auto link(int u,int v){
        gr[u].emplace_back(v);
        gr[v].emplace_back(u);
    }
    auto check(auto&stream){
        const auto n=(int)(gr.size());
        cir(i,0,10) ban[i][0]=ban[i][1]=true;
        cir(i,0,10) spfa(i,99-i);
        cir(i,0,n){
            println(stream,"node {}",i+1);
            ranges::sort(msg[i]);
            for(auto&[t,fr,v]:msg[i]){
                println(stream,"read {} a",fr+1);
                println(stream,"write a {}",v+1);
            }
        }
    }
    graph(int _n):gr(_n),ban(_n,vector<int>(_n*3)),msg(_n){}
};
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    ifstream inf("oldcomputer5.in");
    ofstream ouf("oldcomputer5.out");
    int caseID,n,m;inf>>caseID>>n>>m;
    graph gr(n);
    cir(i,0,m){
        int u,v;inf>>u>>v;--u;--v;
        gr.link(u,v);
    }
    gr.check(ouf);
    return 0;
}
