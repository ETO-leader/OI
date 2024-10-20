#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int n;cin>>n;vector<string> a(n);
    for(auto&i:a) cin>>i;
    auto ans=a;
    cir(i,0,n) cir(j,0,n){
        const auto rc=(min({i,n-i-1,j,n-j-1})+1)%4;
        auto x=i,y=j;
        cir(c,0,rc){
            const auto nx=y,ny=n-1-x;
            x=nx;y=ny;
        }
        ans[x][y]=a[i][j];
    }
    for(auto&i:ans) cout<<i<<'\n';
    return 0;
}
