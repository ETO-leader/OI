#include<bits/stdc++.h>
using namespace std;
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int T;cin>>T;
    while(T--) {
        int a0,a1,b0,b1;
        cin>>a0>>a1>>b0>>b1;
        int a=a0/a1,b=b1/b0,ans=0;
        for(int i=1;i*i<=b1;++i){
            if (b1%i) continue;
            int f=b1/i;
            ans+=i%a1==0&&__gcd(i/a1,a)==1&&__gcd(b1/i,b)==1;
            ans+=f!=i&&f%a1==0&&__gcd(f/a1,a)==1&&__gcd(b1/f,b)==1;
        }
        cout<<ans<<'\n';
    }
    return 0;
}