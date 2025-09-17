#pragma GCC optimize("Ofast","unroll-loops")
#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
class dsu{
private:
    vector<int> f;
public:
    auto findset(auto u)->int{
        return f[u]==u?u:f[u]=findset(f[u]);
    }
    auto merge(auto u,auto v){
        f[findset(u)]=findset(v);
    }
    dsu(auto _n):f(_n){iota(f.begin(),f.end(),0);}
};
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int n;cin>>n;
    vector<int> a(n);
    for(auto&x:a) cin>>x;
    sort(a.begin(),a.end());
    a.erase(unique(a.begin(),a.end()),a.end());
    const auto mxa=*max_element(a.begin(),a.end());
    vector<int> id(mxa+2,-1);
    vector<bool> vis(mxa+2);
    const auto k=(int)(a.size());
    auto las=-1;
    cir(i,0,k) fill(id.begin()+(las+1),id.begin()+a[i]+1,i),las=a[i];
    vector<vector<pair<int,int>>> mxw(mxa+1);
    for(auto&x:a){
        const auto upb=id[x+1];
        if(upb>-1&&a[upb]-x<x) mxw[a[upb]-x].emplace_back(id[x],upb);
        if(!vis[x]) for(auto w=x*2;w<mxa+1;w+=x){
            vis[w]=true;
            const auto upb=id[w];
            if(upb>-1&&a[upb]-w<x) mxw[a[upb]-w].emplace_back(id[x],upb);
        }
    }
    dsu qwq(k);
    auto ans=0ll;
    cir(i,0,mxa+1) for(auto&[a,b]:mxw[i]) if(qwq.findset(a)!=qwq.findset(b)){
        qwq.merge(a,b);
        ans+=i;
    }
    cout<<ans<<'\n';
    return 0;
}
