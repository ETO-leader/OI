#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    lint a,b,c,d,e;cin>>a>>b>>c>>d>>e;
    unordered_map<lint,lint> cnt;
    cir(x0,-50,51) cir(x1,-50,51) cir(x2,-50,51) if(x0&&x1&&x2){
        ++cnt[a*x0*x0*x0+b*x1*x1*x1+c*x2*x2*x2];
    }
    auto ans=0ll;
    cir(x3,-50,51) cir(x4,-50,51) if(x3&&x4){
        ans+=cnt[-(d*x3*x3*x3+e*x4*x4*x4)];
    }
    cout<<ans<<'\n';
    return 0;
}
