#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n,l,r,xi;cin>>n>>l>>r;
    multiset<lint> mts;vector<lint> q;
    lint cnt=0,ans;
    cir(i,0,l) cin>>xi,q.push_back((cnt+=xi));
    ans=cnt;
    cir(i,l,r){
        cin>>xi,mts.insert(q[i-l]);
        q.push_back((cnt+=xi));
        ans=max(ans,max(cnt,cnt-*mts.begin()));
    }
    cir(i,r,n){
        cin>>xi;if(i>r) mts.erase(mts.find(q[i-r-1]));
        q.push_back((cnt+=xi));mts.insert(q[i-l]);
        ans=max(ans,cnt-*mts.begin());
    }
    cout<<ans<<'\n';
    return 0;
}