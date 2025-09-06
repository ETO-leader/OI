#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int n,k;cin>>n>>k;
    vector<vector<int>> a(n*2,vector<int>(n*2));
    for(auto&x:a) for(auto&i:x) cin>>i;
    auto set(auto&st,int x,int y,int&ans){
        cir(i,-n*2,n*2+1){
            const auto nx=x+i,ny=y+i;
            if(nx>-1&&ny>-1&&nx<n*2&&ny<n*2){
                if(!st[nx][ny]) ans+=a[nx][ny],st[nx][ny]=true;
            }
        }
        cir(i,-n*2,n*2+1){
            const auto nx=x+i,ny=y-i;
            if(nx>-1&&ny>-1&&nx<n*2&&ny<n*2){
                if(!st[nx][ny]) ans+=a[nx][ny],st[nx][ny]=true;
            }
        }
    };
    auto ans=0;
    auto dfs=[&](auto __self,auto&st,int x,int y,int uk,int nans){
        if(!uk) return ans=max(ans,nans);
        cir()
    };
    vector<vector<int>> st(n*2,vector<int>(n*2));
    return 0;
}
