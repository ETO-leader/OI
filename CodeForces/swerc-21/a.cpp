#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int T;cin>>T;
    while(T--) [&](){
        int n;cin>>n;map<int,int> ax;
        cir(i,0,n){
            int a,b;cin>>a>>b;ax[b]=max(ax[b],a);
        }
        auto ans=0;
        for(auto&[a,b]:ax) ans+=b;
        if(ax.size()<10) return println("MOREPROBLEMS");
        println("{}",ans);
    }();
    return 0;
}
