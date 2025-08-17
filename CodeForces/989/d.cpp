#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int T;cin>>T;
    while(T--) [&]{
        int n;cin>>n;
        vector<int> a(n);
        for(auto&i:a) cin>>i;
        const auto c0=ranges::count(a,0);
        const auto c2=ranges::count(a,2);
        auto p=0;
        vector<pair<int,int>> c;
        set<int> p1;
        cir(i,0,n) if(a[i]==1) p1.emplace(i);
        for(auto i=n-1;i>n-c2-1;--i){
            if(!a[i]){
                const auto px=*p1.begin();
                swap(a[px],a[i]);
                c.emplace_back(px,i);
                p1.extract(px);
                p1.emplace(i);
            }
            if(a[i]==1){
                while(a[p]!=2) ++p;
                swap(a[p],a[i]);
                c.emplace_back(p,i);
                p1.extract(i);
                p1.emplace(p);
                ++p;
            }
        }
        p=c0;
        cir(i,0,c0){
            if(a[i]==1){
                while(a[p]) ++p;
                swap(a[p],a[i]);
                c.emplace_back(p,i);
                ++p;
            }
        }
        assert(ranges::is_sorted(a));
        cout<<c.size()<<'\n';
        for(auto&[a,b]:c) cout<<a+1<<' '<<b+1<<'\n';
    }();
    return 0;
}
