#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
static constexpr auto _infl=(lint)(1e18l);
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int T;cin>>T;
    while(T--) []{
        int n;cin>>n;vector<pair<int,int>> ax(n);
        for(auto&[a,b]:ax) cin>>a>>b;
        ranges::sort(ax,[](auto&a,auto&b){return a.second-a.first<b.second-b.first;});
        vector f(n+1,vector(3,_infl));
        vector ans(n+1,_infl);
        cir(i,0,n){
            vector g(n+1,vector(3,_infl));
            g[1][0]=ax[i].first*2;
            g[1][1]=ax[i].first;
			cir(w,2,n+1){
				cir(x,0,3) g[w][x]=min(g[w][x],f[w-1][x]+ax[i].first+ax[i].second);
				g[w][1]=min(g[w][1],f[w-1][0]+ax[i].second);
				g[w][2]=min(g[w][2],f[w-1][1]+ax[i].first);
				ans[w]=min(ans[w],f[w-1][1]+ax[i].second);
				ans[w]=min(ans[w],f[w-1][2]+ax[i].second*2);
            }
            cir(w,1,n+1) cir(x,0,3) f[w][x]=min(f[w][x],g[w][x]);
        }
        cir(i,2,n+1) print("{} ",ans[i]);
        println();
    }();
    return 0;
}
