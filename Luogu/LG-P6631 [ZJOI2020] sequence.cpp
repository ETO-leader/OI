#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int T;cin>>T;
    while(T--) []{
        int n;cin>>n;vector<lint> a(n);
        for(auto&i:a) cin>>i;
        a.emplace_back(0);
        auto norm=0ll,skip=0ll,skipd=0ll,ans=0ll;
        cir(i,1,n+1){
            auto w=0;
            if(a[i]<norm+skip){
                auto k=norm+skip-a[i];
                if(skip<k) norm-=k-skip,k=skip;
                if(norm<k) skip-=k-norm,k=norm;
                norm-=k;
                skip-=k;
                a[i]-=k;
                w+=k;
            }
            a[i]-=norm+skip;
            const auto c=min(a[i-1],a[i]);
            ans+=c;a[i-1]-=c;a[i]-=c;
            norm+=c;
            ans+=a[i-1];
            skipd+=a[i-1];
            a[i]+=w;ans-=w;
            swap(skip,skipd);
        }
        cout<<ans<<'\n';
    }();
    return 0;
}
