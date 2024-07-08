#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int T;cin>>T;
    while(T--){
        int n;cin>>n;
        vector<int> v(n);
        for(auto&i:v) cin>>i;
        vector<bool> cx(1<<8);
        int ans=0,x=0;
        reverse(v.begin(),v.end());
        for(auto&i:v){
            x^=i;int ansi=x;
            cir(i,0,(1<<8)) if(cx[i])
                ansi=max(ansi,x^i);
            cx[x]=true;
            ans=max(ans,ansi);
        }
        cout<<ans<<'\n';
    }
    return 0;
}
