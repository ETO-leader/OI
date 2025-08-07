#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int n;cin>>n;
    vector<int> cur;
    auto dfs=[&](auto __self,int w,int mn)->void {
        for(auto i=mn;i*i<(w+1);++i) if(!(w%i)){
            cur.emplace_back(i);
            __self(__self,w/i,i);
            cur.pop_back();
        }
        if(w<n){
            cout<<n<<'=';
            for(auto&i:cur) cout<<i<<'*';
            cout<<w<<'\n';
        }
    };
    cout<<n<<"=1*"<<n<<'\n';
    dfs(dfs,n,2);
    return 0;
}
