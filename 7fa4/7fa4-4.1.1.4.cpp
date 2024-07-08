#include<bits/stdc++.h>
using namespace std;
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    long long n,x;cin>>n;x=(1LL<<(int)(log2(n)));
    cout<<((x>1&&x/2*3<=n?x/2*3:x))<<'\n';
    return 0;
}