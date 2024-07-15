#pragma GCC optimize("Ofast")
#pragma GCC optimize("inline")
#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
auto dfs(int p,vector<lint>&a,vector<lint>&b,vector<lint>&c,vector<lint>&ar,vector<bool>&st,int n,int las,lint ans){
    if(p==n) return ans;
    auto res=0ll;
    cir(i,p,n*2) if(!st[i]){
        a[p]=ar[i];b[p]=ar[n*3-1-p];st[i]=true;
        cir(w,max(las,i)+1,n*2) if(!st[w]){
            st[w]=true;c[p]=ar[w];
            const auto nw=(a[p]-b[p])*c[p]+ans;
            if(nw*n>res*p&&[&](){
                cir(x,0,p){
                    if(a[p]>c[x]&&c[p]<a[x]-b[x]) return false;
                    if(a[p]<c[x]&&c[p]>a[x]-b[x]) return false;
                }
                return true;
            }()) res=max(res,dfs(p+1,a,b,c,ar,st,n,w,nw));
            st[w]=false;
        }
        st[i]=false;
        break;
    }
    return res;
}
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int T,n;cin>>T>>n;
    while(T--) [&](){
        vector<lint> ar(n*3),a(n),b(n),c(n);
        vector<bool> st(n*2);
        for(auto&i:ar) cin>>i;
        ranges::sort(ar,greater<lint>());
        cout<<dfs(0,a,b,c,ar,st,n,0,0)<<'\n';
    }();
    return 0;
}
