#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    lint x,k;cin>>x>>k;
    if(k==1){cout<<x<<'\n';exit(0);}
    unordered_set<lint> cnx;
    lint ans=0,px=0;
    for(lint i=2;i*i*i<=x;++i){
        lint xp=i*i,p=2;
        while(xp<=x/i){
            xp*=i;++p;
            if(p<k||cnx.count(xp)) continue;
            if((lint)(sqrt(xp*1.0L))*(lint)(sqrt(xp*1.0L))==xp)
                ++px;
            cnx.insert(xp);++ans;
        }
    }
    cout<<(k==2?ans+lint(sqrt(x*1.0L))-px:ans+1)<<'\n';
    return 0;
}
