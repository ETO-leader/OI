#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
const int _inf=1e9+7;
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int T;cin>>T;
    while(T--){
        int n;cin>>n;
        vector<int> v(n),lmax(v),rmax(n);
        for(auto&i:v) cin>>i;
        cir(i,0,n)
            lmax[i]=max((i?lmax[i-1]:-_inf),v[i]+i);
        for(int i=n-1;~i;--i)
            rmax[i]=max((i!=n-1?rmax[i+1]:-_inf),v[i]-i);
        int mx=0;
        cir(i,1,n-1){
            mx=max(v[i]+lmax[i-1]+rmax[i+1],mx);
        }
        cout<<mx<<'\n';
    }
    return 0;
}
