#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int T;cin>>T;
    while(T--) [&]{
        int n;string s;cin>>n>>s;
        auto val=s[0]-'0';
        cir(i,1,n){
            if(val>0){
                cout<<'-';
                val-=(s[i]-'0');
            }else{
                cout<<'+';
                val+=(s[i]-'0');
            }
        }
        cout<<'\n';
    }();
    return 0;
}
