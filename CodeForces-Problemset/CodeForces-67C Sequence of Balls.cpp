#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
static constexpr auto alpha=26;
static constexpr auto _inf=(int)(1e9+7);
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int ti,td,tr,te;cin>>ti>>td>>tr>>te;
    string a,b;cin>>a>>b;
    const auto n=(int)(a.size()),m=(int)(b.size());
    vector f(n+1,vector(m+1,_inf)),
        lasa(n,vector(alpha,-1)),
        lasb(m,vector(alpha,-1));
    cir(i,0,n){
        if(i) lasa[i]=lasa[i-1];
        lasa[i][a[i]-'a']=i;
    }
    cir(i,0,m){
        if(i) lasb[i]=lasb[i-1];
        lasb[i][b[i]-'a']=i;
    }
    f[0][0]=0;
    cir(i,0,n+1) cir(j,0,m+1){
        if(i&&j) f[i][j]=min(f[i][j],f[i-1][j-1]+tr*(a[i-1]!=b[j-1]));
        if(i) f[i][j]=min(f[i][j],f[i-1][j]+td);
        if(j) f[i][j]=min(f[i][j],f[i][j-1]+ti);
        if(i-2>-1&&j-2>-1){
            const auto pa=lasa[i-2][b[j-1]-'a'],pb=lasb[j-2][a[i-1]-'a'];
            if(pa>-1&&pb>-1) f[i][j]=min(f[i][j],f[pa][pb]+(i-pa-2)*td+(j-pb-2)*ti+te);
        }
    }
    cout<<f[n][m]<<'\n';
    return 0;
}
