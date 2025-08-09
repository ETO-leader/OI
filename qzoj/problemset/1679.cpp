#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    string s;cin>>s;
    int k;cin>>k;
    const auto n=(int)(s.size());
    vector<int> fail(n),f(n);
    auto ans=0;
    cir(i,0,n-1){
        fail[i]=i-1;
        f[i]=(k>1?n+7:1);
        cir(j,i+1,n){
            auto x=fail[j-1];
            while(x>i-1&&s[x+1]!=s[j]) x=fail[x];
            if(s[x+1]==s[j]) fail[j]=x+1,f[j]=(j-i+1>k-1?min(j-i+1,f[x+1]):n+7);
            else fail[j]=i-1,f[j]=(j-i+1>k-1?j-i+1:n+7);
            ans+=(f[j]*2<(j-i+1));
        }
    }
    cout<<ans<<'\n';
    return 0;
}
