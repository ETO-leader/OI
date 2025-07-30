#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int T;cin>>T;
    while(T--) []{
        int n,k;cin>>n>>k;
        string s;cin>>s;
        auto c0=0,c1=0;
        const auto sum1=ranges::count(s,'1');
        cir(i,0,k){
            c0+=(s[i]=='0');
            c1+=(s[i]=='1');
        }
        auto ans=(int)((!c0)&&(c1==sum1));
        cir(i,k,n){
            c0-=(s[i-k]=='0');
            c1-=(s[i-k]=='1');
            c0+=(s[i]=='0');
            c1+=(s[i]=='1');
            ans+=((!c0)&&(c1==sum1));
        }
        cout<<(ans==1?"Yes":"No")<<'\n';
    }();
    return 0;
}
