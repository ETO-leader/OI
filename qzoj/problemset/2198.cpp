#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
class dsu{
private:
    vector<int> f;
public:
    auto findset(int u)->int{
        return f[u]==u?u:f[u]=findset(f[u]);
    }
    auto merge(int u,int v){
        f[findset(u)]=findset(v);
    }
    dsu(int _n):f(_n){iota(f.begin(),f.end(),0);}
};
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int T;cin>>T;
    while(T--) []{
        int n,m;cin>>n>>m;dsu qwq(n);
        auto ans=false;
        cir(i,0,m){
            int u,v;cin>>u>>v;--u;--v;
            ans|=(qwq.findset(u)==qwq.findset(v));
            qwq.merge(u,v);
        }
        cout<<(ans?"YES":"NO")<<'\n';
    }();
    return 0;
}
