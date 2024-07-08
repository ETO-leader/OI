#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n,li,ri;cin>>n;map<int,int> tv;
    cir(i,0,n) cin>>li>>ri,tv[li]++,tv[ri]--;
    int ans=0,cnt=0;
    for(auto&i:tv){
        cnt+=i.second;ans=max(ans,cnt);
    }
    cout<<ans<<'\n';
    return 0;
}