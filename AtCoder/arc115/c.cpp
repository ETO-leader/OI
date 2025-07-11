#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n;cin>>n;
    vector<int> a(n+1,1);
    cir(i,1,n+1){
        for(auto j=i*2;j<n+1;j+=i) a[j]=max(a[j],a[i]+1);
    }
    cir(i,1,n+1) cout<<a[i]<<' ';
    cout<<'\n';
    return 0;
}
