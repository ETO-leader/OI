#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
static constexpr auto maxsc=650;
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int n;cin>>n;
    vector<pair<int,int>> a(n);
    for(auto&x:a) cin>>x.first>>x.second;
    vector<vector<int>> ord(maxsc+7,vector<int>(maxsc+7));
    for(auto&x:a) ++ord[x.first][x.second];
    vector<int> mnr(n),mxr(n);
    // get min-possible rank
    [&]{
        auto suf=ord;
        for(auto x=maxsc;~x;--x) for(auto y=maxsc;~y;--y){
            suf[x][y]+=suf[x+1][y]+suf[x][y+1]-suf[x+1][y+1];
        }
        cir(i,0,n) mnr[i]=suf[a[i].first+1][a[i].second+1]+1;
    }();
    // get max-possible rank
    [&]{
        auto pre=ord;
        vector<int> xm(maxsc+1),ym(maxsc+1);
        cir(x,0,maxsc+1) cir(y,0,maxsc+1){
            if(x) pre[x][y]+=pre[x-1][y];
            if(y) pre[x][y]+=pre[x][y-1];
            if(x&&y) pre[x][y]-=pre[x-1][y-1];
        }
        cir(i,0,n) if(!a[i].first) ++xm[a[i].second];
        cir(i,0,n) if(!a[i].second) ++ym[a[i].first];
        cir(i,0,n) mxr[i]=n-(a[i].first&&a[i].second?pre[a[i].first-1][a[i].second-1]:0);
        cir(i,0,n) if(a[i].first==650) mxr[i]-=xm[a[i].second];
        cir(i,0,n) if(a[i].second==650) mxr[i]-=ym[a[i].first];
    }();
    cir(i,0,n) cout<<mnr[i]<<' '<<mxr[i]<<'\n';
    return 0;
}
