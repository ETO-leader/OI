#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int n;cin>>n;
    vector<int> a(n);
    for(auto&i:a) cin>>i;
    sort(a.begin(),a.end(),greater<>());
    const auto ws=accumulate(a.begin(),a.end(),0);
    const auto mx=*max_element(a.begin(),a.end());
    cir(len,mx,ws+1) if(!(ws%len)){
        auto dfs=[&](auto __self,int nd,int lp,uint64_t s,int pre){
            if(pre+len==ws) return true;
            if(nd==len){
                const auto x=__lg((~s)&(-(~s)));
                return __self(__self,nd-a[x]?nd-a[x]:len,nd-a[x]?x+1:0,s|((uint64_t)(1)<<x),pre+a[x]);
            }else{
                auto pmn=a[0]+7;
                auto nxt=[&](int p){
                    return __lg((~(s>>(p+1)))&(-(~(s>>(p+1)))))+p+1;
                };
                for(auto i=nxt(lp-1);i<n;i=nxt(i)){
                    if(nd-a[i]>-1&&a[i]!=pmn) if(__self(__self,nd-a[i]?nd-a[i]:len,nd-a[i]?i+1:0,s|((uint64_t)(1)<<i),pre+a[i])) return true;
                    pmn=a[i];
                }
                return false;
            }
        };
        if(dfs(dfs,len,0,0,0)){
            cout<<len<<'\n';
            break;
        }
    }
    return 0;
}
