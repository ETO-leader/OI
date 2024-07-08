#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,abm,mmx,avx,avx2")
#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i) 
using namespace std;
const int nq=1e5+7;
int v[nq],qx[nq],ans[nq],mx[nq],mn[nq];
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n,w,q;cin>>n>>w>>q;
    cir(i,0,n) cin>>v[i];
    cir(i,0,q) cin>>qx[i],qx[i]=w-qx[i];
    cir(i,0,q) mx[i]=mn[i]=v[0];
    cir(i,1,n) cir(j,0,q){
        mx[j]=mx[j]>v[i]?mx[j]:v[i];
        mn[j]=mn[j]<v[i]?mn[j]:v[i];
        if(mx[j]-mn[j]>qx[j])
            ++ans[j],mx[j]=mn[j]=v[i];
    }
    cir(i,0,q) cout<<ans[i]<<'\n';
    return 0;
}