#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n;cin>>n;set<int,greater<int>> B;
    vector<int> v(n),Be;
    cir(i,1,2*n+1) B.insert(i);
    for(auto&i:v) cin>>i,B.erase(i);
    for(auto i:B) Be.push_back(i);
    sort(v.begin(),v.begin()+n/2,greater<int>());
    sort(v.begin()+n/2,v.end());
    int cnt=0,l=0,r=n/2-1;
    cir(i,0,n/2) Be[l]<v[i]?--r:(++l,++cnt);
    l=n/2,r=n-1;
    cir(i,n/2,n) Be[r]>v[i]?++l:(--r,++cnt);
    cout<<cnt<<'\n';
    return 0;
}