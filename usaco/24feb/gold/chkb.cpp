#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n;cin>>n;basic_string<lint> a(n,0);
    for(auto&i:a) cin>>i;
    a=a+a;vector<int> stc;
    vector<lint> ans(n+1);
    ans[0]=accumulate(a.begin(),a.end(),(lint)(0))/2;
    cir(i,0,n*2){
        while((!stc.empty())&&a[stc.back()]>a[i]-1)
            stc.pop_back();
        stc.push_back(i);
        if(i>n-1){
            for(int p=(int)(stc.size())-2;~p;--p){
                const auto tml=i-stc[p];
                if(tml>n) break;
                ans[tml]-=a[stc[p+1]]-a[stc[p]];
            }
        }
    }
    cir(i,1,n+1) cout<<(ans[i]+=ans[i-1])<<'\n';
    return 0;
}
