#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int T;cin>>T;
    while(T--) []{
        int n;cin>>n;
        vector<lint> a(n);
        for(auto&i:a) cin>>i;
        ranges::sort(a,greater<lint>());
        auto dfs=[&](auto __self,vector<lint>&x,const int pre,lint c){
            if(c>5e11l) return c;
            ranges::sort(x);
            if((int)(x.size())==n){
                auto res=c;
                cir(i,0,n) res+=a[i]*x[i];
                return res;
            }
            auto res=(lint)(1e13l);
            auto nx=x;
            cir(i,0,pre-1) nx.emplace_back(x[i]+1);
            cir(i,pre-1,(int)(x.size())){
                if((int)(x.size())+i+1>n) break;
                nx.emplace_back(x[i]+1);
                res=min(res,__self(__self,nx,i+1,c*2+(int)(nx.size())-2));
            }
            return res;
        };
        vector<lint> cur{0};
        cout<<dfs(dfs,cur,1,0)<<'\n';
    }();
    return 0;
}
