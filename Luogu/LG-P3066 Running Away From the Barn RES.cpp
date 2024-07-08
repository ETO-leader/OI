#include<bits/stdc++.h>
#include<bits/extc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace __gnu_pbds;
using namespace std;
using lint=long long;
template<typename T>
using Tree=tree<T,null_type,less<T>,rb_tree_tag,
    tree_order_statistics_node_update>;
Tree<pair<lint,int>> Tr;
struct edge{lint u,w;};
vector<int> Ans;
const int _inf=1e9+7;
vector<vector<edge>> G;
lint N,T;
void dfs(int u,lint h=0){
    Ans[u]=-Tr.order_of_key({h+T,_inf})+Tr.order_of_key({h,-1});
    Tr.insert({h,u});
    for(auto&i:G[u]) dfs(i.u,h+i.w);
    Ans[u]+=Tr.order_of_key({h+T,_inf})-Tr.order_of_key({h,-1});
}
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    cin>>N>>T;Ans.resize(N+1);G.resize(N+1);
    cir(i,2,N+1){
        lint f,w;cin>>f>>w;
        G[f].push_back({i,w});
    }
    dfs(1);
    cir(i,1,N+1) cout<<Ans[i]<<endl;
    return 0;
}
