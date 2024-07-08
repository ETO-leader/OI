#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
int check(int x,int y){
    const int g=__gcd(x,y);
    if(!((x/g)&1)) return 0;
    return 1+((y/g)&1);
}
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int T;cin>>T;
    while(T--) [&]{
        int n;cin>>n;
        vector<int> a(n),b(n);
        for(auto&i:a) cin>>i;
        for(auto&i:b) cin>>i;
        unordered_set<int> cnx;
        cir(i,0,n) if(a[i]|b[i]){
            cnx.insert(check(a[i],b[i]));
        }
        cout<<(cnx.size()<2?"YES\n":"NO\n");
    }();
    return 0;
}
