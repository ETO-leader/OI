#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n,m;cin>>n>>m;
    vector<int64_t> cnt(2);
    cir(i,0,n){
        string s;cin>>s;
        ++cnt[ranges::count(s,'0')&1];
    }
    cout<<cnt[0]*cnt[1]<<'\n';
    return 0;
}
