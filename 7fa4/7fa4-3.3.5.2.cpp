#include<bits/stdc++.h>
#define cir(i,a,b) for(auto i=a;i<b;++i)
using namespace std;
using lint=long long;
using VL=vector<lint>;
const lint _inf=1e18+7;
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n,m;cin>>n>>m;
    vector<vector<VL>>
        D(n+2,vector<VL>(n+1,VL(m+1,-_inf)));
    vector<VL> v(n+1,VL(n+1));
    cir(i,1,n+1) cir(j,1,i+1)
        cin>>v[j][n-i+1];
    D[n+1][0][0]=0;
    lint ans=0;
    for(int i=n;i;--i){
        lint vc=0;
        cir(h,0,n-i+2){
            vc+=v[i][h];
            cir(w,h,m+1) cir(hx,max(h-1,0),n-i+2){
                auto&d=D[i][h][w];
                d=max(d,D[i+1][hx][w-h]+vc);
                ans=max(ans,d);
            }
        }
    }
    cout<<ans<<'\n';
    return 0;
}
