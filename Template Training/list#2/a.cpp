#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int n;cin>>n;
    vector ax(n,vector<int>(5));
    for(auto&x:ax) for(auto&i:x) cin>>i;
    auto check=[](vector<int> a,vector<int> b){
        if(a==b) return false;
        auto cnt=0;
        cir(i,0,5){
            if(a[i]!=b[i]){
                ++cnt;
                if(i+1<5&&a[i+1]!=b[i+1]){
                    if((a[i]+10-b[i])%10!=(a[i+1]+10-b[i+1])%10) return false;
                }
                ++i;
            }
        }
        return cnt<2;
    };
    auto ans=0;
    cir(a,0,10) cir(b,0,10) cir(c,0,10) cir(d,0,10) cir(e,0,10){
        auto vaild=true;
        for(auto&i:ax) vaild&=check({a,b,c,d,e},i);
        ans+=vaild;
    }
    cout<<ans<<'\n';
    return 0;
}
