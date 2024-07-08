#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using VI=vector<int>;
const int _inf=1e9+7;
struct seg{int l,r;};
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int T;cin>>T;
    while(T--){
        int n;cin>>n;vector<seg> vs(n);
        for(auto&[l,r]:vs) cin>>l>>r;
        sort(vs.begin(),vs.end(),
            [](seg&a,seg&b){return a.r<b.r;});
        VI D(n+1);
        cir(i,1,n+1){
            int mxl=-_inf;D[i]=min(i,D[i-1]+1);
            for(int j=i-1;~j;--j){
                if(mxl>(j?vs[j-1].r:-1)&&
                    vs[i-1].l>(j?vs[j-1].r:-1)){
                    D[i]=min(D[i],D[j]+i-j-2);
                }
                if(j&&vs[j-1].r>=vs[i-1].l)
                    mxl=max(mxl,vs[j-1].l);
            }
        }
        int ans=_inf;
        cir(i,1,n+1) ans=min(ans,D[i]+n-i);
        cout<<ans<<'\n';
    }
    return 0;
}
