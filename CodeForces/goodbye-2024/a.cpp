#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int T;cin>>T;
    while(T--) []{
        int n;cin>>n;
        auto vaild=false;
        int las;cin>>las;
        cir(i,0,n-1){
            int w;cin>>w;
            vaild|=(w*2>las&&las*2>w);
            las=w;
        }
        println("{}",vaild?"YES":"NO");
    }();
    return 0;
}
