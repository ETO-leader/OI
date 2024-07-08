#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
const int _inf=1e9+7;
struct medicine{int d,rx,afu,saf;};
vector<int> D,vis;
vector<medicine> vm;
//int dfs(int st){
//    if(!st) return 0;
//    if(ins[st]) return _inf;
//    if(vis[st]) return D[st];
//    ins[st]=true;
//    for(auto&[d,rx,x,y]:vm) if(st&rx){
//        D[st]=min(D[st],dfs((st&x)|y)+d);
//    }
//    ins[st]=false;vis[st]=true;
//    return D[st];
//}
int to_int(string&s){
    int res=0;
    cir(i,0,s.size())
        res+=((int)(s[i]-'0')<<i);
    return res;
}
struct heapnode{
    int v,w;
    bool operator<(const heapnode&hp) const{
        return w>hp.w;
    }
};
void dijkstra(int st){
    priority_queue<heapnode> pq;pq.push({st,0});
    D[st]=0;
    while(!pq.empty()){
        auto [u,w]=pq.top();pq.pop();
        if(vis[u]) continue;
        vis[u]=true;
        for(auto&[d,rx,x,y]:vm){
            const int v=((u&x)|y);
            if(vis[v]||(D[v]<=w+d)) continue;
            D[v]=w+d;
            pq.push({v,w+d});
        }
    }
}
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int T;cin>>T;
    while(T--){
        int n,m;cin>>n>>m;
        const int fullset=(1<<n)-1;
        D.clear();vm.clear();
        D.resize(1<<n,_inf);
        vis.clear();vis.resize(1<<n);
        vm.resize(m);
        string st;cin>>st;
        const int state=to_int(st);
        for(auto&i:vm){
            string s1,s2;int d;cin>>d>>s1>>s2;
            i={d,to_int(s1),
                fullset^to_int(s1),to_int(s2)};
        }
        dijkstra(state);
        int d=D[0];
        if(d==_inf) cout<<-1<<'\n';
        else cout<<d<<'\n';
    }
    return 0;
}
