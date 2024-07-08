#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n;cin>>n;vector<lint> v(n);
    for(auto&i:v) cin>>i;
    sort(v.begin(),v.end());
    if(v.front()!=1) cout<<1<<'\n',exit(0);
    lint cnt=1;
    cir(i,1,n){
        if(v[i]>cnt+1) break;
        cnt+=v[i];
    }
    cout<<cnt+1<<'\n';
    return 0;
}