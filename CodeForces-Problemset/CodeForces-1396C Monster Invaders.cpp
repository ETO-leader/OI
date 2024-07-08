#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
using VI=vector<lint>;
const lint _inf=1e18+7;
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n;lint r1,r2,r3,d;
    cin>>n>>r1>>r2>>r3>>d;
    VI a(n),D(n+1);
    for(auto&i:a) cin>>i;
    D[0]=-d;D[1]=min(a[0]*r1+r3,r2+d*2+r1);
    cir(i,2,n+1){
        D[i]=min({
        //use AWP
            D[i-1]+d+a[i-1]*r1+r3,
        //use USP,once
            D[i-1]+d*3+(a[i-1]+2)*r1,
        //use XM1017
            D[i-1]+d*3+r1+r2,
        //use USP or XM1017, kill the recent boss together
            D[i-2]+d*4+min((a[i-2]+1)*r1,r2)+
                min((a[i-1]+1)*r1,r2)+r1*2
        });
    }
    cout<<min(D[n],D[n-2]+d+r2+r1+
        d*2+a[n-1]*r1+r3)<<'\n';
    return 0;
}
/*
                     _
              |||||>=o=<|||||||
||zzzzzzzzzzz ;====/==/=============================||==
||||||||    //\_||||||||||||||||||||
|||||||||==//   =====

*/