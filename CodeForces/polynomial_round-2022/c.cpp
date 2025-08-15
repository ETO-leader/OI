#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int T;cin>>T;
    while(T--) [&]{
        int n;cin>>n;
        string a;cin>>a;
        auto ans=1;
        cout<<ans<<' ';
        cir(i,1,n-1){
            ans=((a[i-1]=='0'&&a[i]=='1')||(a[i-1]=='1'&&a[i]=='0')?i+1:ans);
            cout<<ans<<' ';
        }
        cout<<'\n';
    }();
    return 0;
}
