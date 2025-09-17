#pragma GCC optimize("Ofast")
#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int n;cin>>n;
    vector<string> a(n);
    for(auto&x:a) cin>>x;
    vector<uint64_t> hx(n);
    unordered_map<uint64_t,vector<int>> pos;
    unordered_map<uint64_t,int> f;
    auto ans=0;
    auto cnt=-1;
    vector<pair<int,uint64_t>> sufs;
    unordered_set<uint64_t> thash;
    for(auto&x:a){
        ++cnt;
        reverse(x.begin(),x.end());
        auto w=(uint64_t)(0);
        cir(i,0,(int)(x.size())-1) (w*=251)+=x[i];
        pos[w].emplace_back(cnt);
        sufs.emplace_back((int)(x.size())-1,w);
        (w*=251)+=x.back();
        hx[cnt]=w;
        thash.emplace(hx[cnt]);
    }
    sort(sufs.begin(),sufs.end());
    sufs.erase(unique(sufs.begin(),sufs.end()),sufs.end());
    reverse(sufs.begin(),sufs.end());
    for(auto&[l,suf]:sufs){
        const auto uc=(int)(pos[suf].size());
        auto uf=uc;
        vector<int> nf;
        for(auto&x:pos[suf]) if(f.count(hx[x])){
            nf.emplace_back(f[hx[x]]);
            uf=max(uf,f[hx[x]]+uc);
        }
        sort(nf.begin(),nf.end(),greater<>());
        if(nf.size()>1) ans=max(ans,nf[0]+nf[1]+uc+(int)(thash.count(suf)));
        f[suf]=uf;
        ans=max(ans,uf);
    }
    cout<<ans<<'\n';
    return 0;
}