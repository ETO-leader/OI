#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int n,p;cin>>n>>p;
    vector f(n*3+1,vector<lint>(n+1));
    f[0][0]=1;
    cir(i,0,n*3) cir(x,0,n+1){
        (f[i+1][x]+=f[i][x])%=p;
        if(x<n&&i+2<n*3+1){
            (f[i+2][x+1]+=f[i][x]*(i+1))%=p;
        }
        if(x<n&&i+3<n*3+1){
            (f[i+3][x+1]+=f[i][x]*(i+1)%p*(i+2))%=p;
        }
    }
    cout<<accumulate(f[n*3].begin(),f[n*3].end(),0ll)%p<<'\n';
    return 0;
}
