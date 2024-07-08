#include<bits/stdc++.h>
using namespace std;
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n,k;cin>>n;set<int> s;
    while(n--) cin>>k,s.insert(k);
    cout<<s.size()<<'\n';
    return 0;
}
