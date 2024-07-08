#include<bits/stdc++.h>
#define cir(i,a,b ) for(int i=a;i<b;++i)
using namespace std;
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int T;cin>>T;
    while(T--){
        int n;cin>>n;vector<int> v(n),x;
        for(auto&i:v) cin>>i;
        cir(i,0,n) x.push_back(abs(v[i]-v[n-i-1]));
        cout<<accumulate(x.begin(),x.end(),0,
            [](int a,int b){return __gcd(a,b);})<<'\n';
    }
    return 0;
}
