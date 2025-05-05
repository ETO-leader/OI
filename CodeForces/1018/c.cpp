#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
static constexpr auto _infl=(lint)(1e18l);
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int T;cin>>T;
    while(T--) [&]{
        int n;cin>>n;vector a(n,vector<lint>(n));
        for(auto&i:a) for(auto&x:i) cin>>x;
        vector<lint> wx(n),wy(n);
        for(auto&i:wx) cin>>i;
        for(auto&i:wy) cin>>i;
        vector fx(n,vector<lint>(2,_infl));
        fx[0][0]=0;fx[0][1]=wx[0];
        cir(i,0,n-1) cir(c,0,2) cir(x,0,2) [&]{
            cir(j,0,n) if(a[i][j]+c==a[i+1][j]+x) return;
            fx[i+1][x]=min(fx[i+1][x],fx[i][c]+wx[i+1]*x); 
        }();
        vector fy(n,vector<lint>(2,_infl));
        fy[0][0]=0;fy[0][1]=wy[0];
        cir(i,0,n-1) cir(c,0,2) cir(x,0,2) [&]{
            cir(j,0,n) if(a[j][i]+c==a[j][i+1]+x) return;
            fy[i+1][x]=min(fy[i+1][x],fy[i][c]+wy[i+1]*x); 
        }();
        const auto ux=min(fx[n-1][0],fx[n-1][1]);
        const auto uy=min(fy[n-1][0],fy[n-1][1]);
        if(ux>_infl-1||uy>_infl-1){
            cout<<-1<<'\n';
        }else{
            cout<<ux+uy<<'\n';
        }
    }();
    return 0;
}
