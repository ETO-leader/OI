#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int T;cin>>T;
    while(T--) [&]{
        int n;cin>>n;vector<int> a(n);
        for(auto&i:a) cin>>i;
        cir(i,0,n) if(a[i]<max(i,n-1-i)*2+1) return println("NO");
        println("YES");
    }();
    return 0;
}
