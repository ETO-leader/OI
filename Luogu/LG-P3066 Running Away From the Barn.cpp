#include<bits/stdc++.h>
#include<bits/extc++.h>
using namespace __gnu_pbds;
using namespace std;
typedef long long lint;
const lint _inf=1e18+7;
vector<vector<pair<lint,lint>>> G;
template<typename T>
using Tree=tree<T,null_type,less<T>,rb_tree_tag,
    tree_order_statistics_node_update>;
Tree<pair<lint,lint>> Tr;
vector<lint> ans;
void dfs(lint u,lint&cnt,lint t,lint h=0){
    Tr.insert({h,++cnt});
    ans[u]=-Tr.order_of_key({h+t,_inf})+Tr.order_of_key({h,cnt+1});
    for(auto&i:G[u]) dfs(i.first,cnt,t,h+i.second);
    ans[u]+=Tr.order_of_key({h+t,_inf})-Tr.order_of_key({h,cnt+1});
}
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    lint n,ccnt=0,t;cin>>n>>t;
    G.resize(n+1);ans.resize(n+1);
    for(int i=2;i<=n;++i){
        lint a,b;cin>>a>>b;
        G[a].push_back({i,b});
    }
    dfs(1,ccnt,t);
    for(int i=1;i<=n;++i) cout<<ans[i]+1<<endl;
    return 0;
}