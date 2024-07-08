#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n,cnt=0;cin>>n;vector<int> Vp(n);
    for(auto&i:Vp) cin>>i;
    multiset<int> mts;
    for(auto&i:Vp){
        if(mts.empty()||i>=*(--mts.end())) mts.insert(i),++cnt;
        else mts.erase(mts.upper_bound(i)),mts.insert(i);
    }
    cout<<cnt<<'\n';
    return 0;
}