#include<bits/stdc++.h>
#define cir(i,a,b) for(auto i=a;i<b;++i)
using namespace std;
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n;cin>>n;vector<int> mxi(n);
    cir(i,1,n+1)
        for(auto j=i*2;j<n+1;j+=i)
            mxi[j-1]=i;
    sort(mxi.begin(),mxi.end());
    mxi.erase(mxi.begin());
    for(auto&i:mxi) cout<<i<<' ';
    cout<<'\n';
    return 0;
}
