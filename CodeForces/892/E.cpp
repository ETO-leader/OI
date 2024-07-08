#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
using VI=vector<lint>;
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int T;cin>>T;
    while(T--){
        int n,k;cin>>n>>k;VI a(n+1),b(n+1);
        cir(i,1,n+1) cin>>a[i];
        cir(i,1,n+1) cin>>b[i];
        auto getw=[&](int l,int r){
            return abs(b[l]-a[r])+abs(b[r]-a[l]);
        };
        auto len=[&](int l,int r){
            return r-l+1;
        };
        vector<VI> f(n+1);
        vector<vector<tuple<lint,lint,lint>>> wx(n+1);
        cir(l,1,n+1) cir(r,l,n+1){
            wx[len(l,r)].push_back({getw(l,r),l,r});
        }
        cir(i,1,k+1){
            sort(wx[i].begin(),wx[i].end(),
                greater<tuple<lint,lint,lint>>());
            while(wx[i].size()*i>k*5) wx[i].pop_back();
            for(auto&[x,l,r]:wx[i]) f[r].push_back(l);
        }
        vector<VI> D(n+1,VI(k+1));
        cir(i,1,n+1) cir(w,0,k+1){
            D[i][w]=D[i-1][w];
            for(auto&x:f[i]){
                if(len(x,i)>w) break;
                D[i][w]=max(D[i][w],D[
                    x-1][w-len(x,i)]+getw(x,i));
            }
        }
        cout<<D[n][k]<<'\n';
    }
    return 0;
}
