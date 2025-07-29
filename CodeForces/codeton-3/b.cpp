#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int T;cin>>T;
    while(T--) [&]{
        int n;cin>>n;string s;
        cin>>s;
        auto ans=(lint)(ranges::count(s,'0'))*ranges::count(s,'1');
        cir(i,0,n) if(s[i]=='0'){
            auto p=i;
            while(p<n&&s[p]=='0') ++p;
            ans=max(ans,(lint)(p-i)*(p-i));
            i=p;
        }
        cir(i,0,n) if(s[i]=='1'){
            auto p=i;
            while(p<n&&s[p]=='1') ++p;
            ans=max(ans,(lint)(p-i)*(p-i));
            i=p;
        }
        cout<<ans<<'\n';
    }();
    return 0;
}
