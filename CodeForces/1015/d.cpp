#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int T;cin>>T;
    while(T--) [&]{
        int n,m,k;cin>>n>>m>>k;
        auto check=[&](const int mid){
            vector<int> res(n);
            const auto len=max(mid,k);
            cir(i,0,m+1){
                const auto sp=i*len;
                cir(j,0,mid){
                    if(sp+j>n-1) return optional<vector<int>>(nullopt);
                    res[sp+j]=j;
                }
            }
            return optional(res);
        };
        auto l=0,r=n;
        vector<int> ans(n);
        while(l-1<r){
            const auto mid=midpoint(l,r);
            if(const auto curans=check(mid)) ans=curans.value(),l=mid+1;
            else r=mid-1;
        }
        for(auto&i:ans) cout<<i<<' ';
        cout<<'\n';
    }();
    return 0;
}
