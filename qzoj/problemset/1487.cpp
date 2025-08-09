#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int n;cin>>n;
    vector<int> a(n);
    for(auto&i:a) cin>>i;
    const auto s=accumulate(a.begin(),a.end(),0);
    const auto mx=*max_element(a.begin(),a.end());
    cir(len,mx,s+1) if(!(s%len)){
        auto dfs=[&](auto __self,int nd,int lp,uint64_t s){
            if(__builtin_popcount(s)==n) return true;
            if(nd==len){
                const auto x=__lg((~s)&(-(~s)));
                return __self(__self,nd-a[x]?nd-a[x]:len,nd-a[x]?x+1:0,s|((uint64_t)(1)<<x));
            }else{
                cir(i,lp,n) if(!((s>>i)&1)){
                    if(nd-a[i]>-1) if(__self(__self,nd-a[i]?nd-a[i]:len,nd-a[i]?i+1:0,s|((uint64_t)(1)<<i))) return true;
                }
                return false;
            }
        };
        if(dfs(dfs,len,0,0)){
            cout<<len<<'\n';
            break;
        }
    }
    return 0;
}
