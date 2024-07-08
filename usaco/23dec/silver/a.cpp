#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n,m,k;cin>>n>>m>>k;
    map<lint,lint,greater<lint>> cntx;
    cir(i,0,n){
        lint a,b;cin>>a>>b;
        cntx[a]+=b;
    }
    map<lint,lint> f;lint ans=0,cnt=0;
    for(auto&[w,a]:cntx){
        if(cnt<m){
            const auto ad=min(a,m-cnt);
            a-=ad;ans+=ad;cnt+=ad;f[w]+=ad;
        }
        if(!a) continue;
        while(a&&f.lower_bound(w+k)!=f.end()){
            auto lb=f.lower_bound(w+k);
            if(a>lb->second){
                ans+=lb->second;a-=lb->second;
                f[w]+=lb->second;f.erase(lb);
            }else{
                f[w]+=a;lb->second-=a;
                ans+=a;a=0;
            }
        }
    }
    cout<<ans<<'\n';
    return 0;
}
