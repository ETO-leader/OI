#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int T;cin>>T;
    while(T--) []{
        int n;cin>>n;
        vector<int> p(n);
        cir(i,1,n) cin>>p[i],--p[i];
        vector<vector<int>> gr(n);
        cir(i,1,n) gr[p[i]].emplace_back(i);
        vector<pair<int,int>> es;
        vector<int> udep(n);
        vector<int> chk;
        [&](this auto __self,int u,int dep)->void {
            ++dep;
            udep[u]=dep;
            if(dep>3) chk.emplace_back(u);
            for(auto&i:gr[u]) __self(i,dep);
        }(0,-1);
        vector col(n,-1);
        vector<int> ord(n);
        ranges::iota(ord,0);
        ranges::sort(ord,[&](auto u,auto v){return udep[u]>udep[v];});
        for(auto&x:ord){
            auto ok=false;
            for(auto&i:gr[x]) ok|=col[i];
            col[x]=!ok;
        }
        cir(i,0,n){
            if(col[i]) es.emplace_back(i+1,1);
            else es.emplace_back(1,i+1);
        }
        cout<<"Yes"<<'\n';
        cout<<es.size()<<'\n';
        for(auto&[u,v]:es) cout<<u<<' '<<v<<'\n';
    }();
    return 0;
}
