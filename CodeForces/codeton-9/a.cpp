#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int T;cin>>T;
    while(T--) [&]{
        int n;cin>>n;vector<int> ans(n);
        cir(i,0,n) ans[i]=i+(i+1);
        for(auto&i:ans) print("{} ",i);
        println("");
    }();
    return 0;
}
