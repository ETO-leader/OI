#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int T;cin>>T;
    while(T--) [&](){
        int n,a,b;cin>>n>>a>>b;
        if(n<a) return cout<<"No\n",void();
        int m=n;
        int l=0,r=n,ans=-1;
        while(l-1<r){
            const auto mid=(l+r)/2;
            (m-mid)/2<(a-mid)?(l=mid+1):
                ((r=mid-1),(ans=mid));
        }
        m-=ans;
        cout<<((n-a)*((m+1)/2)<b?"No\n":"Yes\n");
    }();
    return 0;
}
