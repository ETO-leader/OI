#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int T;cin>>T;
    while(T--){
        int n;cin>>n;
        if(n==2){
            int64_t a,b,x,y;cin>>a>>b>>x>>y;
            const auto d=b-a;
            const auto s=x+y;
            cout<<(d-1)/s*2+1<<' '<<(d-1)/s*2+1<<'\n';
        }
    }
    return 0;
}
