#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int n;cin>>n;vector<int> a(n);
    for(auto&i:a) cin>>i;
    map<int,int> id;
    for(auto&i:a) id.emplace(i,0);
    for(auto c=-1;auto&[a,b]:id) b=++c;
    const auto m=(int)(id.size());
    for(auto&i:a) i=id[i];
    vector<vector<int>> pos(m);
    cir(i,0,n) pos[a[i]].push_back(i);
    vector f(1<<m,n+7);
    f[0]=-1;
    cir(s,0,(1<<m)) if(f[s]<n+7){
        cir(w,0,m) if(!(s&(1<<w))){
            auto px=ranges::upper_bound(pos[w],f[s]);
            if(px==pos[w].end()) continue;
            px=next(px);
            if(px==pos[w].end()) continue;
            f[s|(1<<w)]=min(f[s|(1<<w)],*px);
        }
    }
    auto ans=0;
    cir(s,0,(1<<m)) if(f[s]<n+7) ans=max<int>(ans,popcount((uint)(s))*2);
    cout<<ans<<'\n';
    return 0;
}
