#include<bits/stdc++.h>
#define cir(i,a,b) for(auto i=a;i<b;++i)
using namespace std;
using lint=long long;
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int n,m;lint k;cin>>n>>m>>k;
    map<pair<int,int>,int> mcnt;
    cir(i,0,m){
        int x,y;cin>>x>>y;
        const auto g=__gcd(x,y);
        ++mcnt[{x/g,y/g}];
    }
    vector<int> phi(n+1,1),isp(n+1,true);
    cir(i,2,n+1) if(isp[i]){
        phi[i]=i-1;
        for(auto j=i*2,c=2;j<n+1;j+=i,++c){
            isp[j]=false;
            phi[j]*=(i-1);
            auto w=c;
            while(!(w%i)) w/=i,phi[j]*=i;
        }
    }
    vector<lint> cnt(n);
    cnt[n-1]=3;
    cir(i,2,n+1) cnt[(n-1)/i]+=phi[i]*2;
    for(auto&[x,y]:mcnt){
        const auto c=(n-1)/max(x.first,x.second);
        --cnt[c];
        ++cnt[c-y];
    }
    auto ans=0ll;
    for(auto i=n-1;~i;--i){
        if(cnt[i]<k){
            ans+=cnt[i]*i;
            k-=cnt[i];
        }else{
            ans+=k*i;
            break;
        }
    }
    cout<<ans<<'\n';
    return 0;
}
