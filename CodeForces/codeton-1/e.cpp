#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int T;cin>>T;
    while(T--) [&]{
        int n;cin>>n;
        vector<vector<int>> vx(n);
        cir(i,0,n-1){
            int u,v;cin>>u>>v;--u;--v;
            vx[u].emplace_back(v);
            vx[v].emplace_back(u);
        }
        vector<int> col(n);
        [&](this auto&&__self,int u,int f,int c)->void {
            col[u]=c;
            for(auto&i:vx[u]) if(i!=f) __self(i,u,-c);
        }(0,-1,1);
        cir(i,0,n) cout<<col[i]*(int)(vx[i].size())<<' ';
        cout<<'\n';
    }();
    return 0;
}
