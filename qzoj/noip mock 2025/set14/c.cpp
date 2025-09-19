#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int n,m,x,y;cin>>n>>m>>x>>y;
    vector<int> a(n),b(m);
    for(auto&i:a) cin>>i;
    for(auto&i:b) cin>>i;
    sort(a.begin(),a.end());
    priority_queue<int,vector<int>,greater<>> q(b.begin(),b.end());
    auto ans=0;
    for(auto&i:a){
        while((!q.empty())&&(q.top()<i-x)) q.pop();
        if((!q.empty())&&q.top()<i+y+1){
            ++ans;
            q.pop();
        }
    }
    cout<<ans<<'\n';
    return 0;
}
