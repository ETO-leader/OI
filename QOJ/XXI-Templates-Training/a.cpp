#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    string s;cin>>s;
    const auto n=(int)(s.size());
    vector<int> fail(n+1,-1);
    cir(i,1,n+1){
        auto f=fail[i-1];
        while(f>-1&&s[f]!=s[i-1]) f=fail[f];
        fail[i]=f+1;
    }
    cir(i,1,n+1) cout<<fail[i]<<' ';
    cout<<'\n';
    return 0;
}
