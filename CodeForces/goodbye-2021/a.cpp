#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int T;cin>>T;
    while(T--) [&](){
        int n;cin>>n;set<int> a;
        cir(i,0,n){
            int x;cin>>x;
            if(a.count(x)) x*=-1;
            a.insert(x);
        }
        println("{}",a.size());
    }();
    return 0;
}
