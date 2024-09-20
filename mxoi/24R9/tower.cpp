#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
ifstream fcin("tower.in");
ofstream fcout("tower.out");
class fileio{
public:
    ~fileio(){
        fcin.close();fcout.close();
    }
} use_fileio;
static constexpr auto _inf=(int)(1e9+7);
constexpr auto extinfoln(auto info){
    exit((fcout<<info<<'\n',0));
}
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int n,q;fcin>>n>>q;
    vector<int> u(n),v(n);
    for(auto&i:u) fcin>>i;
    for(auto&i:v) fcin>>i;
    vector w(n,vector<int>(n));
    for(auto&x:w) for(auto&i:x) fcin>>i;
    if(n>100){
        vector f(n,vector<int>(n,-_inf));
        cir(i,0,n) cir(j,0,n) f[i][j]=w[i][j]-u[i]-v[j];
        cir(i,0,n) cir(j,0,n){
            cir(las,0,i) f[i][j]=max({f[i][j],f[las][j]-u[i]+w[i][j]});
            cir(las,0,j) f[i][j]=max({f[i][j],f[i][las]-v[j]+w[i][j]});
        }
        auto ans=f;
        cir(i,1,n) cir(j,0,n) ans[i][j]=max(ans[i][j],ans[i-1][j]);
        cir(i,0,n) cir(j,1,n) ans[i][j]=max(ans[i][j],ans[i][j-1]);
        cir(i,0,q){
            int a,b,c,d;fcin>>a>>b>>c>>d;
            for(auto x:{&a,&b,&c,&d}) --(*x);
            fcout<<max(ans[b][d],0)<<'\n';
        }
    }else{
        cir(i,0,q){
            int a,b,c,d;fcin>>a>>b>>c>>d;
            for(auto x:{&a,&b,&c,&d}) --(*x);
            vector f(n,vector<int>(n,-_inf));
            cir(i,a,b+1) cir(j,c,d+1) f[i][j]=w[i][j]-u[i]-v[j];
            cir(i,a,b+1) cir(j,c,d+1){
                cir(las,a,i) f[i][j]=max({f[i][j],f[las][j]-u[i]+w[i][j]});
                cir(las,c,j) f[i][j]=max({f[i][j],f[i][las]-v[j]+w[i][j]});
            }
            auto ans=f;
            cir(i,max(a,1),b+1) cir(j,c,d+1) ans[i][j]=max(ans[i][j],ans[i-1][j]);
            cir(i,a,b+1) cir(j,max(c,1),d+1) ans[i][j]=max(ans[i][j],ans[i][j-1]);
            fcout<<max(ans[b][d],0)<<'\n';
        }
    }
    return 0;
}
