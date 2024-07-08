#include<bits/stdc++.h>
using namespace std;
using lint=long long;
unordered_map<lint,lint> D;
lint dfs(lint x){
    if(!x) return 1;
    if(D.count(x)) return D[x];
    return D[x]=dfs(x/2)+dfs(x/3);
}
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    lint x;cin>>x;
    cout<<dfs(x)<<'\n';
    return 0;
}
