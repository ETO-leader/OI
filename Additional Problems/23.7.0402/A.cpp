#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
const int _inf=1e9+7;
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n;cin>>n;int ml=0,mx=_inf;
    cir(i,0,n){
        int l,r;cin>>l>>r;
        ml=max(l,ml);mx=min(r,mx);
        cout<<max(0,(ml-mx+1)/2)<<'\n';
    }
    return 0;
}
