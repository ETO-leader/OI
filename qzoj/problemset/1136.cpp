#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    string s;cin>>s;
    const auto n=(int)(s.size());
    int k;cin>>k;
    auto ans=(string)("");
    auto p=-1;
    while(p+k+1<n){
        auto mn=251,px=-1;
        cir(i,0,k+1) if(p+i+1<n) if(s[p+i+1]-'0'<mn){
            mn=s[p+i+1]-'0';px=p+i+1;
        }
        ans+=mn+'0';
        k-=px-p-1;
        p=px;
    }
    while(ans.size()>1&&ans.front()=='0') ans.erase(ans.begin());
    cout<<ans<<'\n';
    return 0;
}
