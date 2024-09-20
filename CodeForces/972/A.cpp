#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int T;cin>>T;
    while(T--) [&](){
        int n;cin>>n;
        auto cnt=n/5;
        cir(i,0,5){
            if(n%5>i) cout<<"aeiou"[i];
            cir(j,0,cnt) cout<<"aeiou"[i];
        }
        cout<<'\n';
    }();
    return 0;
}
