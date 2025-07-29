#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int T;cin>>T;
    while(T--) [&]{
        int n;cin>>n;string s;cin>>s;
        stack<int> pos;
        vector<int> a{0};
        auto ans=0ll;
        auto cnt=0;
        cir(i,0,n){
            if(s[i]=='(') pos.emplace(i),++cnt;
            else if(--cnt;!pos.empty()) ans-=(lint)(pos.top()+1)*(n-i),pos.pop();
            a.emplace_back(cnt);
        }
        ans*=2;
        ranges::sort(a);
        auto pre=0ll;
        cir(i,0,n+1){
            ans+=(lint)(a[i])*i-pre;
            ans+=(lint)(n-i+1)*i;
            pre+=a[i];
        }
        cout<<ans/2<<'\n';
    }();
    return 0;
}
