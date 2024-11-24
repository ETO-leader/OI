#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int T;cin>>T;
    while(T--) [&]{
        int n,m;cin>>n>>m;vector<int> s(m);
        for(auto&i:s) cin>>i;
        ranges::reverse(s);
        vector<int> divc(n+1),isp(n+1,true);
        cir(i,2,n+1) if(isp[i]){
            auto w=(lint)(i);
            while(w<n+1){
                for(auto j=w;j<n+1;j+=w) ++divc[j],isp[j]=false;
                w*=i;
            }
        }
        vector<int> ans(n);
        cir(i,0,n) if(divc[i+1]>m-1) return println("-1");
        cir(i,0,n) ans[i]=s[divc[i+1]];
        for(auto&i:ans) print("{} ",i);
        println("");
    }();
    return 0;
}
