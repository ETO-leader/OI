#include<bits/stdc++.h>
#define cir(i,a,b) for(auto i=a;i<b;++i)
using namespace std;
using lint=long long;
class dsu{
private:
    vector<int> a;
public:
    auto findset(int u)->int{
        return a[u]==u?u:a[u]=findset(a[u]);
    }
    auto merge(int u,int v){
        a[findset(u)]=findset(v);
    }
    dsu(int _n):a(_n){ranges::iota(a,0);}
};
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int T;cin>>T;
    while(T--) []{
        int n;cin>>n;vector<lint> a(n);
        for(auto&i:a) cin>>i;
        const auto ws=set(a.begin(),a.end());
        a=vector(ws.begin(),ws.end());
        n=(int)(ws.size());
        const auto mx=a[n-1];
        vector<lint> nxtu(mx+2,-1);
        for(auto&x:a) nxtu[x]=x;
        for(auto i=mx;~i;--i) if(nxtu[i]==-1) nxtu[i]=nxtu[i+1]; 
        vector<tuple<int,int,int>> es;
        for(auto&w:a){
            const auto nxt=nxtu[w+1];
            if(nxt>-1) es.emplace_back(nxt%w,w,nxt);
            for(auto x=w*2;x<mx+1;x+=w){
                const auto nxt=nxtu[x];
                if(nxt>-1) es.emplace_back(nxt%w,w,nxt);
            }
        }
        dsu d(mx+1);
        auto ans=0ll;
        ranges::sort(es);
        for(auto&[w,u,v]:es) if(d.findset(u)!=d.findset(v)){
            ans+=w;d.merge(u,v);
        }
        println("{}",ans);
    }();
    return 0;
}
