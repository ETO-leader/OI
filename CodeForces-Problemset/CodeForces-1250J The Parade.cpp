#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
const lint _inf=1e15+7;
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int T;cin>>T;
    while(T--){
        lint n,k;cin>>n>>k;
        vector<lint> a(n);
        for(auto&i:a) cin>>i;
        lint l=1,r=_inf,ans=0;
        while(r>=l){
            const auto mid=(l+r)/2;
            [&](){
                lint res=0;
                auto ax=a;
                cir(i,0,n-1){
                    res+=ax[i]/mid,ax[i]%=mid;
                    if(ax[i]&&(ax[i]+ax[i+1])>mid-1){
                        ++res;
                        ax[i+1]-=(mid-ax[i]);
                    }
                }
                return res+(ax[n-1]/mid)>k-1;
            }()?((l=mid+1),(ans=mid)):(r=mid-1);
        }
        cout<<ans*k<<'\n';
    }
    return 0;
}
