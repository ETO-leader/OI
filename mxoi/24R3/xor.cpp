#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
ifstream fcin("xor.in");
ofstream fcout("xor.out");
class fileio{
public:
    ~fileio(){
        fcin.close();fcout.close();
    }
} use_fileio;
using lint=long long;
class dsu{
private:
    vector<int> f,siz,cnt;
public:
    auto findset(int u)->int{
        return f[u]==u?u:f[u]=findset(f[u]);
    }
    auto merge(int u,int v){
        u=findset(u);v=findset(v);++cnt[v];
        if(u==v) return;
        f[u]=v;siz[v]+=siz[u];cnt[v]+=cnt[u];
    }
    auto size(int u){return siz[findset(u)];}
    auto count(int u){return cnt[u];}
    dsu(int _n):f(_n),siz(_n,1),cnt(_n){iota(f.begin(),f.end(),0);}
};
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n;fcin>>n;vector<int> a(n),b(n);
    for(auto&i:a) fcin>>i;
    for(auto&i:b) fcin>>i;
    a.push_back(accumulate(a.begin(),a.end(),0,[](int x,int y){
        return x^y;
    }));
    multiset ax(a.begin(),a.end());
    for(auto&i:b) ax.extract(i);
    b.push_back(*ax.begin());
    map<int,int> id;
    multiset ins(a.begin(),a.end());
    for(auto c=0;auto&i:ins) id[i]=c++;
    dsu ds(n+1);
    cir(i,0,n) if(a[i]!=b[i]) ds.merge(id[a[i]],id[b[i]]);
    auto ans=0,cnt=0;
    cir(i,0,n+1) if(ds.findset(i)==i){
        ans+=ds.count(i);
        cnt+=(ds.size(i)>1);
    }
    fcout<<max(ans+cnt-1,0)<<'\n';
    return 0;
}
