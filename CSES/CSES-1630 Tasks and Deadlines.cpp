#include<bits/stdc++.h>
using namespace std;
using lint=long long;
template<typename T>
struct task{T v,ed;};
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n;cin>>n;vector<task<lint>> tsk(n);
    for(auto&i:tsk) cin>>i.v>>i.ed;
    sort(tsk.begin(),tsk.end(),
        [](task<lint>&a,task<lint>&b){return a.v<b.v;});
    lint Ntime=0,ans=0;
    for(auto&i:tsk) ans+=(i.ed-(Ntime+=i.v));
    cout<<ans<<'\n';
    return 0;
}