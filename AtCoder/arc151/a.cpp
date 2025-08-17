#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int n;cin>>n;
    string a,b;cin>>a>>b;
    auto cnt=0;
    cir(i,0,n) cnt+=a[i]!=b[i];
    if(cnt&1){
        cout<<-1<<'\n';
    }else{
        cnt/=2;
        auto acnt=cnt,bcnt=cnt;
        string ans;
        cir(i,0,n) if(a[i]!=b[i]){
            if(a[i]=='0'&&acnt) ans+=a[i],--acnt;
            else if(b[i]=='0'&&bcnt) ans+=b[i],--bcnt;
            else if(acnt) ans+=a[i],--acnt;
            else ans+=b[i],--bcnt;
        }else{
            ans+='0';
        }
        cout<<ans<<'\n';
    }
    return 0;
}
