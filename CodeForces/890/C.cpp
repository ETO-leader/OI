#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
const int _inf=1e9+7;
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int T;cin>>T;
    while(T--){
        int n,k;cin>>n>>k;
        vector<int> a(n);
        for(auto&i:a) cin>>i;
        lint l=0,r=_inf,ans=0;
        while(r>=l){
            const int mid=(l+r)/2;
            [&](){
                cir(i,0,n){
                    vector<lint> D(n);D[i]=mid;
                    lint vali=0;
                    cir(j,i,n){
                        if(a[j]>D[j]-1) break;
                        if(j>n-2){
                            vali=k+1;break;
                        }
                        vali+=D[j]-a[j];
                        D[j+1]=max<lint>(0,D[j]-1);
                    }
                    if(vali<k+1) return true;
                }
                return false;
            }()?((l=mid+1),(ans=mid)):(r=mid-1);
        }
        cout<<ans<<'\n';
    }
    return 0;
}
