#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int n;cin>>n;
    vector<int> c(n+2,1);
    cir(i,2,n+2) if(c[i]==1){
        for(auto j=i*2;j<n+2;j+=i) c[j]=2;
    }
    cout<<*max_element(c.begin(),c.end())<<'\n';
    cir(i,2,n+2) cout<<c[i]<<' ';
    cout<<'\n';
    return 0;
}
