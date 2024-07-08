#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n;cin>>n;vector<int> v(n);
    for(auto&i:v) cin>>i;
    cout<<((v[n-1]-v[n-2]>1||(!((v[n-1]-n)&1)))?
        "Alice\n":"Bob\n");
    return 0;
}
