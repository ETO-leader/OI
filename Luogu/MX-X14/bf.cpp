#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
static constexpr auto _inf=(int)(1e9+7);
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int T;cin>>T;
    while(T--) []{
        int n;cin>>n;vector<int> a(n);
        if(n>10) return;
        for(auto&x:a) cin>>x;
        vector<vector<int>> ans;
        vector<vector<int>> cur;
        auto dfs=[&](auto __self,int p)->void {
            if(p==n){
                auto ok=true;
                cir(i,0,(int)(cur.size())) ok&=(!(cur[i].size()&1));
                if(ok){
                    if(ans.empty()) ans=cur;
                    else if(ans.size()>cur.size()) ans=cur;
                }
                return;
            }
            cur.emplace_back(vector{a[p]});
            __self(__self,p+1);
            cur.pop_back();
            cir(i,0,(int)(cur.size())){
                if(ranges::count(cur[i],a[p])) continue;
                cur[i].emplace_back(a[p]);
                __self(__self,p+1);
                cur[i].pop_back();
            }
        };
        dfs(dfs,0);
        if(!ans.empty()){
            cout<<ans.size()<<'\n';
            for(auto&x:ans){
                cout<<x.size()<<' ';
                for(auto&i:x) cout<<i<<' ';
                cout<<'\n';
            }
        }else{
            cout<<-1<<'\n';
        }
    }();
    return 0;
}
