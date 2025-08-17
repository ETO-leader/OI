#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int n;cin>>n;
    set<char> apr;
    vector<string> a(n);
    for(auto&i:a){
        cin>>i;
        for(auto&x:i) apr.emplace(x);
    }
    string sq;cin>>sq;
    for(auto&x:sq) apr.emplace(x);
    vector<vector<int>> vx(26);
    vector<int> inc(26);
    cir(i,1,n) cir(j,0,(int)(min(a[i-1].size(),a[i].size()))){
        if(a[i-1][j]!=a[i][j]){
            vx[a[i-1][j]-'a'].emplace_back(a[i][j]-'a'),++inc[a[i][j]-'a'];
            break;
        }
    }
    vector<int> mxd(26);
    queue<int> q;
    cir(i,0,26) if(!inc[i]) q.emplace(i);
    while(!q.empty()){
        const auto u=q.front();q.pop();
        for(auto&i:vx[u]) if(!(--inc[i])){
            mxd[i]=mxd[u]+1;
            q.emplace(i);
        }
    }
    if(*max_element(mxd.begin(),mxd.end())!=(int)(apr.size())-1){
        cout<<0<<'\n';
    }else{
        for(auto&i:sq) cout<<(char)(mxd[i-'a']+'a');
        cout<<'\n';
    }
    return 0;
}
