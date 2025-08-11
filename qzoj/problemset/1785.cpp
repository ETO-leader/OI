#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
static constexpr auto _inf=(int)(1e9+7);
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int n,h;cin>>n>>h;
    auto dfs=[&](auto __self,int req,int k,int mxr,int mxh){
        if(mxr*mxr*mxh*k<req) return _inf;
        if(!k) return 0;
        auto res=_inf;
        cir(r,k,mxr+1) cir(h,1,mxh+1){
            if(r*r*h>req) break;
            res=min(res,__self(__self,req-r*r*h,k-1,r-1,h-1)+r*h*2);
        }
        return res;
    };
    auto ans=_inf;
    cir(r0,h,n+1) cir(h0,1,40){
        if(r0*r0*h0>n) break;
        ans=min(ans,dfs(dfs,n-r0*r0*h0,h-1,r0-1,h0-1)+r0*h0*2+r0*r0);
    }
    cout<<(ans<_inf?ans:0)<<'\n';
    return 0;
}
