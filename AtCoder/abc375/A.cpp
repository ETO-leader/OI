#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int n;cin>>n;
    string s;cin>>s;
    auto ans=0;
    cir(i,1,n-1) ans+=(s[i-1]=='#'&&s[i]=='.'&&s[i+1]=='#');
    cout<<ans<<'\n';
    return 0;
}
