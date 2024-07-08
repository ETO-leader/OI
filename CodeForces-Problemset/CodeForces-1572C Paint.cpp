#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using VI=vector<int>;
const int _inf=1e9+7;
int main(){
    int T;cin>>T;
    while(T--){
        int n;cin>>n;VI a(n);
        vector<VI> mp(n+1);
        cir(i,0,n){
            cin>>a[i];mp[a[i]].push_back(i);
        }
        vector<VI> D(n,VI(n));
        cir(x,1,n) cir(l,0,n-x){
            const int r=l+x;
            auto&d=D[l][r];
            d=D[l+1][r-1]+1+(a[r]!=a[r-1])+(l!=r);
            for(auto&p:mp[a[l]]){
                if(p>r) break;
                if(p>l-1){
                    d=min(d,D[l][p]+(p<n-1?D[p+1][r]:0)
                        +(a[p]!=a[r]));
                }
            }
        }
        cout<<D[0][n-1]<<'\n';
    }
    return 0;
}
