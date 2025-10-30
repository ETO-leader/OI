#include<bits/stdc++.h>
#define cir(i,a,b) for(auto i=a;i<b;++i)
using namespace std;
using lint=long long;
static constexpr auto _infl=(lint)(1e18l);
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int c,T;cin>>c>>T;
    while(T--) []{
        int n,m,k,d;cin>>n>>m>>k>>d;
        vector pre(n,vector<lint>(k+1));
        cir(i,0,m){
            int x,y,v;cin>>x>>y>>v;--x;
            if(y<k+1) pre[x][y]+=v;
        }
        cir(i,0,n) cir(w,1,k+1) pre[i][w]+=pre[i][w-1];
        vector f(n+1,vector(k+1,-_infl));
        f[0][0]=0;
        cir(i,0,n) cir(w,0,k+1){
            f[i+1][0]=max(f[i+1][0],f[i][w]);
            if(w+1<k+1) f[i+1][w+1]=max(f[i+1][w+1],f[i][w]+pre[i][w+1]-d);
        }
        cout<<*ranges::max_element(f[n])<<'\n';
    }();
    return 0;
}
