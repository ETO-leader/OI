#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int n,m;cin>>n>>m;
    vector<vector<int>> a(n,vector<int>(m));
    for(auto&x:a) for(auto&i:x) cin>>i;
    vector<vector<bool>> isok(n-1,vector<bool>(m-1));
    cir(i,0,n-1) cir(j,0,m-1) isok[i][j]=(a[i][j]+a[i+1][j+1]<a[i+1][j]+a[i][j+1]+1);
    a.assign(n-1,vector<int>(m-1));
    auto&ur=a;
    cir(i,0,n-1){
        auto pos=m-2;
        for(auto j=m-2;~j;--j) if(isok[i][j]){
            ur[i][j]=pos-j+1;
        }else{
            ur[i][j]=-1;pos=j-1;
        }
    }
    auto ans=0;
    cir(i,0,m-1){
        cir(l,0,n-1) if(ur[l][i]>-1){
            auto mxr=n+m+7;
            cir(r,l,n-1){
                mxr=min(mxr,ur[r][i]+1);
                if(!mxr) break;
                ans=max(ans,mxr*(r-l+2));
            }
        }
    }
    cout<<ans<<'\n';
    return 0;
}
