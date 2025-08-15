#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int T;cin>>T;
    while(T--) [&]{
        int n,m;cin>>n>>m;
        vector a(n,vector<int>(m));
        for(auto&x:a) for(auto&i:x) cin>>i;
        vector<int> c(n);
        cir(i,0,n) c[i]=accumulate(a[i].begin(),a[i].end(),0);
        const auto cnt=accumulate(c.begin(),c.end(),0);
        if(cnt%n) return cout<<"-1"<<'\n',void();
        auto ans=0;
        stringstream ouf;
        cir(j,0,m){
            vector<int> pg,pr;
            cir(i,0,n) if(c[i]>cnt/n&&a[i][j]) pg.emplace_back(i);
            cir(i,0,n) if(c[i]<cnt/n&&(!a[i][j])) pr.emplace_back(i);
            cir(i,0,(int)(min(pg.size(),pr.size()))){
                --c[pg[i]];
                ++c[pr[i]];
                ++ans;
                ouf<<pg[i]+1<<' '<<pr[i]+1<<' '<<j+1<<'\n';
            }
        }
        cout<<ans<<'\n';
        cout<<ouf.str();
    }();
    return 0;
}
