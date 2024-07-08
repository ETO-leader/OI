#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
using VI=vector<lint>;
auto initp2(int n,const int p){
    VI res(1,1);
    cir(i,0,n) res.push_back(res.back()*2%p);
    return res;
}
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n,p;cin>>n>>p;
    static const auto p2=initp2(n,p);
    VI D(n+1),pre(n+1);
    vector<VI> g(n+1,VI(n+1)),f(n+1,VI(n+1));
    D[1]=1;pre[1]=1;g[1][1]=1;
    cir(i,2,n+1){
        cir(j,1,i+1) if(j*2+2<i)
            g[i][j]=D[j]*pre[i-j*2-2]%p;
        D[i]=p2[i-2];
        cir(j,1,i+1) (D[i]+=(p-g[i][j]))%=p;
        (g[i][i]+=D[i])%=p;
        cir(j,1,i+1) if(j<n){
            f[i][j]=(f[i-1][j+1]+g[i][j])%p;
        }
        pre[i]=(pre[i-1]+f[i][1])%p;
    }
    cout<<D[n]<<'\n';
    return 0;
}
