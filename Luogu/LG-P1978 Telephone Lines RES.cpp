#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
template<typename T>
struct graph{
    struct edge{int u;T w;};
    vector<vector<edge>> G;int n;
    T _inf;
    graph(int _n):G(_n+1),n(_n){_inf=numeric_limits<T>::max()/2;}
    void insert(int u,int v,T w){
        G[u].push_back({v,w});G[v].push_back({u,w});
    }
    int count_max(T mxd){
        deque<int> q;q.push_back(1);
        vector<T> D(n+1,_inf);vector<bool> vis(n+1);
        D[1]=0;
        while(!q.empty()){
            auto f=q.front();q.pop_front();
            if(vis[f]) continue;
            vis[f]=true;
            for(auto&i:G[f]){
                int Ad=(i.w>mxd);
                if(vis[i.u]||D[f]+Ad>=D[i.u]) continue;
                Ad?q.push_back(i.u):q.push_front(i.u);
                D[i.u]=D[f]+Ad;
            }
        }
        return D[n];
    }
    void GotE(){
        int u,v;T w;cin>>u>>v>>w;
        insert(u,v,w);
    }
};
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n,p,k;cin>>n>>p>>k;
    graph<int> G(n);
    cir(i,0,p) G.GotE();
    int l=0,r=1e9+7,ans=-1;
    while(r>=l){
        int mid=l+(r-l)/2;
        G.count_max(mid)<=k?r=mid-1,ans=mid:l=mid+1;
    }
    cout<<ans<<endl;
    return 0;
}