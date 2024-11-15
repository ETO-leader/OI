#pragma GCC optimize("Ofast")
#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
static constexpr auto maxa=(int)(4e5+7);
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int T;cin>>T;
    vector<vector<int>> fctors(maxa),to(maxa);
    bitset<maxa> vis;
    cir(i,2,maxa){
        for(auto x=i;x<maxa;x+=i) fctors[x].push_back(i);
    }
    cir(i,2,maxa){
        for(auto&w:fctors[i]){
            if(i+w>maxa-1) break;
            to[i].push_back(i+w);
        }
    }
    vector<pair<int,bitset<maxa>>> ax;
    auto bfs=[&](int u){
        vector<int> q(maxa);
        auto head=0,tail=0;
        q[tail]=u;vis[u]=true;
        while(head<tail+1){
            const auto ux=q[head];++head;
            for(auto&i:to[ux]) if(!vis[i]){
                vis[i]=true;q[++tail]=i;
            }
        }
    };
    bfs(2);
    while(T--) [&](){
        int n;cin>>n;vector<int> a(n);
        for(auto&i:a) cin>>i;
        auto ok2=true;
        for(auto&i:a) ok2&=vis[i];
        if(ok2) return println("2");
        auto p=-1;
        for(auto&i:a) if(fctors[i].size()==1){
            p=i;break;
        }
        cir(i,0,n) if(a[i]!=p&&a[i]!=p*2&&a[i]-fctors[a[i]].front()<p*2) return println("-1");
        println("{}",p);
    }();
    return 0;
}
