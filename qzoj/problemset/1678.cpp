#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int n;cin>>n;
    string s;cin>>s;
    vector<int> fail(n),val(n);
    fail[0]=-1;
    iota(val.begin(),val.end(),1);
    auto ans=0ll;
    cir(i,1,n){
        auto p=fail[i-1];
        while(p>-1&&s[p+1]!=s[i]) p=fail[p];
        if(s[p+1]!=s[i]) fail[i]=-1;
        else fail[i]=p+1,ans+=(i+1-(val[i]=min(val[i],val[p+1])));
    }
    cout<<ans<<'\n';
    return 0;
}
