#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
vector<lint> fib(62,1);
lint lca(lint a,lint b){
    if(a==b) return a;
    if(a<b) swap(a,b);
    const int p=lower_bound(fib.begin(),
        fib.end(),a)-fib.begin();
    return lca(b,a-fib[p-1]);
}
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int m;cin>>m;
    cir(i,2,62) fib[i]=fib[i-1]+fib[i-2];
    while(m--){
        lint a,b;cin>>a>>b;
        cout<<lca(a,b)<<'\n';
    }
    return 0;
}
