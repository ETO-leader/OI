#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int T;cin>>T;
    while(T--) []{
        int n;cin>>n;vector<int> a(n);
        unordered_map<int,int> cnt;
        for(auto&i:a) cin>>i,cnt[i]=false;
        cir(l,0,n){
            auto cur=a[l];
            cir(r,l+1,n){
                cur+=a[r];
                if(cnt.contains(cur)) cnt[cur]=true;
            }
        }
        auto ans=0;
        for(auto&i:a) ans+=cnt[i];
        println("{}",ans);
    }();
    return 0;
}
