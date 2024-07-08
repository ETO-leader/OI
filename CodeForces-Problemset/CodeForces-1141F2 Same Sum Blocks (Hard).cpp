#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
struct seg{int l,r;};
auto calc(vector<seg>&a){
    sort(a.begin(),a.end(),[](const seg&a
        ,const seg&b){return a.r<b.r;});
    int res=0,rx=-1;
    vector<seg> s;
    for(auto&[l,r]:a) if(l>rx){
        ++res;rx=r;
        s.push_back({l,r});
    }
    return make_pair(res,s);
}
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n;cin>>n;vector<lint> a(n);
    for(auto&i:a) cin>>i;
    cir(i,1,n) a[i]+=a[i-1];
    unordered_map<lint,vector<seg>> um;
    auto sum=[&](int l,int r){
        return a[r]-(l?a[l-1]:0);
    };
    cir(i,0,n) cir(j,i,n)
        um[sum(i,j)].push_back({i,j});
    int ans=0;vector<seg> s;
    for(auto&[x,y]:um){
        auto[w,sx]=calc(y);
        if(w>ans){
            ans=w;s=sx;
        }
    }
    cout<<ans<<'\n';
    for(auto&[l,r]:s)
        cout<<l+1<<' '<<r+1<<'\n';
    return 0;
}
