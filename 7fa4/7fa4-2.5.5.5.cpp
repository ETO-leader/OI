#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    lint n,k,m;cin>>n>>k>>m;
    const int U=log2(m)+1;
    vector<lint> v(n);vector<int> F(n);
    for(auto&i:v) cin>>i;
    int l=0,r=k;
    cir(i,0,n){
        while(r<n-1&&l<=i&&abs(v[r+1]-v[i])<abs(v[i]-v[l])) ++l,++r;
        while(r<i) ++r,++l;
        F[i]=abs(v[i]-v[l])<abs(v[r]-v[i])?r:l;
    }
    vector<vector<int>> UP(U+1,vector<int>(n));
    cir(i,0,n) UP[0][i]=F[i];
    cir(step,1,U+1) cir(i,0,n)
        UP[step][i]=UP[step-1][UP[step-1][i]];
    cir(i,0,n){
        lint u=i;
        for(int j=U;j+1;--j) if(m&(1LL<<j)) u=UP[j][u];
        cout<<u+1<<' ';
    }
    cout<<'\n';
    return 0;
}