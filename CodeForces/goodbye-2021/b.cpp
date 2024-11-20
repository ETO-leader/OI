#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int T;cin>>T;
    while(T--) [&](){
        int n;cin>>n;
        string s;cin>>s;
        auto ans=(string)("")+s[0]+s[0];
        string cur(1,s[0]);
        cir(i,1,n) if(s[i]<s[i-1]+1) cur+=s[i];
        while(!cur.empty()){
            auto mn=cur;
            for(auto i:views::reverse(cur)) mn+=i;
            ans=min(ans,mn);
            const auto bk=cur.back();
            while((!cur.empty())&&cur.back()==bk) cur.pop_back();
        }
        println("{}",ans);
    }();
    return 0;
}
