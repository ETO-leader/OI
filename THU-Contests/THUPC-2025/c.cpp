#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int T;cin>>T;
    while(T--) []{
        int n,p;cin>>n>>p;--p;vector<int> a(n);
        for(auto&i:a) cin>>i;
        multiset<int> nums(a.begin(),a.end());
        auto ans=(nums.size()<3?(*nums.rbegin()):*next(next(nums.begin())));
        multiset<int,greater<int>> sp;
        cir(i,-1,2) if(p+i>-1&&p+i<n) sp.insert(a[p+i]);
        sp.erase(sp.begin());
        if(sp.size()) ans=max(ans,*sp.begin());
        cout<<ans<<'\n';
    }();
    return 0;
}
