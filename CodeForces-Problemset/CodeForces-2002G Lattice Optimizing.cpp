#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int T;cin>>T;
    while(T--) []{
        int n;cin>>n;
        vector a(n-1,vector<int>(n)),b(n,vector<int>(n-1));
        for(auto&x:a) for(auto&i:x) cin>>i;
        for(auto&x:b) for(auto&i:x) cin>>i;
        const auto lim=(n*2-2)/3;
        vector<vector<uint64_t>> st(n);
        [&](this auto __self,int x,int y,uint64_t s){
            if(x+y==lim) return st[x].emplace_back(s),void();
            if(x+1<n){
                __self(x+1,y,s);
                if(!((s>>a[x][y])&1)) __self(x+1,y,s|(1ull<<a[x][y]));
            }
            if(y+1<n){
                __self(x,y+1,s);
                if(!((s>>b[x][y])&1)) __self(x,y+1,s|(1ull<<b[x][y]));
            }
        }(0,0,0);
        for(auto&x:st){
            ranges::sort(x);
            x.erase(unique(x.begin(),x.end()),x.end());
        }
        auto ans=0;
        [&](this auto __self,int x,int y,uint64_t s){
            if(x+y==lim){
                cir(v,ans+1,n*2){
                    const auto ns=s&((1ull<<v)-1);
                    const auto req=((1ull<<v)-1)^ns;
                    if(ranges::binary_search(st[x],req)) ans=v;
                    else break;
                }
                return;
            }
            if(x) __self(x-1,y,s|(1ull<<a[x-1][y]));
            if(y) __self(x,y-1,s|(1ull<<b[x][y-1]));
        }(n-1,n-1,0);
        println(cout,"{}",ans);
    }();
    return 0;
}
