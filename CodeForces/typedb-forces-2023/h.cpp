#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int T;cin>>T;
    while(T--) [&]{
        int n;cin>>n;
        vector<tuple<lint,lint,lint>> x(n);
        for(auto&[k,b,a]:x) cin>>k>>b>>a;
        priority_queue<tuple<lint,int,int>> q;
        cir(i,0,n){
            const auto[k,b,a]=x[i];
            q.emplace(k,i,2);
            q.emplace((b-a)%k,i,1);
            q.emplace(0,i,0);
        }
        vector<int> vis(n);
        auto t=1;
        auto ans=0ll;
        while(!q.empty()){
            const auto[k,i,ty]=q.top();q.pop();
            if(vis[i]) continue;
            const auto[uk,ub,ua]=x[i];
            if(ty==2){
                if(ub-uk*(t+1)>ua-1){
                    ans+=(ub-uk*t);
                    vis[i]=true;
                }else{
                    continue;
                }
            }else if(ty==1){
                if(ub-uk*t>ua-1){
                    ans+=(ub-uk*t);
                    vis[i]=true;
                }else{
                    continue;
                }
            }else{
                vis[i]=true;
                ans+=ua;
            }
            clog<<" --> "<<t<<": "<<k<<' '<<i<<" ("<<ty<<")"<<" ans = "<<ans<<'\n';
            ++t;
        }
        cout<<ans<<'\n';
    }();
    return 0;
}
