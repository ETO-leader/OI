#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
using VL=vector<lint>;
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n,m,k;cin>>n>>m>>k;
    vector<VL> mp(n,VL(m));
    vector<vector<VL>> D(n,vector<VL>(m,VL(4)));
    cir(i,0,k){
        int x,y,v;cin>>x>>y>>v;--x,--y;
        mp[x][y]=v;
    }
    cir(i,1,4) D[0][0][i]=mp[0][0];
    cir(i,0,n) cir(j,0,m) cir(w,0,4){
        auto&d=D[i][j][w];
        lint cx=(mp[i][j]&&w?w-1:w),ad=(w?mp[i][j]:0LL);
        if(i) cir(p,0,4) d=max(d,D[i-1][j][p]+ad);
        if(j) d=max({d,D[i][j-1][w],D[i][j-1][cx]+ad});
    }
    cout<<*max_element(D[n-1][m-1].begin(),
        D[n-1][m-1].end())<<'\n';
    return 0;
}
