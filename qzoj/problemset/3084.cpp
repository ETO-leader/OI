#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int n;cin>>n;
    auto dfs=[&](auto __self,int x){
        if(x==0) return (string)("0");
        auto res=(string)("");
        for(auto i=__lg(x)+7;~i;--i) if((x>>i)&1){
            if(i==1) res+="2+";
            else res+="2("+__self(__self,i)+")+";
        }
        res.pop_back();
        return res;
    };
    cout<<dfs(dfs,n)<<'\n';
    return 0;
}
