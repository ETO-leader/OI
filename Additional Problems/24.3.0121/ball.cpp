#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
ifstream fcin("ball.in");
ofstream fcout("ball.out");
class fileio{
public:
    ~fileio(){
        fcin.close();fcout.close();
    }
} use_fileio;
using db=long double;
static constexpr auto eps=1e-20L;
auto gauss(vector<vector<db>> a){
    const int n=a.size();
    cir(i,0,n){
        cir(j,i+1,n) if(abs(a[j][i])>abs(a[i][i]))
            swap(a[i],a[j]);
        if(abs(a[i][i])>eps) cir(j,i+1,n){
            const auto x=a[j][i]/a[i][i];
            cir(k,i,n+1) a[j][k]-=x*a[i][k];
        }
    }
    for(int i=n-1;~i;--i){
        cir(j,i+1,n) a[i][n]-=a[j][n]*a[i][j];
        a[i][n]/=a[i][i];
    }
    vector<db> res;res.reserve(n);
    cir(i,0,n) res.push_back(a[i][n]);
    return res;
}
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n;fcin>>n;
    vector<vector<db>> a(n+1,vector<db>(n)),
        f(n,vector<db>(n+1));
    for(auto&i:a) for(auto&j:i) fcin>>j;
    cir(i,0,n) cir(j,0,n){
        const auto ax=a[i][j],bx=a[i+1][j];
        f[i][j]=(bx-ax)*2;
        f[i][n]+=bx*bx-ax*ax;
    }
    auto ans=gauss(f);
    for(auto&i:ans){
        fcout<<fixed<<setprecision(15)<<i<<' ';
    }
    fcout<<'\n';
    return 0;
}
