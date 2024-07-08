#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using VI=vector<int>;
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int T;cin>>T;
    while(T--) []{
        int n,m,a,b;cin>>n>>m>>a>>b;
        if(a*n!=b*m)
            return cout<<"NO\n",void();
        vector<VI> ans(n,VI(m));
        const int sft=[&](){
            cir(i,1,m) if(!(i*n%m))
                return i;
            return m;
        }();
        cir(i,0,n) cir(j,0,a)
            ans[i][(j+i*sft)%m]=true;
        cout<<"YES\n";
        for(auto&i:ans){
            for(auto&j:i) cout<<j;
            cout<<'\n';
        }
    }();
    return 0;
}
