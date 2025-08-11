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
    int n;cin>>n;vector<int> cnt(n);
    int u,v;
    dsu qwq(n);
    while(cin>>u>>v){
        --u;--v;
        if(qwq.findset(u)==qwq.findset(v)) exit((cout<<0<<'\n',0));
        ++cnt[u];++cnt[v];
        qwq.merge(u,v);
    }
    cout<<((count(cnt.begin(),cnt.end(),1)==2&&(count(cnt.begin(),cnt.end(),1)+count(cnt.begin(),cnt.end(),2)==n))||n==1)<<'\n';
    return 0;
}
