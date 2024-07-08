#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using VI=vector<int>;
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n;cin>>n;VI a(n),vis(n);
    for(auto&i:a) cin>>i;
    int ans=0;
    cir(i,0,n) if(a[i]){
        int j=i;
        while(j<n-1&&a[j+1]) ++j;
        bool is2=false;
        cir(x,i,j+1) is2|=(a[x]==2);
        if(is2){
            if(i) vis[i-1]=true;
            if(j<n-1) vis[j+1]=true;
        }else{
            if(i&&(!vis[i-1])) vis[i-1]=true;
            else if(j<n-1) vis[j+1]=true;
        }
        cir(x,i,j+1) vis[x]=true;
        ++ans;
        i=j+1;
    }
    cout<<ans+count(vis.begin(),
        vis.end(),false)<<'\n';
    return 0;
}
