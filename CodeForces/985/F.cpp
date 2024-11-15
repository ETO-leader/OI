#pragma GCC optimize("Ofast")
#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
static constexpr auto maxa=(int)(4e5+7);
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int T;cin>>T;
    while(T--) [&](){
        int n;cin>>n;
        string s;cin>>s;
        if(ranges::count(s,'R')<2) return println("YES");
        if(ranges::count(s,'B')<2) return println("YES");
        s=s+s;
        const auto ec=s[n-1];
        auto pos=s.begin();
        while(*pos==ec) ++pos;
        s.erase(s.begin(),pos);
        vector<int> cr,cb;
        cir(i,0,n-1){
            if(s[i]=='R'){
                auto cnt=1;
                while(s[i+1]=='R') ++i,++cnt;
                if(cnt>1) cr.push_back(cnt);
            }else{
                auto cnt=1;
                while(s[i+1]=='B') ++i,++cnt;
                if(cnt>1) cb.push_back(cnt);
            }
        }
        if(cr.size()&&cb.size()) return println("NO");
        if(!(cr.size()||cb.size())) return println("NO");
        auto cntvaild2=0;
        for(auto&i:cr) if(!(i&1)) ++cntvaild2;
        for(auto&i:cb) if(!(i&1)) ++cntvaild2;
        println("{}",(cntvaild2==1?"YES":"NO"));
    }();
    return 0;
}
