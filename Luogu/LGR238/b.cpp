#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
static constexpr auto _inf=(int)(1e9+7);
using lint=long long;
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int T;cin>>T;
    while(T--) []{
        int n,a,b;cin>>n>>a>>b;
        if(a+b>max(n,2)-2){
            cout<<-2<<'\n';
        }else{
            vector<int> ans(n);
            auto v=0;
            if(a) ans[0]=1;
            if(b) ans[n-1]=-1;
            for(auto p=a;p;--p){
                ans[p]=v;v^=1;
            }
            v=0;
            for(auto p=n-b-1;p<n-1;++p){
                if(p>a) ans[p]=-v;
                v^=1;
            }
            for(auto&x:ans) cout<<x<<' ';
            cout<<'\n';
        }
    }();
    return 0;
}
