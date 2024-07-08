#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
int mex(vector<int>&v){
    vector<int> c(32,true);
    for(auto&i:v) c[i]=false;
    cir(i,0,32) if(c[i]) return i;
    return 114514;
}
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int T;cin>>T;
    while(T--){
        int n;cin>>n;
        vector<int> v(n);
        for(auto&i:v) cin>>i;
        const int cx=(1<<n);
        int ans=0;
        cir(i,1,cx){
            vector<int> vx;int mx=0;
            cir(j,0,n) if(i&(1<<j)){
                mx=max(mx,v[j]);
                vx.push_back(v[j]);
            }
            (ans+=(mx<=(mex(vx)+1)))%=998244353;
        }
        cout<<ans<<'\n';
    }
    return 0;
}
