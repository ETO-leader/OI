#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int n;cin>>n;
    vector<int> a(n);
    for(auto&i:a) cin>>i;
    auto check=[](vector<int> a){
        multiset<int> cur;
        auto l=0,ans=0;
        const auto x=(int)(a.size());
        cir(r,0,x){
            if(a[r]==114514191){
                l=r+1,cur.clear();
                continue;
            }
            while(cur.count(a[r])) cur.extract(a[l]),++l;
            cur.insert(a[r]);
            ans=max(ans,(r-l+1)*2);
        }
        return ans;
    };
    vector<int> lx,rx;
    for(auto i=0;i+1<n;i+=2){
        lx.push_back(a[i]==a[i+1]?a[i]:114514191);
    }
    for(auto i=1;i+1<n;i+=2){
        rx.push_back(a[i]==a[i+1]?a[i]:114514191);
    }
    cout<<max(check(lx),check(rx))<<'\n';
    return 0;
}
