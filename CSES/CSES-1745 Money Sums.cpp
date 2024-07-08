#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n;cin>>n;set<int> s;
    cir(i,0,n){
        int k;cin>>k;
        vector<int> v;v.push_back(k);
        for(auto i:s) v.push_back(i+k);
        for(auto&i:v) s.insert(i);
    }
    cout<<s.size()<<'\n';
    for(auto i:s) cout<<i<<' ';
    cout<<'\n';
    return 0;
}