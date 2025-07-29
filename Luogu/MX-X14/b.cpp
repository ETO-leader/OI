#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
static constexpr auto _inf=(int)(1e9+7);
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int T;cin>>T;
    while(T--) []{
        int n;cin>>n;map<int,int> cnt;
        cir(i,0,n){
            int x;cin>>x;++cnt[x];
        }
        if(n&1) return cout<<-1<<'\n',void();
        vector<pair<int,int>> cinfo;
        for(auto&x:cnt) cinfo.emplace_back(x);
        ranges::sort(cinfo,[&](auto&a,auto&b){return a.second>b.second;});
        cir(i,1,n/2+1){
            const auto w0=(n/i)-((n/i)&1);
            const auto w1=w0+2;
            const auto c0=i-(n-w0*i)/2;
            const auto c1=i-c0;
            vector<vector<int>> ans(i);
            priority_queue<pair<int,int>> lim;
            cir(i,0,c1) lim.emplace(w1,i);
            cir(i,0,c0) lim.emplace(w0,i+c1);
            auto las=-1;
            auto ok=true;
            for(auto[a,b]:cinfo){
                vector<pair<int,int>> ins;
                while(!lim.empty()){
                    const auto[w,p]=lim.top();lim.pop();
                    ans[p].emplace_back(a);
                    --b;
                    if(w-1) ins.emplace_back(w-1,p);
                    if(!b) break;
                }
                for(auto&x:ins) lim.emplace(x);
                if(b) ok=false;
            }
            if(!ok) continue;
            cout<<i<<'\n';
            for(auto&x:ans){
                cout<<x.size()<<' ';
                for(auto&i:x) cout<<i<<' ';
                cout<<'\n';
            }
            return;
        }
        cout<<-1<<'\n';
    }();
    return 0;
}
