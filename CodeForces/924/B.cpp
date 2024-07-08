#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int T;cin>>T;
    while(T--){
        int n;cin>>n;vector<int> a(n);
        for(auto&i:a) cin>>i;
        sort(a.begin(),a.end());
        a.erase(unique(a.begin(),a.end()),a.end());
        int l=0,r=-1,ans=0;
        const auto ln=n;n=a.size();
        cir(i,0,n){
            while(r+1<n&&a[r+1]-a[l]<ln) ++r;
            ans=max(ans,r-l+1);++l;
        }
        cout<<ans<<'\n';
    }
    return 0;
}
