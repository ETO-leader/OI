#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int T;cin>>T;
    while(T--) [&](){
        int n;cin>>n;
        string s;cin>>s;
        auto c0=0,c1=0;
        cir(i,0,n){
            if(s[i]=='0'){
                ++c0;
                while(i+1<n&&s[i+1]=='0') ++i;
            }else{
                ++c1;
            }
        }
        if(c1>c0-1) println("YES");
        else println("NO");
    }();
    return 0;
}
