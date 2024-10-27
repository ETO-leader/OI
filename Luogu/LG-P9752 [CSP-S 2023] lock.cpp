#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int n;cin>>n;
    vector<vector<int>> a(n,vector<int>(5));
    for(auto&x:a) for(auto&i:x) cin>>i;
    auto check=[&](vector<int> a,vector<int> b){
        vector<pair<int,int>> pos;
        cir(i,0,5) if(a[i]!=b[i]) pos.emplace_back(i,(a[i]+10-b[i])%10);
        if(pos.empty()) return false;
        if(pos.size()>2) return false;
        if(pos.size()==1) return true;
        return pos[1].first-pos[0].first==1&&pos[1].second==pos[0].second;
    };
    auto checkarr=[&](vector<int> x){
        auto res=true;
        for(auto&xi:a) res&=check(xi,x);
        return res;
    };
    auto cnt=0;
    cir(a0,0,10) cir(a1,0,10) cir(a2,0,10) cir(a3,0,10) cir(a4,0,10) cnt+=checkarr({a0,a1,a2,a3,a4});
    cout<<cnt<<'\n';
    return 0;
}
