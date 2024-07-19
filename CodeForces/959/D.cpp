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
    ios::sync_with_stdio(false),cin.tie(0);
    int T;cin>>T;
    while(T--) [&](){
        int n;cin>>n;vector<int> a(n);
        for(auto&i:a) cin>>i;
        dsu ds(n);
        vector<pair<int,int>> ans;
        for(auto x=n-1;x;--x){
            vector<map<int,vector<int>>> ax(x);
            cir(i,0,n) ax[a[i]%x][ds.findset(i)].push_back(i);
            auto ok=false;
            for(auto&i:ax) if(i.size()>1){
                ok=true;
                ans.push_back({(i.begin()->second)[0]+1,(next(i.begin())->second)[0]+1});
                ds.merge(i.begin()->first,next(i.begin())->first);
                break;
            }
            if(!ok) return cout<<"NO\n",void();
        }
        cout<<"YES\n";
        ranges::reverse(ans);
        for(auto&[a,b]:ans) cout<<a<<' '<<b<<'\n';
    }();
    return 0;
}
