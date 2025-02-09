#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int T;cin>>T;
    while(T--) [&]{
        int n;cin>>n;vector<int> a(n);
        for(auto&i:a) cin>>i,i=i&1;
        ranges::sort(a);
        println("{}",accumulate(a.begin()+1,a.end(),0)+(!a[0]));
    }();
    return 0;
}
