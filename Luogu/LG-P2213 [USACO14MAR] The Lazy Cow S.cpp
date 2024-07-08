#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using VI=vector<int>;
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n,k;cin>>n>>k;
    vector<VI> a(n,VI(n));
    for(auto&i:a) for(auto&j:i) cin>>j;
    for(auto&i:a) cir(j,1,n) i[j]+=i[j-1];
    auto qry=[&](int x,int l,int r){
        return a[x][r]-(l?a[x][l-1]:0);
    };
    auto calc=[&](int x,int y){
        int res=0;
        cir(i,0,n) if(abs(i-x)<k+1){
            const int d=k-abs(i-x);
            res+=qry(i,max(y-d,0),min(y+d,n-1));
        }
        return res;
    };
    int ans=0;
    cir(i,0,n) cir(j,0,n) ans=max(ans,calc(i,j));
    cout<<ans<<'\n';
    return 0;
}
