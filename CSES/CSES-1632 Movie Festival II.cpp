#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
struct film{int s,e;};
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n,m;cin>>n>>m;vector<film> vf(n);
    for(auto&i:vf) cin>>i.s>>i.e;
    sort(vf.begin(),vf.end(),
        [](film&a,film&b){return a.e<b.e;});
    multiset<int> ed;
    cir(i,0,m) ed.insert(0);
    int cnt=0;
    for(auto&i:vf){
        auto upp=ed.upper_bound(i.s);
        if(upp==ed.begin()) continue;
        --upp;cnt++,ed.erase(upp),ed.insert(i.e);
    }
    cout<<cnt<<'\n';
    return 0;
}