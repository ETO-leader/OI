#include<bits/stdc++.h>
using namespace std;
using lint=long long;
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    lint n;cin>>n;
    while(n-1) cout<<n<<' ',n=(n&1?n*3+1:n/2);
    cout<<1<<'\n';
    return 0;
}