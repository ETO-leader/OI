#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
const int bound_max=1e9+7;
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n,a,b;cin>>n>>a>>b;
    vector<int> vx(n);
    for(auto&i:vx) cin>>i;
    sort(vx.begin(),vx.end());
    int l=0,r=bound_max,ans=-1;
    while(r>=l){
        const int mid=(l+r)/2;
        [&a,&b](int mid,vector<int> vx){
            auto i=vx.begin(),j=vx.end()-1;
            for(;i<vx.end();++i){
                if((*i)>=mid) break;
                while(j>i&&(*i)<mid){
                    while(j>i&&((*j)-b<mid)) --j;
                    if(i!=j){
                        const int dst=min(((*j)-mid)/b,
                            (mid-(*i)+a-1)/a);
                        (*j)-=(dst*b);
                        (*i)+=(dst*a);
                    }
                }
                if(i==j&&(*i)<mid) return false;
            }
            return true;
        }(mid,vx)?(l=mid+1),(ans=mid):(r=mid-1);
    }
    cout<<ans<<'\n';
    return 0;
}
