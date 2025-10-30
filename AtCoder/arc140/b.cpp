#include<bits/stdc++.h>
#define cir(i,a,b) for(auto i=a;i<b;++i)
using namespace std;
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int n;string s;cin>>n>>s;
    const auto rcnt=count(s.begin()+1,s.end()-1,'R');
    auto ucnt=0;
    cir(i,0,n) if(s[i]=='R'){
        auto c=1;
        while(i-c>-1&&i+c<n&&s[i-c]=='A'&&s[i+c]=='C'){
            ++ucnt;++c;
        }
    }
    cout<<min<int>(rcnt*2,ucnt)<<'\n';
    return 0;
}
