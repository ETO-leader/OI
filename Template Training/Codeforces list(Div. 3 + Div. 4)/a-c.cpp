#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int T;cin>>T;
    while(T--) []{
        lint n,k;cin>>n>>k;
        println("{}",(k-1)/(n-1)*n+k-(k-1)/(n-1)*(n-1));
    }();
    return 0;
}
