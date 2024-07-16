#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
#define rcir(i,a,b) for(int i=a;i>b;--i)
#define putstr(str) {cout<<(str)<<'\n';return;}
using namespace std;
using lint=long long;
const lint _inf=1e18+7;
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int T;cin>>T;
    while(T--){
        int n;cin>>n;
        vector<lint> D(n),C(n),v(n);
        for(auto&i:v) cin>>i;
        auto gt=[&n](vector<lint>&v,int pos){
            return pos>=0&&pos<n?v[pos]:0;
        };
        cir(i,0,n){
            D[i]=((v[i]-gt(D,i-1)>=0)?
                v[i]-gt(D,i-1):_inf);
        }
        rcir(i,n-1,-1){
            C[i]=((v[i]-gt(C,i+1))>=0?
                v[i]-gt(C,i+1):_inf/2);
        }
        [&](){
            cir(i,0,n-1){
                if(D[i]==C[i+1]) putstr("YES");
                auto v1=v[i],v2=v[i+1];
                if(v2-gt(D,i-1)>=0&&v1-gt(C,i+2)>=0
                    &&(v2-gt(D,i-1)==v1-gt(C,i+2)))
                        putstr("YES");
            }
            putstr("NO");
        }();
    }
    return 0;
}
