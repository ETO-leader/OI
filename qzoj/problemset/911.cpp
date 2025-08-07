#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
class dsu{
private:
    vector<int> f;
public:
    auto findset(int u)->int{
        return f[u]==u?u:(f[u]=findset(f[u]));
    }
    auto merge(int u,int v){
        f[findset(u)]=findset(v);
    }
    dsu(int n):f(n){iota(f.begin(),f.end(),0);}
};
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int n,m;cin>>n>>m;dsu qwq(n);
    cir(i,0,m){
        int u,v;cin>>u>>v;--u;--v;
        qwq.merge(u,v);
    }
    set<int> x;
    cir(i,0,n) x.emplace(qwq.findset(i));
    cout<<(x.size()==1?"YES":"NO")<<'\n';
    return 0;
}
