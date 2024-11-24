#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int T;cin>>T;
    while(T--) [&]{
        string s;cin>>s;
        cir(i,0,(int)(s.size())){
            if(i+1<(int)(s.size())&&s[i]==s[i+1]) return println("{}{}",s[i],s[i+1]);
            if(i+2<(int)(s.size())&&set{s[i],s[i+1],s[i+2]}.size()==3) return println("{}{}{}",s[i],s[i+1],s[i+2]);
        }
        println("-1");
    }();
    return 0;
}
