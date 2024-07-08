#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n;lint d;cin>>n>>d;d*=d;
    auto ans=0;
    cir(i,0,n){
        lint x,y;cin>>x>>y;
        ans+=((x*x+y*y)<d+1);
    }
    cout<<ans<<'\n';
    return 0;
}
