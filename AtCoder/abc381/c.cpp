#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int n;cin>>n;
    string s;cin>>s;
    auto ans=(int)((bool)(ranges::count(s,'/')));
    cir(i,1,n-1) if(s[i]=='/'){
        auto l=i-1,r=i+1;
        ans=max(ans,1);
        if(s[l]!='1'||s[r]!='2') continue;
        while(l>0&&r<n-1&&s[l-1]=='1'&&s[r+1]=='2') --l,++r;
        ans=max(ans,r-l+1);
    }
    cout<<ans<<'\n';
    return 0;
}
